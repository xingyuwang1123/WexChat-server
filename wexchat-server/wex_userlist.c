#include "wex_userlist.h"
#include "wex_data_constraints.h"

wex_uid_sock_map = NULL;
wex_sock_uid_map = NULL;

int wex_init_userlist() {
    wex_uid_sock_map = shashmap_init(hashcode_str, equals_str);
    wex_sock_uid_map = shashmap_init(hashcode_int, equals_int);
    if (!wex_uid_sock_map || !wex_sock_uid_map) {
        return -1;
    }
    return 0;
}

int wex_add_userlist(const char *uid, int descripter) {
    char *newid = malloc(MAX_UID_LENGTH * sizeof(char));
    strncpy(newid, uid, MAX_UID_LENGTH);
    char *des = malloc(sizeof(int));
    *des = descripter;
    shashmap_put(wex_uid_sock_map, newid, des);
    shashmap_put(wex_sock_uid_map, descripter, newid);
    return 0;
}

int wex_remove_userlist_byuid(const char *uid) {

}
