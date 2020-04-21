#ifndef WEX_PROTOCOL_PARSER_H_INCLUDED
#define WEX_PROTOCOL_PARSER_H_INCLUDED

#include "wex_data_constraints.h"
#include <stdint.h>
#include <stdio.h>

typedef struct {
    char method_name[MAX_METHODNAME_LENGTH];
    char pro_name[MAX_PRONAME_LENGTH];
    char version[MAX_VERSIONONAME_LENGTH];
    uint16_t msg_length;
    size_t content_length;
    char *content;
}wex_protocol_request;

typedef struct {
    char code[MAX_CODE_LENGTH];
    char pro_name[MAX_PRONAME_LENGTH];
    char version[MAX_VERSIONONAME_LENGTH];
    uint16_t msg_length;
    size_t content_length;
    char *content;
}wex_protocol_response;

//fast wrong message
#define WEX_ERROR_MSG1 "RES 10 WEX/1.0 0 \n"
#define WEX_ERROR_MSG2 "RES 20 WEX/1.0 0 \n"
#define WEX_ERROR_MSG3 "RES 30 WEX/1.0 0 \n"

//fast message inform

#define WEX_MESSAGE_INFORM "BRO 00 WEX/1.0 \n"

/*
if flag is 0, set creq to NULL, and it will construct a request; or it will add buf to content.
return NULL if failed
*/
wex_protocol_request *wex_parse_request(char *buf, ssize_t len, int flag, wex_protocol_request *creq);

/*
length is content's string length, and contentlength is content's buf size , please alloc memory first, ti may be realloced in function.
*/
wex_protocol_response *wex_construct_response(const char *code, const char *pro_name, const char *version, uint16_t length, char *content, size_t content_length);

/*
=translate response into buf string.
*/
int wex_deparse_response(wex_protocol_response *res, char *buf, size_t buf_size);

void wex_free_request(wex_protocol_request *req);

void wex_free_response(wex_protocol_response *res);

#endif // WEX_PROTOCOL_PARSER_H_INCLUDED
