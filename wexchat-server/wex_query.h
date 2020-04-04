#ifndef WEX_QUERY_H_INCLUDED
#define WEX_QUERY_H_INCLUDED

#include "wex_entity.h"

int register_query(wex_entity_user *user);

int login_query(const char *username, const char *password, int *res);

int query_id_by_username(const char *username, const char *password, char *res);

int query_headername_by_uid(const char *uid, char *header, char *name);

int query_alluserinfo_by_uid(const char *uid, wex_entity_user *user);

#endif // WEX_QUERY_H_INCLUDED
