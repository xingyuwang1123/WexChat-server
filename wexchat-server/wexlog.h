#ifndef WEXLOG_H_INCLUDED
#define WEXLOG_H_INCLUDED
#define DEBUG

typedef enum {
    wex_log_debug=0,
    wex_log_info=1,
    wex_log_warning=2,
    wex_log_warning_with_perror=3,
    wex_log_error=4,
    wex_log_error_with_perror=5
}wex_log_level;


void wexlog(wex_log_level level, const char* msg);


#endif // WEXLOG_H_INCLUDED
