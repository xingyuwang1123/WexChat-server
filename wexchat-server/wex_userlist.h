#ifndef WEX_USERLIST_H_INCLUDED
#define WEX_USERLIST_H_INCLUDED
#include "wex_hashmap.h"
#include "wex_list.h"
#include "wex_data_constraints.h"

extern T_NODE *user_table;

typedef struct {
    char uid[MAX_UID_LENGTH];
    int descripter;
}wex_user_list_entity;

//init map
int wex_init_userlist();

//add item to userlist
int wex_add_userlist(const char *uid, int descripter);

//remove item by uid
int wex_remove_userlist_byuid(const char *uid);

//remove item by descripter
int wex_remove_userlist_bydesc(int desc);

//find item by uid, return -1 if not found
int wex_find_userlist(const char *uid);

void print_userlist();

#endif // WEX_USERLIST_H_INCLUDED
