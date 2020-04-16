#ifndef WEX_ENTITY_H_INCLUDED
#define WEX_ENTITY_H_INCLUDED
#include <time.h>

/*
here we define some data entity to transport data
*/

//ex:
typedef struct {
    char *uid;
    char *username;
    char *password;
    char *nickname;
    char *header;
    time_t birthtime;
    char *introduction;
    char *email;
    char *phone_number;
    char *address_p;
    char *address_c;
    char *note;
    time_t created_at;
    char *cutin;
}wex_entity_user;

typedef struct {
    char *uid;
    char *username;
    char *header;
    char *cutin;
}wex_entity_frienditem;

//entity allocker
wex_entity_user *wex_entity_user_alloc();

wex_entity_frienditem *wex_entity_frienditem_alloc();
//entity freeder
void wex_entity_user_free(wex_entity_user *user);

void wex_entity_frienditem_free(wex_entity_frienditem *frienditem);

#endif // WEX_ENTITY_H_INCLUDED
