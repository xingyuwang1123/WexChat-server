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
    char *res3 = malloc(sizeof(char) * MAX_UID_LENGTH);
    int ret = login_query(username->valuestring, password->valuestring, res2);
    if (ret < 0) {
        strcpy(res, "loginfailed");
    }
    else {
        if (*res2 == 0) {
            strcpy(res, "loginwrongup");
        }
        else if (*res2 == 1){
            ret = query_id_by_username(username->valuestring, password->valuestring, res3);
            if (ret < 0) {
                strcpy(res, "loginfailed");
                goto error;
            }
            cJSON *json2 = cJSON_CreateObject();

            cJSON_AddItemToObject(json2, "result", cJSON_CreateString("ok"));
            cJSON_AddItemToObject(json2, "uid", cJSON_CreateString(res3));
            char *temp = cJSON_Print(json2);
            strncpy(res, temp, ORIGINAL_CONTENT_LENGTH);
            free(temp);
            cJSON_Delete(json2);
            //strcpy(res, "loginok");
        }
    }
error:    cJSON_Delete(json);
    free(res2);
    free(res3);
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
        strcpy(res, "registerfailed");
    }
    else {
        strcpy(res, "registerok");
    }
    wex_entity_user_free(user);
    cJSON_Delete(json);
    return 0;
}

int getheadername_processer(char *content, size_t length, char *res, size_t res_length) {
    char uid[MAX_UID_LENGTH];
    strncpy(uid, content, MAX_UID_LENGTH);
    char header[MAX_SHORT_STRING_LENGTH];
    char name[MAX_SHORT_STRING_LENGTH];
    int ret = query_headername_by_uid(uid, header, name);
    if (ret < 0) {
        strcpy(res, "failed");
    }
    else {
        cJSON *json = cJSON_CreateObject();
        cJSON *namej = cJSON_CreateString(name);
        cJSON *headerj = cJSON_CreateString(header);
        cJSON_AddItemToObject(json, "name", namej);
        cJSON_AddItemToObject(json, "header", headerj);
        char *temp = cJSON_Print(json);
        strncpy(res, temp, ORIGINAL_CONTENT_LENGTH);
        cJSON_Delete(json);
        free(temp);
    }
    return 0;
}

 int getalluserinfo_processer(char *content, size_t length, char *res, size_t res_length) {
    char uid[MAX_UID_LENGTH];
    strncpy(uid, content, MAX_UID_LENGTH);
    wex_entity_user *user = wex_entity_user_alloc();
    int ret = query_alluserinfo_by_uid(uid, user);
    if (ret < 0) {
        strcpy(res, "failed");
    }
    else {
        cJSON *json = cJSON_CreateObject();
        cJSON_AddItemToObject(json, "username", cJSON_CreateString(user->username));
        cJSON_AddItemToObject(json, "nickname", cJSON_CreateString(user->nickname));
        cJSON_AddItemToObject(json, "header", cJSON_CreateString(user->header));
        cJSON_AddItemToObject(json, "birthtime", cJSON_CreateNumber(user->birthtime));
        cJSON_AddItemToObject(json, "introduction", cJSON_CreateString(user->introduction));
        cJSON_AddItemToObject(json, "email", cJSON_CreateString(user->email));
        cJSON_AddItemToObject(json, "phone_number", cJSON_CreateString(user->phone_number));
        cJSON_AddItemToObject(json, "address_p", cJSON_CreateString(user->address_p));
        cJSON_AddItemToObject(json, "address_c", cJSON_CreateString(user->address_c));
        cJSON_AddItemToObject(json, "note", cJSON_CreateString(user->note));
        cJSON_AddItemToObject(json, "created_at", cJSON_CreateNumber(user->created_at));
        cJSON_AddItemToObject(json, "cutin", cJSON_CreateString(user->cutin));
        char *print_text = cJSON_PrintUnformatted(json);
        strncpy(res, print_text, ORIGINAL_CONTENT_LENGTH);
        cJSON_Delete(json);
    }

    wex_entity_user_free(user);
    return 0;
 }





