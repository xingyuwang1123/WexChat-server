#include <stdio.h>
#include "wex_neo4j_connctor.h"
#include "wex_query.h"
#include "wexlog.h"
#include "wex_data_constraints.h"


struct midway1{
    char *name;
    char *header;
};
//parser here
void login_parser(neo4j_result_stream_t *results, void *result) {
    unsigned int count = neo4j_nfields(results);
    int *result2 = (int *)result;
    neo4j_result_t *res = neo4j_fetch_next(results);
    if (result == NULL) {
        wexlog(wex_log_warning, "failed to fetch result");
        return;
    }
    neo4j_value_t value = neo4j_result_field(res, 0);
    *result2 = neo4j_int_value(value);
}


void id_by_username_parser(neo4j_result_stream_t *results, void *result) {
    char *result2 = (char *)result;
    neo4j_result_t *res = neo4j_fetch_next(results);
    if (result == NULL) {
        wexlog(wex_log_warning, "failed to fetch result");
        return;
    }
    neo4j_value_t value = neo4j_result_field(res, 0);
    int ivalue = neo4j_int_value(value);
    sprintf(result2, "%d", ivalue);
}

void getheadername_parser(neo4j_result_stream_t *results, void *result) {
    struct midway1 *result2 = (struct midway1 *)result;
    neo4j_result_t *res = neo4j_fetch_next(results);
    if (result == NULL) {
        wexlog(wex_log_warning, "failed to fetch result");
        return;
    }
    neo4j_value_t value = neo4j_result_field(res, 0);
    neo4j_value_t value2 = neo4j_result_field(res, 1);
    char temp[MAX_SHORT_STRING_LENGTH];
    neo4j_string_value(value, temp, MAX_SHORT_STRING_LENGTH);
    strncpy(result2->header, temp, MAX_SHORT_STRING_LENGTH);
    neo4j_string_value(value2, temp, MAX_SHORT_STRING_LENGTH);
    strncpy(result2->name, temp, MAX_SHORT_STRING_LENGTH);
}

void getalluserinfo_parser(neo4j_result_stream_t *results, void *result) {
    wex_entity_user *user = (wex_entity_user *)result;
    neo4j_result_t *res = neo4j_fetch_next(results);
    if (result == NULL) {
        wexlog(wex_log_warning, "failed to fetch result");
        return;
    }
    neo4j_value_t username_value = neo4j_result_field(res, 0);
    neo4j_value_t nickname_value = neo4j_result_field(res, 1);
    neo4j_value_t header_value = neo4j_result_field(res, 2);
    neo4j_value_t birthtime_value = neo4j_result_field(res, 3);
    neo4j_value_t introduction_value = neo4j_result_field(res, 4);
    neo4j_value_t mail_value = neo4j_result_field(res, 5);
    neo4j_value_t number_value = neo4j_result_field(res, 6);
    neo4j_value_t address_p_value = neo4j_result_field(res, 7);
    neo4j_value_t address_c_value = neo4j_result_field(res, 8);
    neo4j_value_t note_value = neo4j_result_field(res, 9);
    neo4j_value_t created_at_value = neo4j_result_field(res, 10);
    neo4j_value_t cutin_value = neo4j_result_field(res, 11);
    //insert
    if (user != NULL) {
        char temp[MAX_SHORT_STRING_LENGTH];
        neo4j_string_value(username_value, temp, MAX_SHORT_STRING_LENGTH);
        strncpy(user->username, temp, MAX_SHORT_STRING_LENGTH);
        neo4j_string_value(nickname_value, temp, MAX_SHORT_STRING_LENGTH);
        strncpy(user->nickname, temp, MAX_SHORT_STRING_LENGTH);
        neo4j_string_value(header_value, temp, MAX_SHORT_STRING_LENGTH);
        strncpy(user->header, temp, MAX_SHORT_STRING_LENGTH);
        user->birthtime = neo4j_int_value(birthtime_value);
        neo4j_string_value(introduction_value, temp, MAX_SHORT_STRING_LENGTH);
        strncpy(user->introduction, temp, MAX_SHORT_STRING_LENGTH);
        neo4j_string_value(mail_value, temp, MAX_SHORT_STRING_LENGTH);
        strncpy(user->email, temp, MAX_SHORT_STRING_LENGTH);
        neo4j_string_value(number_value, temp, MAX_SHORT_STRING_LENGTH);
        strncpy(user->phone_number, temp, MAX_SHORT_STRING_LENGTH);
        neo4j_string_value(address_p_value, temp, MAX_SHORT_STRING_LENGTH);
        strncpy(user->address_p, temp, MAX_SHORT_STRING_LENGTH);
        neo4j_string_value(address_c_value, temp, MAX_SHORT_STRING_LENGTH);
        strncpy(user->address_c, temp, MAX_SHORT_STRING_LENGTH);
        neo4j_string_value(note_value, temp, MAX_SHORT_STRING_LENGTH);
        strncpy(user->note, temp, MAX_SHORT_STRING_LENGTH);
        user->created_at = neo4j_int_value(created_at_value);
        neo4j_string_value(cutin_value, temp, MAX_SHORT_STRING_LENGTH);
        strncpy(user->cutin, temp, MAX_SHORT_STRING_LENGTH);
    }
}

void query_cutin_by_uid_parser(neo4j_result_stream_t *results, void *result) {
    char *res = (char *)result;
    neo4j_result_t *nres = neo4j_fetch_next(results);
    if (nres == NULL) {
        wexlog(wex_log_warning, "failed to fetch result");
        return;
    }
    neo4j_value_t value = neo4j_result_field(nres, 0);
    neo4j_string_value(value, result, MAX_SHORT_STRING_LENGTH);
}

void query_allfriends_by_uid_parser(neo4j_result_stream_t *results, void *result) {
    T_NODE *head = (T_NODE*)result;
    neo4j_result_t *res = NULL;
    //char temp[MAX_SHORT_STRING_LENGTH];
    while(res = neo4j_fetch_next(results)) {
        neo4j_value_t value1 = neo4j_result_field(res, 0);
        neo4j_value_t value2 = neo4j_result_field(res, 1);
        neo4j_value_t value3 = neo4j_result_field(res, 2);
        neo4j_value_t value4 = neo4j_result_field(res, 3);
        wex_entity_frienditem *item = wex_entity_frienditem_alloc();
        sprintf(item->uid, "%d", neo4j_int_value(value1));
        neo4j_string_value(value2, item->username, MAX_SHORT_STRING_LENGTH);
        neo4j_string_value(value3, item->header, MAX_SHORT_STRING_LENGTH);
        neo4j_string_value(value4, item->cutin, MAX_SHORT_STRING_LENGTH);
        list_tail_insert(head, item);
    }
}

//query here
int register_query(wex_entity_user *user) {
    char statement[256];
    statement[0] = '\0';
    sprintf(statement, "create (n:User {username:'%s',nickname:'%s',header:'',birthtime:%d,introduction:'',email:'%s',phone_number:'%s',address_p:'',address_c:'',note:'',created_at:timestamp(),cutin:'',password:'%s'})", user->username, user->nickname, user->birthtime, user->email, user->phone_number, user->password);
    int ret = wex_neo4j_do_query(statement);
    if (ret < 0) {
        wexlog(wex_log_warning, "query:error  in querying neo4j");
        return -1;
    }
    return 0;
}

int login_query(const char *username, const char *password, int *res) {
    char statement[256];
    statement[0] = '\0';
    sprintf(statement, "match (n:User {username:'%s',password:'%s'}) return count(n)", username, password);
    int ret = wex_neo4j_do_query_with_result(statement, res, &login_parser);
    if (ret < 0) {
        wexlog(wex_log_warning, "query:error  in querying neo4j");
        return -1;
    }
    return 0;
}

int query_id_by_username(const char *username, const char *password, char *res) {
    char statement[256];
    statement[0] = '\0';
    sprintf(statement, "match (n:User {username:'%s',password:'%s'}) return id(n)", username, password);
    int ret = wex_neo4j_do_query_with_result(statement, res, &id_by_username_parser);
    if (ret < 0) {
        wexlog(wex_log_warning, "query:error  in querying neo4j");
        return -1;
    }
    return 0;
}

int query_headername_by_uid(const char *uid, char *header, char *name) {
    char statement[256];
    statement[0] = '\0';
    sprintf(statement, "match (n:User) where id(n)=%s return n.header, n.nickname", uid);
    struct midway1 midway1;
    midway1.name = name;
    midway1.header = header;
    int ret = wex_neo4j_do_query_with_result(statement, &midway1, &getheadername_parser);
    if (ret < 0) {
        wexlog(wex_log_warning, "query:error  in querying neo4j");
        return -1;
    }
    return 0;
}

int query_alluserinfo_by_uid(const char *uid, wex_entity_user *user) {
    char statement[256];
    statement[0] = '\0';
    sprintf(statement, "match (n:User) where id(n)=%s return n.username,n.nickname,n.header,n.birthtime, n.introduction, n.email, n.phone_number, n.address_p, n.address_c, n.note,n.created_at, n.cutin", uid);
    int ret = wex_neo4j_do_query_with_result(statement, user, &getalluserinfo_parser);
    if (ret < 0) {
        wexlog(wex_log_warning, "query:error  in querying neo4j");
        return -1;
    }
    return 0;
}

int update_userinfo_by_uid(wex_entity_user *user) {
    char statement[256];
    statement[0] = '\0';
    sprintf(statement, "match (n:User) where id(n)=%s set n.nickname='%s',n.birthtime=%d,n.email='%s',n.address_c = '%s',n.address_p='%s',n.note='%s',n.introduction='%s'", user->uid, user->nickname, user->birthtime, user->email, user->address_p, user->address_c, user->note, user->introduction);
    int ret = wex_neo4j_do_query(statement);
    if (ret < 0) {
        wexlog(wex_log_warning, "query:error  in querying neo4j");
        return -1;
    }
    return 0;
}

int query_cutin_by_uid(const char *uid, char *cutin) {
    char statement[256];
    statement[0] = '\0';
    sprintf(statement, "match (n:User) where id(n)=%s return n.cutin", uid);
    int ret = wex_neo4j_do_query_with_result(statement, cutin, &query_cutin_by_uid_parser);
    if (ret < 0) {
        wexlog(wex_log_warning, "query:error  in querying neo4j");
        return -1;
    }
    return 0;
}

int query_allfriends_by_uid(const char *uid, T_NODE *friend_head) {
    char statement[256];
    statement[0] = '\0';
    sprintf(statement, "match (n:User)-[r1:FRIENDS]->(m:User) where id(n)=%s return id(m),m.username,m.header,r1.cutin", uid);
    int ret = wex_neo4j_do_query_with_result(statement, friend_head, &query_allfriends_by_uid_parser);
    if (ret < 0) {
        wexlog(wex_log_warning, "query:error  in querying neo4j");
        return -1;
    }
    return 0;
}

int update_cutin_by_uid(const char *uid, const char *cutin) {
    char statement[256];
    statement[0] = '\0';
    sprintf(statement, "match (n:User) where id(n)=%s set n.cutin = '%s'", uid, cutin);
    int ret = wex_neo4j_do_query(statement);
    if (ret < 0) {
        wexlog(wex_log_warning, "query:error  in querying neo4j");
        return -1;
    }
    return 0;
}

//int main () {
//    int ret = wex_neo4j_connect_to_server("127.0.0.1", "7687", "neo4j", "137730");
//    if (ret < 0) {
//        printf("error\n");
//        exit(0);
//    }
//    wex_entity_user *user = wex_entity_user_alloc();
//    user->birthtime = time(0);
//    user->created_at  = time(0);
//    strcpy(user->username, "test1");
//    strcpy(user->password, "123456");
//    strcpy(user->email, "287577487@qq.com");
//    strcpy(user->nickname, "wang");
//    strcpy(user->phone_number, "18795891335");
//    register_query(user);
//    wex_entity_user_free(user);
//    return 0;
//}
