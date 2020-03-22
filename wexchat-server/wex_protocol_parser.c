#include "wex_protocol_parser.h"
#include <string.h>
#include <stdlib.h>

wex_protocol_request *wex_parse_request(char *buf, ssize_t len, int flag, wex_protocol_request *creq) {
    if (flag == 0) {
        char *token;
        char cpbuf[NETWORK_BUFF_SIZE];
        strncpy(cpbuf, buf, NETWORK_BUFF_SIZE);
        wex_protocol_request *req = malloc(sizeof(wex_protocol_request));
        //give up first string
        //token = strtok(cpbuf, " ");
        if ((token = strtok(cpbuf, " ")) != NULL) {
            strncpy(req->method_name, token, MAX_METHODNAME_LENGTH);
        }
        else {goto error;}
        if ((token = strtok(NULL, " ")) != NULL) {
            char *ptr = token;
            for (;*ptr != '\0';ptr++) {
                if (*ptr == '/') {
                    size_t n = (size_t)(ptr-token);
                    if (n < MAX_PRONAME_LENGTH) {
                        strncpy(req->pro_name, token, n);
                    }
                    if (ptr+1 != '\0') {
                        strncpy(req->version, ptr+1, MAX_VERSIONONAME_LENGTH);
                    }
                }
            }
        }
        else {goto error;}
        if ((token = strtok(NULL, " ")) != NULL) {
            uint16_t length = (uint16_t)atoi(token);
            req->msg_length = length;
        }
        else {goto error;}
        if ((token = strtok(NULL, " ")) != NULL) {
           if (*token != '\n') {goto error;}
        }
        else {goto error;}
        //content
        req->content = malloc(sizeof(char) * ORIGINAL_CONTENT_LENGTH);
        strncpy(req->content, token + 1, ORIGINAL_CONTENT_LENGTH);
        req->content_length = ORIGINAL_CONTENT_LENGTH;
        return req;
error:
        free(req);
        return NULL;
    }
    else {
        size_t slen = strlen(creq->content);
        while (len > (creq->content_length - slen)) {
            // no enough memory
            realloc(creq->content, creq->content_length * 2);
            creq->content_length = creq->content_length * 2;
        }
        strncat(creq->content, buf, len);
        return creq;
    }

}

wex_protocol_response *wex_construct_response(const char *code, const char *pro_name, const char *version, uint16_t length, char *content, size_t content_length) {
    wex_protocol_response *res = malloc(sizeof(wex_protocol_response));
    strncpy(res->code, code, MAX_CODE_LENGTH);
    strncpy(res->pro_name, pro_name, MAX_PRONAME_LENGTH);
    strncpy(res->version, version, MAX_VERSIONONAME_LENGTH);
    res->msg_length = length;
    res->content = content;
    res->content_length = content_length;
    return res;
}


void wex_free_request(wex_protocol_request *req) {
    free(req->content);
    free(req);
}

void wex_free_response(wex_protocol_response *res) {
    free(res->content);
    free(res);
}

int wex_deparse_response(wex_protocol_response *res, char *buf, size_t buf_size) {
    //char header[MAX_HEADER_LENGTH] = {'\0'};
    char *ptr = buf;
    buf[0] = '\0';
    strncat(buf, "RES ", 4);
    strncat(buf, res->code, MAX_CODE_LENGTH);
    strncat(buf, " ", 1);
    strncat(buf, res->pro_name, MAX_PRONAME_LENGTH);
    strncat(buf, "/", 1);
    strncat(buf, res->version, MAX_VERSIONONAME_LENGTH);
    strncat(buf, " ", 1);
    char temp[16];
    sprintf(temp, "%d", res->msg_length);
    strncat(buf, temp, 16);
    strncat(buf, " \n", 2);
    //content
    size_t slen = strlen(buf);
    while ((buf_size - slen) < res->msg_length) {
        realloc(buf, sizeof(char) * buf_size * 2);
        buf_size = buf_size * 2;
    }
    strncat(buf, res->content, res->msg_length);
    return slen;
}


//test cjson
//int main () {
//    wex_protocol_request *req = wex_parse_request("Method WEX/1.0 12 \n{asdasdasdafadewfffdsfsdcvsdzfc}", 0, 0,NULL);
//    printf("%s,%s,%s,%d,%s\n", req->method_name, req->pro_name, req->version, req->msg_length, req->content);
//    char *buf = "asdasfdsfvsv.....aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
//    wex_parse_request(buf, strlen(buf), 1, req);
//    printf("%s,%s,%s,%d,%s\n", req->method_name, req->pro_name, req->version, req->msg_length, req->content);
//    char *content = malloc(sizeof(char) * 128);
//    strncpy(content, "content", 128);
//    wex_protocol_response *res = wex_construct_response("00", "WEX", "1.0", 7, content, 128);
//    char buf2[NETWORK_BUFF_SIZE];
//    wex_deparse_response(res, buf2, NETWORK_BUFF_SIZE);
//    printf("%s", buf2);
//    //printf("%s\n", wex_deparse_response(res, ))
//    wex_free_request(req);
//    wex_free_response(res);
//    return 0;
//}
