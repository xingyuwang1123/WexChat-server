#include <stdio.h>
#include <stdlib.h>
#include "wex_server.h"
#include "wexlog.h"
//
int main(int argc, char *argv[])
{
    int listenfd = wex_init_server();
    if (listenfd > 0) {
        wexlog(wex_log_info, "server inited success");
        wex_run_server(listenfd);
    }
    else {
        wexlog(wex_log_error, "wrong in inition");
    }
    wex_quit_server();
    return 0;
}


//test cjson
//int main () {
//    return 0;
//}
