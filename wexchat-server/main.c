#include <stdio.h>
#include <stdlib.h>
#include "wex_server.h"

int main(int argc, char *argv[])
{
    int listenfd = wex_init_server();
    if (listenfd > 0) {
        printf("server inited\n");
        wex_run_server(listenfd);
    }
    return 0;
}
