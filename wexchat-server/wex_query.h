#ifndef WEX_QUERY_H_INCLUDED
#define WEX_QUERY_H_INCLUDED

#include "wex_entity.h"

int register_query(wex_entity_user *user);

int login_query(const char *username, const char *password, int *res);

#endif // WEX_QUERY_H_INCLUDED
