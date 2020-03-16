#include "wex_entity.h"
#include "wex_data_constraints.h"
#include <stdlib.h>

wex_entity_user *wex_entity_user_alloc(const char *name, const char *password) {
    wex_entity_user *res = malloc(sizeof(wex_entity_user));
    res->name = malloc(MAX_SHORT_STRING_LENGTH * sizeof(char));
    res->password = malloc(MAX_SHORT_STRING_LENGTH * sizeof(char));
    return res;
}

void wex_entity_user_free(wex_entity_user *user) {
    free(user->name);
    free(user->password);
    free(user);
}
