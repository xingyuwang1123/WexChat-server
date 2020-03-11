#include "wex_server.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

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
        str_echo(connfd);
        close(connfd);
    }
}

void str_echo(int sockfd) {
    ssize_t len;
    char buf[1024];

again:
    while((len = read(sockfd, buf, 1024)) > 0) {
        write(sockfd, buf, len);
    }
    if (len < 0 && errno == EINTR)
        goto again;
    else if (len < 0) {
        printf("str_echo: read err\n");
        exit(-1);
    }
}
