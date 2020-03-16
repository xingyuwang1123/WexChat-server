#ifndef WEX_ENTITY_H_INCLUDED
#define WEX_ENTITY_H_INCLUDED

/*
here we define some data entity to transport data
*/

//ex:
typedef struct {
    char *name;
    char *password;
}wex_entity_user;

wex_entity_user *wex_entity_user_alloc(const char *name, const char *password);

void wex_entity_user_free(wex_entity_user *user);

#endif // WEX_ENTITY_H_INCLUDED
