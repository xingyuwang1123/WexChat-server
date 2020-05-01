#include "wex_logic_group.h"
#include "wexlog.h"
#include "cJSON.h"
#include "wex_entity.h"
#include "wex_query.h"
#include "wex_data_constraints.h"
#include "wex_userlist.h"

int creategroupbyuid_processer(char *content, size_t length, char *res, size_t res_length) {
    cJSON *json = cJSON_Parse(content);
    if (json == NULL) {
        wexlog(wex_log_warning, "error in parsing json");
        return -1;
    }
    cJSON *namej = cJSON_GetObjectItem(json, "name");
    cJSON *introj = cJSON_GetObjectItem(json, "intro");
    cJSON *headerj = cJSON_GetObjectItem(json, "header");
    cJSON *uidj = cJSON_GetObjectItem(json, "masteruid");
    wex_entity_groupitem *item = wex_entity_groupitem_alloc();
    strncpy(item->name, namej->valuestring, MAX_SHORT_STRING_LENGTH);
    strncpy(item->intro, introj->valuestring, MAX_SHORT_STRING_LENGTH);
    strncpy(item->header, headerj->valuestring, MAX_SHORT_STRING_LENGTH);
    strncpy(item->masteruid, uidj->valuestring, MAX_UID_LENGTH);
    int ret = create_group_query(item);
    if (ret < 0) {
        strcpy(res, "failed");
    }
    else {
        strcpy(res, "ok");
    }
    wex_entity_groupitem_free(item);
    cJSON_Delete(json);
    return 0;
}

int getgroupinfobyid_processer(char *content, size_t length, char *res, size_t res_length) {
    char gid[MAX_UID_LENGTH];
    strncpy(gid, content, MAX_UID_LENGTH);
    wex_entity_groupitem *item = wex_entity_groupitem_alloc();
    int ret = query_groupinfo_by_id(gid, item);
    if (ret < 0) {
        strcpy(res, "failed");
    }
    else {
        cJSON *json = cJSON_CreateObject();
        cJSON_AddItemToObject(json, "name", cJSON_CreateString(item->name));
        cJSON_AddItemToObject(json, "intro", cJSON_CreateString(item->intro));
        cJSON_AddItemToObject(json, "header", cJSON_CreateString(item->header));
        cJSON_AddItemToObject(json, "masteruid", cJSON_CreateString(item->masteruid));
        char *temp = cJSON_PrintUnformatted(json);
        strncpy(res, temp, ORIGINAL_CONTENT_LENGTH);
        free(temp);
        cJSON_Delete(json);
    }
    wex_entity_groupitem_free(item);
    return 0;
}

int doapplygroup_processer(char *content, size_t length, char *res, size_t res_length) {
    cJSON *json = cJSON_Parse(content);
    if (json == NULL) {
        wexlog(wex_log_warning, "error in parsing json");
        return -1;
    }
    cJSON *uidj = cJSON_GetObjectItem(json, "uid");
    cJSON *gidj = cJSON_GetObjectItem(json, "gid");
    cJSON *appinfoj = cJSON_GetObjectItem(json, "appinfo");
    int ret = create_groupapply_query(gidj->valuestring, uidj->valuestring, appinfoj->valuestring);
    if (ret < 0) {
        strcpy(res, "failed");
    }
    else {
        strcpy(res, "ok");
    }
    return 0;
}

int getallgroupsbyuid_processer(char *content, size_t length, char *res, size_t res_length) {
    char uid[MAX_UID_LENGTH];
    strncpy(uid, content, MAX_UID_LENGTH);
    T_NODE *head = list_init(0);
    int ret = query_allgroupinfo_by_uid(uid, head);
    if (ret < 0) {
        strcpy(res, "failed");
    }
    else {
        cJSON *arr = cJSON_CreateArray();
        T_NODE *temp = head;
        while (temp->link) {
            temp = temp->link;
            wex_entity_groupitem *item = (wex_entity_groupitem *)temp->var;
            cJSON *node = cJSON_CreateObject();
            cJSON_AddItemToObject(node, "name", cJSON_CreateString(item->name));
            cJSON_AddItemToObject(node, "header", cJSON_CreateString(item->header));
            cJSON_AddItemToObject(node, "intro", cJSON_CreateString(item->intro));
            cJSON_AddItemToObject(node, "gid", cJSON_CreateString(item->masteruid));
            cJSON_AddItemToObject(node, "tip", cJSON_CreateBool(item->tip));
            cJSON_AddItemToArray(arr, node);
        }
        char *tempbuf = cJSON_PrintUnformatted(arr);
        strncpy(res, tempbuf, ORIGINAL_CONTENT_LENGTH);
        free(tempbuf);
        free(arr);
    }
    del_list(head, &wex_entity_groupitem_free);
    return 0;
}

int getallgroupmemberbugid_processer(char *content, size_t length, char *res, size_t res_length) {
    char gid[MAX_UID_LENGTH];
    strncpy(gid, content, MAX_UID_LENGTH);
    T_NODE *head = list_init(0);
    int ret = query_all_groupmember_by_id(gid, head);
    if (ret < 0) {
        strcpy(res, "failed");
    }
    else {
         cJSON *arr = cJSON_CreateArray();
        T_NODE *temp = head;
        while (temp->link) {
            temp = temp->link;
            wex_entity_user *item = (wex_entity_user *)temp->var;
            cJSON *node = cJSON_CreateObject();
            cJSON_AddItemToObject(node, "uid", cJSON_CreateString(item->uid));
            cJSON_AddItemToObject(node, "name", cJSON_CreateString(item->nickname));
            cJSON_AddItemToObject(node, "header", cJSON_CreateString(item->header));
            cJSON_AddItemToArray(arr, node);
        }
        char *tempbuf = cJSON_PrintUnformatted(arr);
        strncpy(res, tempbuf, ORIGINAL_CONTENT_LENGTH);
        free(tempbuf);
        free(arr);
    }
    del_list(head, &wex_entity_user_free);
    return 0;
}

int getallgroupapplyuserbygid_processer(char *content, size_t length, char *res, size_t res_length) {
    char gid[MAX_UID_LENGTH];
    strncpy(gid, content, MAX_UID_LENGTH);
    T_NODE *head = list_init(0);
    int ret = query_all_groupapplyuser_by_id(gid, head);
    if (ret < 0) {
        strcpy(res, "failed");
    }
    else {
         cJSON *arr = cJSON_CreateArray();
        T_NODE *temp = head;
        while (temp->link) {
            temp = temp->link;
            wex_entity_user *item = (wex_entity_user *)temp->var;
            cJSON *node = cJSON_CreateObject();
            cJSON_AddItemToObject(node, "uid", cJSON_CreateString(item->uid));
            cJSON_AddItemToObject(node, "name", cJSON_CreateString(item->nickname));
            cJSON_AddItemToObject(node, "header", cJSON_CreateString(item->header));
            cJSON_AddItemToObject(node, "appinfo", cJSON_CreateString(item->introduction));
            cJSON_AddItemToArray(arr, node);
        }
        char *tempbuf = cJSON_PrintUnformatted(arr);
        strncpy(res, tempbuf, ORIGINAL_CONTENT_LENGTH);
        free(tempbuf);
        free(arr);
    }
    del_list(head, &wex_entity_user_free);
    return 0;
}

int rejectgroupapply_processer(char *content, size_t length, char *res, size_t res_length) {
    cJSON *json = cJSON_Parse(content);
    if (json == NULL) {
        wexlog(wex_log_warning, "error in parsing json");
        return -1;
    }
    cJSON *uidj = cJSON_GetObjectItem(json, "uid");
    cJSON *gidj = cJSON_GetObjectItem(json, "gid");
    int ret = delete_group_apply_by_id(gidj->valuestring, uidj->valuestring);
    if (ret < 0) {
        strcpy(res, "failed");
    }
    else {
        strcpy(res, "ok");
    }
    cJSON_Delete(json);
    return 0;
}

int acceptgroupapply_processer(char *content, size_t length, char *res, size_t res_length) {
    cJSON *json = cJSON_Parse(content);
    if (json == NULL) {
        wexlog(wex_log_warning, "error in parsing json");
        return -1;
    }
    cJSON *uidj = cJSON_GetObjectItem(json, "uid");
    cJSON *gidj = cJSON_GetObjectItem(json, "gid");
    int ret = accept_group_apply_by_id(gidj->valuestring, uidj->valuestring);
    if (ret < 0) {
        strcpy(res, "failed");
    }
    else {
        strcpy(res, "ok");
    }
    cJSON_Delete(json);
    return 0;
}

int quitgroupbyid_processer(char *content, size_t length, char *res, size_t res_length) {
    cJSON *json = cJSON_Parse(content);
    if (json == NULL) {
        wexlog(wex_log_warning, "error in parsing json");
        return -1;
    }
    cJSON *uidj = cJSON_GetObjectItem(json, "uid");
    cJSON *gidj = cJSON_GetObjectItem(json, "gid");
    int ret = delete_groupmember_by_id(gidj->valuestring, uidj->valuestring);
    if (ret < 0) {
        strcpy(res, "failed");
    }
    else {
        strcpy(res, "ok");
    }
    cJSON_Delete(json);
    return 0;
}

int cleargroupbyid_processer(char *content, size_t length, char *res, size_t res_length) {
    cJSON *json = cJSON_Parse(content);
    if (json == NULL) {
        wexlog(wex_log_warning, "error in parsing json");
        return -1;
    }
    cJSON *uidj = cJSON_GetObjectItem(json, "uid");
    cJSON *gidj = cJSON_GetObjectItem(json, "gid");
    int ret = delete_group_by_id(gidj->valuestring, uidj->valuestring);
    if (ret < 0) {
        strcpy(res, "failed");
    }
    else {
        strcpy(res, "ok");
    }
    cJSON_Delete(json);
    return 0;
}
