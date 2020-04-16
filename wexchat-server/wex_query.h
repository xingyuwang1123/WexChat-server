#ifndef WEX_QUERY_H_INCLUDED
#define WEX_QUERY_H_INCLUDED

#include "wex_entity.h"
#include "wex_list.h"

int register_query(wex_entity_user *user);

int login_query(const char *username, const char *password, int *res);

int query_id_by_username(const char *username, const char *password, char *res);

int query_headername_by_uid(const char *uid, char *header, char *name);

int query_alluserinfo_by_uid(const char *uid, wex_entity_user *user);

int update_userinfo_by_uid(wex_entity_user *user);

int query_cutin_by_uid(const char *uid, char *cutin);

int query_allfriends_by_uid(const char *uid, T_NODE *friend_head);

int update_cutin_by_uid(const char *uid, const char *cutin);

#endif // WEX_QUERY_H_INCLUDED
