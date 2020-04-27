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

wex_entity_frienditem *wex_entity_frienditem_alloc() {
    wex_entity_frienditem *item = malloc(sizeof(wex_entity_frienditem));
    item->uid = malloc(sizeof(char) * MAX_UID_LENGTH);
    item->username = malloc(sizeof(char) * MAX_SHORT_STRING_LENGTH);
    item->username[0] = '\0';
    item->header = malloc(sizeof(char) * MAX_SHORT_STRING_LENGTH);
    item->header[0] = '\0';
    item->cutin = malloc(sizeof(char) * MAX_SHORT_STRING_LENGTH);
    item->cutin[0] = '\0';
    return item;
}

wex_entity_applyitem *wex_entity_applyitem_alloc() {
    wex_entity_applyitem *item = malloc(sizeof(wex_entity_applyitem));
    item->header = malloc(sizeof(char) * MAX_SHORT_STRING_LENGTH);
    item->header[0] = '\0';
    item->name = malloc(sizeof(char) * MAX_SHORT_STRING_LENGTH);
    item->name[0] = '\0';
    item->uid = malloc(sizeof(char) * MAX_UID_LENGTH);
    item->uid[0] = '\0';
    item->applyinfo = malloc(sizeof(char) * MAX_SHORT_STRING_LENGTH);
    item->applyinfo[0] = '\0';
    return item;
}

wex_entity_msgitem *wex_entity_msgitem_alloc() {
    wex_entity_msgitem *item = malloc(sizeof(wex_entity_msgitem));
    item->text = malloc(sizeof(char) * MAX_SHORT_STRING_LENGTH);
    item->text[0] = '/0';
    item->fromuid = malloc(sizeof(char) * MAX_UID_LENGTH);
    item->fromuid[0] = '/0';
    item->area = malloc(sizeof(char) * MAX_UID_LENGTH);
    item->area[0] = '/0';
    return item;
}

wex_entity_groupitem *wex_entity_groupitem_alloc() {
    wex_entity_groupitem *item = malloc(sizeof(wex_entity_groupitem));
    item->header[0] = '/0';
    item->name[0] = '/0';
    item->masteruid[0] = '/0';
    item->intro[0] = '/0';
    return item;
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

void wex_entity_frienditem_free(wex_entity_frienditem *frienditem) {
    free(frienditem->uid);
    free(frienditem->username);
    free(frienditem->header);
    free(frienditem->cutin);
    free(frienditem);
}

void wex_entity_applyitem_free(wex_entity_applyitem *item) {
    free(item->applyinfo);
    free(item->header);
    free(item->name);
    free(item->uid);
    free(item);
}

void wex_entity_msgitem_free(wex_entity_msgitem *item) {
    free(item->area);
    free(item->fromuid);
    free(item->text);
    free(item);
}

void wex_entity_groupitem_free(wex_entity_groupitem *item) {
    free(item);
}
