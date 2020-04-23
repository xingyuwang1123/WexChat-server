#include "wex_userlist.h"
#include "wexlog.h"

T_NODE *user_table = NULL;

void item_deleter(wex_user_list_entity *item) {
    if (item != NULL) {
        free(item);
    }
}

int wex_init_userlist() {
    user_table = list_init(0);
    return 0;
}

int wex_add_userlist(const char *uid, int descripter) {
    wex_user_list_entity *item = malloc(sizeof(wex_user_list_entity));
    strncpy(item->uid, uid, MAX_UID_LENGTH);
    item->descripter = descripter;
    list_tail_insert(user_table, item);
    return 0;
}

int wex_remove_userlist_byuid(const char *uid) {
    T_NODE *temp = user_table;
    while (temp->link) {
        temp = temp->link;
        wex_user_list_entity *item = temp->var;
        if (!strncmp(item->uid, uid, MAX_UID_LENGTH)) {
            del_specific_var(user_table, item, &item_deleter);
            return 0;
        }
    }
    return -1;
}

int wex_remove_userlist_bydesc(int desc) {
    T_NODE *temp = user_table;
    while (temp->link) {
        temp = temp->link;
        wex_user_list_entity *item = temp->var;
        if (item->descripter == desc) {
            del_specific_var(user_table, item, &item_deleter);
            return 0;
        }
    }
    return -1;
}

int wex_find_userlist(const char *uid) {
    T_NODE *temp = user_table;
    while (temp->link) {
        temp = temp->link;
        wex_user_list_entity *item = temp->var;
        if (!strncmp(item->uid, uid, MAX_UID_LENGTH)) {
            //del_specific_var(user_table, item, &item_deleter);
            return item->descripter;
            return 0;
        }
    }
    return -1;
}

void print_userlist() {
    T_NODE *temp = user_table;
    while (temp->link) {
        temp = temp->link;
        wex_user_list_entity *item = temp->var;
        char buf[256];
        sprintf(buf, "uid:%s, desc:%d", item->uid, item->descripter);
        wexlog(wex_log_debug, buf);
    }
}

//int main() {
//    wex_init_userlist();
//    wex_add_userlist("45", 1);
//    wex_add_userlist("46", 2);
//    wex_add_userlist("47", 3);
//    wex_add_userlist("48", 4);
//    print_userlist();
//    wex_remove_userlist_bydesc(1);
//    wex_remove_userlist_byuid("46");
//    print_userlist();
//    char buf[20];
//    sprintf(buf, "ok:%d", wex_find_userlist("47"));
//    wexlog(wex_log_debug, buf);
//    return 0;
//}
