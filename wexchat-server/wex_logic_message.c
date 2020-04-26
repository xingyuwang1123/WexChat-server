#include "wex_logic_message.h"
#include "wexlog.h"
#include "cJSON.h"
#include "wex_entity.h"
#include "wex_query.h"
#include "wex_data_constraints.h"
#include "wex_userlist.h"

int sendmessagetouser_processer(char *content, size_t length, char *res, size_t res_length, int socket) {
    //user offline
         //parse message
    cJSON *json = cJSON_Parse(content);
    if (json == NULL) {
        wexlog(wex_log_warning, "error in parsing json");
        return -1;
    }
    cJSON *textj = cJSON_GetObjectItem(json, "text");
    cJSON *fromuidj = cJSON_GetObjectItem(json, "fromuid");
    cJSON *areaj = cJSON_GetObjectItem(json, "area");
    cJSON *typej = cJSON_GetObjectItem(json, "type");
    cJSON *msgtimej = cJSON_GetObjectItem(json, "msgtime");
    //test if user online
    int retsock = -1;
    if ((retsock = wex_find_userlist(areaj->valuestring)) < 0) {
        wex_entity_msgitem *item = wex_entity_msgitem_alloc();
        strncpy(item->text, textj->valuestring, MAX_SHORT_STRING_LENGTH);
        strncpy(item->fromuid, fromuidj->valuestring, MAX_UID_LENGTH);
        strncpy(item->area, areaj->valuestring, MAX_UID_LENGTH);
        item->msgtime = msgtimej->valueint;
        item->type= typej->valueint;
        int ret = create_message_query(item);
        if (ret < 0) {
            strcpy(res, "failed");
        }
        else {
            strcpy(res, "ok");
        }
        wex_entity_msgitem_free(item);
        cJSON_Delete(json);
    }
    else {
        //user online
        char buf[ORIGINAL_CONTENT_LENGTH];

        sprintf(buf, "BRO 00 WEX/1.0 %d \n%s", length, content);
        int slen = strlen(buf);
        int ret = write(retsock, buf, slen);
        if (ret != slen) {
            wexlog(wex_log_error_with_perror, "err in writing in message");
            strcpy(res, "failed");
        }
        else {
            strcpy(res, "ok");
        }
    }


    return 0;
}
