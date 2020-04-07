#include "wex_entity.h"
#include "wex_data_constraints.h"
#include <stdlib.h>

wex_entity_user *wex_entity_user_alloc() {
    wex_entity_user *res = malloc(sizeof(wex_entity_user));
    res->uid = malloc(MAX_SHORT_STRING_LENGTH * sizeof(char));
    res->uid[0] = '\0';
    res->username = malloc(MAX_SHORT_STRING_LENGTH * sizeof(char));
    res->username[0] = '\0';
    res->password = malloc(MAX_SHORT_STRING_LENGTH * sizeof(char));
    res->password[0] = '\0';
    res->address_c = malloc(MAX_SHORT_STRING_LENGTH * sizeof(char));
    res->address_c[0] = '\0';
    res->address_p = malloc(MAX_SHORT_STRING_LENGTH * sizeof(char));
    res->address_p[0] = '\0';
    res->cutin = malloc(MAX_SHORT_STRING_LENGTH * sizeof(char));
    res->cutin[0] = '\0';
    res->email = malloc(MAX_SHORT_STRING_LENGTH * sizeof(char));
    res->email[0] = '\0';
    res->header = malloc(MAX_SHORT_STRING_LENGTH * sizeof(char));
    res->header[0] = '\0';
    res->introduction = malloc(MAX_SHORT_STRING_LENGTH * sizeof(char));
    res->introduction[0] = '\0';
    res->nickname = malloc(MAX_SHORT_STRING_LENGTH * sizeof(char));
    res->nickname[0] = '\0';
    res->note = malloc(MAX_SHORT_STRING_LENGTH * sizeof(char));
    res->note[0] = '\0';
    //res->password = malloc(MAX_SHORT_STRING_LENGTH * sizeof(char));
    res->phone_number = malloc(MAX_SHORT_STRING_LENGTH * sizeof(char));
    res->phone_number[0] = '\0';
    res->birthtime = 0;
    res->created_at = 0;
    return res;
}

void wex_entity_user_free(wex_entity_user *user) {
    free(user->uid);
    free(user->username);
    free(user->password);
    free(user->address_c);
    free(user->address_p);
    free(user->cutin);
    free(user->email);
    free(user->header);
    free(user->introduction);
    free(user->nickname);
    free(user->note);
    free(user->phone_number);
    free(user);
}
