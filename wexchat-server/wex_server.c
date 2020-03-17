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
        wexlog(wex_log_error_with_perror, "connect to neo4j");
    }
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
    }
}

void str_echo(void *sockfd) {
    ssize_t len;
    char buf[NETWORK_BUFF_SIZE];
    int sockfd2 = *((int *)sockfd);
    //false represents that socket can accept request, or it is reading content
    bool reading = false;
again:
    while((len = read(sockfd2, buf, NETWORK_BUFF_SIZE)) > 0) {
        //do here
        //write(sockfd2, buf, len);
        if (reading == false) {
            //get header
            char *head = strtok(buf, " ");
            if (!strcmp(head, "REQ")) {
                //request
                wexlog(wex_log_debug, "req accepted");
            }
            else if (!strcmp(head, "ALIVE")) {
                //alive request
                wexlog(wex_log_debug, "alive accepted");
            }
            else {
                //error
                char *error = WEX_ERROR_MSG1;
                write(sockfd2, error, strlen(error));
            }
        }
    }
    //reentered error
    if (len < 0 && errno == EINTR)
        goto again;
    else if (len < 0) {
        //printf("str_echo: read err\n");
        wexlog(wex_log_debug, "str_echo: read err");
        close(sockfd2);
        free(sockfd);
    }
    else {
        close(sockfd2);
        free(sockfd);
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
