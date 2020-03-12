#include "wex_server.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "threadpool.h"

static threadpool_t *wex_pool;

int wex_init_server(void) {

    int listenfd;
    struct sockaddr_in servaddr;
    int ret = -1;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("socket");
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(8080);

    if ((ret = bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) < 0) {
        perror("bind");
        return -1;
    }

    if ((ret = listen(listenfd, 5)) < 0) {
        perror("listen");
        return -1;
    }

    //create a thread pool
    wex_pool = threadpool_create(10, 10, 0);

    return listenfd;
}

void wex_run_server(int listenfd) {
    int connfd;
    socklen_t clilen;
    struct sockaddr_in cliaddr;

    for (;;) {
        clilen = sizeof(cliaddr);
        if ((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen)) < 0) {
            perror("accept");
            return;
        }
//        str_echo(connfd);
        int *connfdptr = malloc(sizeof(int));
        *connfdptr = connfd;
        threadpool_add(wex_pool, &str_echo, (void*)connfdptr, 0);
        //get a thread to access it

    }
}

void str_echo(void *sockfd) {
    ssize_t len;
    char buf[1024];
    int sockfd2 = *((int *)sockfd);

again:
    while((len = read(sockfd2, buf, 1024)) > 0) {
        write(sockfd2, buf, len);
    }
    if (len < 0 && errno == EINTR)
        goto again;
    else if (len < 0) {
        printf("str_echo: read err\n");
        close(sockfd2);
        exit(-1);
    }
    else if (len == 0) {
        close(sockfd2);
        free(sockfd);
        printf("ternimal closed");
    }
}

void quit_server(void) {
    threadpool_destroy(wex_pool, threadpool_graceful);
}
