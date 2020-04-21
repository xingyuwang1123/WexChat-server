#ifndef WEX_USERLIST_H_INCLUDED
#define WEX_USERLIST_H_INCLUDED
#include "wex_hashmap.h"

extern SHashMap *wex_uid_sock_map;

extern SHashMap *wex_sock_uid_map;

//init map

int wex_init_userlist();

int wex_add_userlist(const char *uid, int descripter);

int wex_remove_userlist_byuid(const char *uid);



#endif // WEX_USERLIST_H_INCLUDED
