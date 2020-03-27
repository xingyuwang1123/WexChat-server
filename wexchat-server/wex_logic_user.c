#include "wex_logic_user.h"
#include "wexlog.h"
#include "cJSON.h"
#include "wex_entity.h"
#include "wex_query.h"
#include "wex_data_constraints.h"

int login_processer(char *content, size_t length, char *res, size_t res_length) {
    cJSON *json = cJSON_Parse(content);
    if (json == NULL) {
        wexlog(wex_log_warning, "error in parsing json");
        return -1;
    }
    cJSON *username = cJSON_GetObjectItem(json, "username");
    cJSON *password = cJSON_GetObjectItem(json, "password");
    //wexlog(wex_log_debug, cJSON_Print(json));
    //strcpy(res, "ok");
    int *res2 = malloc(sizeof(int));
    int ret = login_query(username->valuestring, password->valuestring, res2);
    if (ret < 0) {
        strcpy(res, "failed");
    }
    else {
        if (*res2 == 0) {
            strcpy(res, "wrongup");
        }
        else if (*res2 == 1){
            strcpy(res, "ok");
        }
    }
    cJSON_Delete(json);
    return 0;
}

int register_processer(char *content, size_t length, char *res, size_t res_length) {
    cJSON *json = cJSON_Parse(content);
    if (json == NULL) {
        wexlog(wex_log_warning, "error in parsing json");
        return -1;
    }
    cJSON *username = cJSON_GetObjectItem(json, "username");
    cJSON *password = cJSON_GetObjectItem(json, "password");
    cJSON *phone = cJSON_GetObjectItem(json, "phone");
    cJSON *mail = cJSON_GetObjectItem(json, "mail");
    cJSON *nickname = cJSON_GetObjectItem(json, "nickname");
    //wexlog(wex_log_debug, cJSON_Print(json));
    wex_entity_user *user = wex_entity_user_alloc();
    strncpy(user->username, username->valuestring, MAX_SHORT_STRING_LENGTH);
    strncpy(user->password, password->valuestring, MAX_SHORT_STRING_LENGTH);
    strncpy(user->phone_number, phone->valuestring, MAX_SHORT_STRING_LENGTH);
    strncpy(user->email, mail->valuestring, MAX_SHORT_STRING_LENGTH);
    strncpy(user->nickname, nickname->valuestring, MAX_SHORT_STRING_LENGTH);
    int ret = register_query(user);
    if (ret < 0) {
        strcpy(res, "failed");
    }
    else {
        strcpy(res, "ok");
    }
    wex_entity_user_free(user);
    cJSON_Delete(json);
    return 0;
}
