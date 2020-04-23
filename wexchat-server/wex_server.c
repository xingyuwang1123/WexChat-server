#include "wex_server.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "wexlog.h"
#include "threadpool.h"
#include "wex_neo4j_connctor.h"
#include "wex_logic_interface.h"
#include "wex_userlist.h"

static threadpool_t *wex_pool;

int wex_init_server(void) {

    int listenfd;
    struct sockaddr_in servaddr;
    int ret = -1;

    //get the server configure
    wex_conf = wex_loadconf(CONF_FILEPATH, 0);

    //do init socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        //perror("socket");
        wexlog(wex_log_error_with_perror, "socket");
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    uint16_t port = (uint16_t)atoi(shashmap_get(wex_conf->conf_map, "SERVER_PORT"));
    servaddr.sin_port = htons(port);

    if ((ret = bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) < 0) {
        //perror("bind");
        wexlog(wex_log_error_with_perror, "bind");
        return -1;
    }

    if ((ret = listen(listenfd, 5)) < 0) {
        //perror("listen");
        wexlog(wex_log_error_with_perror, "listen");
        return -1;
    }

    //create a thread pool
    int maxcount = atoi(shashmap_get(wex_conf->conf_map, "MAX_THREAD_QUEUE_COUNT"));
    int maxsize = atoi(shashmap_get(wex_conf->conf_map, "MAX_THREAD_QUEUE_SIZE"));
    wex_pool = threadpool_create(maxcount, maxsize, 0);

    //init neo4j connector
    char *address = shashmap_get(wex_conf->conf_map, "DB_ADDRESS");
    char *kport = shashmap_get(wex_conf->conf_map, "DB_PORT");
    char *username = shashmap_get(wex_conf->conf_map, "DB_USERNAME");
    char *pass = shashmap_get(wex_conf->conf_map, "DB_PASSWORD");
    ret = wex_neo4j_connect_to_server(address, kport, username, pass);
    if (ret < 0) {
        wexlog(wex_log_error_with_perror, "disconnect to neo4j");
    }
    //init userlist
    wex_init_userlist();
    return listenfd;
}

void wex_run_server(int listenfd) {
    int connfd;
    socklen_t clilen;
    struct sockaddr_in cliaddr;

    for (;;) {
        clilen = sizeof(cliaddr);
        if ((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen)) < 0) {
            //perror("accept");
            wexlog(wex_log_warning_with_perror, "accept");
            return;
        }
//        str_echo(connfd);
        int *connfdptr = malloc(sizeof(int));
        *connfdptr = connfd;
        int ret = threadpool_add(wex_pool, &str_echo, (void*)connfdptr, 0);
        //get a thread to access it
        if (ret < 0) {
            wexlog(wex_log_warning, "wrong in adding thread to threadpool");
            close(connfd);
        }
        else {
            wexlog(wex_log_debug, "someone connected");
        }
    }
}

ssize_t wex_readline(int fd, void *vptr, ssize_t maxlen)
{
	ssize_t n, rc;
	char c, *ptr;

	ptr = vptr;
	for (n = 1; n < maxlen; n++)
	{
		again:
		if ((rc = read(fd, &c, 1)) == 1)
		{
			*ptr++ = c;
			if (c == '\n') {
                *(ptr-1) = '\0';
                break;
			}

		}
		else if (rc == 0)
		{
			*ptr = 0;
			return(n - 1);
		}
		else
		{
			if (errno == EINTR)
				goto again;
			return(-1);
		}
	}
	*ptr = 0;
	return(n);
}


void str_echo(void *sockfd) {
    ssize_t len;
    char buf[NETWORK_BUFF_SIZE];
    char *bufptr = buf;
    bool reset_flag = false;
    int sockfd2 = *((int *)sockfd);
    wex_protocol_request *req;
    char header_buf[MAX_HEADER_LENGTH];
    //false represents that socket can accept request, or it is reading content
    bool reading = false;
    size_t resting = 0;

 again:   while(1) {
        //read header
        len = wex_readline(sockfd2, header_buf, MAX_HEADER_LENGTH);
        wexlog(wex_log_debug, "header:");
        wexlog(wex_log_debug, header_buf);
        if (len <= 0) goto error;
        char *token = strtok(header_buf, " ");
        if (!strcmp(token, "ALIVE")) {
            char *msg = "ALIVE \n";
            write(sockfd2, msg, strlen(msg));
            continue;
        }
        else if (!strcmp(token, "REQ")) {
            req = wex_parse_request(header_buf + 4, MAX_HEADER_LENGTH - 4, 0, NULL);
            if (req == NULL) {
                wexlog(wex_log_warning, "bad request");
                char *msg = WEX_ERROR_MSG1;
                write(sockfd2, msg, strlen(msg));
                continue;
            }
            //read resting
            if (req->msg_length != 0) {
                resting = req->msg_length;
                while(resting > 0) {
                    if (resting > NETWORK_BUFF_SIZE)
                        len = read(sockfd2, buf, NETWORK_BUFF_SIZE);
                    else
                        len = read(sockfd2, buf, resting);
                    if (len <= 0) goto error;
                    wexlog(wex_log_debug, "body:");
                    wexlog(wex_log_debug, buf);
                    resting -= len;
                    wex_parse_request(buf, len, 1, req);
                }
                if (resting != 0) {
                    wexlog(wex_log_warning, "error in reading content");
                    continue;
                }
            }
            //do response
            char *res = wex_logic_doenter(req->method_name, req->content, req->msg_length, sockfd2);
            wex_free_request(req);
            wex_protocol_response *response = wex_construct_response("00", "WEX", "1.0", strlen(res), res, 0);
            char *writebuf = malloc(sizeof(char) * ORIGINAL_CONTENT_LENGTH);
            int slen = wex_deparse_response(response, writebuf, ORIGINAL_CONTENT_LENGTH);
            write(sockfd2, writebuf, slen);
            free(writebuf);
            wex_free_response(response);
        }


    }

error:    if (len < 0 && errno == EINTR)
        goto again;
    else if (len < 0) {
        //printf("str_echo: read err\n");
        wexlog(wex_log_debug, "str_echo: read err");
        close(sockfd2);
        free(sockfd);
        wex_remove_userlist_bydesc(sockfd2);
    }
    else {
        close(sockfd2);
        free(sockfd);
        wex_remove_userlist_bydesc(sockfd2);
        //printf("ternimal closed");
        wexlog(wex_log_debug, "ternimal closed");
    }

}

void wex_quit_server(void) {
    int ret = threadpool_destroy(wex_pool, threadpool_graceful);
    if (ret < 0) {
        wexlog(wex_log_error, "error in destroying threadpool");
    }
    wex_neo4j_endup();
    wex_free_conf(wex_conf);

}
