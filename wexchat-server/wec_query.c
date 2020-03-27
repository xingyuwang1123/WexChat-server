#include <stdio.h>
#include "wex_neo4j_connctor.h"
#include "wex_query.h"
#include "wexlog.h"

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
