#include "wex_logic_interface.h"
#include "wex_data_constraints.h"
#include "wex_logic_user.h"
#include <stdlib.h>


char *wex_logic_doenter(const char *method, char *content, size_t length, int socket) {
    char *res = malloc(sizeof(char) * ORIGINAL_CONTENT_LENGTH);
    res[0] = '\0';
    //expand here
    if (!strncmp(method, "login", MAX_METHODNAME_LENGTH)) {
        int ret = login_processer(content, length, res, ORIGINAL_CONTENT_LENGTH, socket);
    }
    else if (!strncmp(method, "register", MAX_METHODNAME_LENGTH)) {
        int ret = register_processer(content, length, res, ORIGINAL_CONTENT_LENGTH);
    }
    else if (!strncmp(method, "getheadername", MAX_METHODNAME_LENGTH)) {
        getheadername_processer(content, length, res, ORIGINAL_CONTENT_LENGTH);
    }
    else if (!strncmp(method, "getalluserinfo", MAX_METHODNAME_LENGTH)) {
        getalluserinfo_processer(content, length, res, ORIGINAL_CONTENT_LENGTH);
    }
    else if (!strncmp(method, "updateinfobyuid", MAX_METHODNAME_LENGTH)) {
        updateinfobyuid_processer(content, length, res, ORIGINAL_CONTENT_LENGTH);
    }
    else if (!strncmp(method, "getcutinbyuid", MAX_METHODNAME_LENGTH)) {
        getcutinbyuid_processer(content, length, res, ORIGINAL_CONTENT_LENGTH);
    }
    else if (!strncmp(method, "getallfriendsbyuid", MAX_METHODNAME_LENGTH)) {
        getallfriendsbyuid_processer(content, length, res, ORIGINAL_CONTENT_LENGTH);
    }
    else if (!strncmp(method, "updatecutinbyuid", MAX_METHODNAME_LENGTH)) {
        updatecutinbyuid_processer(content, length, res, ORIGINAL_CONTENT_LENGTH);
    }
    else if (!strncmp(method, "applyfriend", MAX_METHODNAME_LENGTH)) {
        applyfriend_processer(content, length, res, ORIGINAL_CONTENT_LENGTH);
    }
    else if (!strncmp(method, "getallapply", MAX_METHODNAME_LENGTH)) {
        getallapply_processer(content, length, res, ORIGINAL_CONTENT_LENGTH);
    }
    else if (!strncmp(method, "rejectapply", MAX_METHODNAME_LENGTH)) {
        rejectapply_processer(content, length, res, ORIGINAL_CONTENT_LENGTH);
    }
    else if (!strncmp(method, "acceptapply", MAX_METHODNAME_LENGTH)) {
        acceptapply_processer(content, length, res, ORIGINAL_CONTENT_LENGTH);
    }
    else if (!strncmp(method, "deletefriend", MAX_METHODNAME_LENGTH)) {
        deletefriend_processer(content, length, res, ORIGINAL_CONTENT_LENGTH);
    }
    else if (!strncmp(method, "changeheaderbyuid", MAX_METHODNAME_LENGTH)) {
        changeheaderbyuid_processer(content, length, res, ORIGINAL_CONTENT_LENGTH);
    }
    else if (!strncmp(method, "sendmessagetouser", MAX_METHODNAME_LENGTH)) {
        sendmessagetouser_processer(content, length, res, ORIGINAL_CONTENT_LENGTH, socket);
    }
    return res;
}
