#include "wexlog.h"


void wexlog(wex_log_level level, const char* msg) {
    //debug stage, we print it to console
    #ifdef DEBUG
        printf("wexlog:%s\n",msg);
    #endif // DEBUG
}
