#ifndef WEX_UNIXCONF_H_INCLUDED
#define WEX_UNIXCONF_H_INCLUDED

#include "wex_hashmap.h"

#define CONF_FILEPATH "./server.conf"
#define MAXLINE 208

typedef struct {
    int conf_count;
    SHashMap *conf_map;
}wex_confres_t;

typedef enum {
    wex_conf_unixconf = 1
}wex_conf_type;

/*
load configuration from filepath, deault is ./server.conf
*/
wex_confres_t *wex_loadconf(const char *filepath, wex_conf_type type);

/*
free wex_confres_t
*/
void wex_free_conf(wex_confres_t *conf);

#endif // WEX_UNIXCONF_H_INCLUDED
