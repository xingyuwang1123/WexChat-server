#include "wex_logic_interface.h"
#include "wex_data_constraints.h"
#include "wex_logic_user.h"
#include <stdlib.h>


char *wex_logic_doenter(const char *method, char *content, size_t length) {
    char *res = malloc(sizeof(char) * ORIGINAL_CONTENT_LENGTH);
    res[0] = '\0';
    //expand here
    if (!strncmp(method, "login", MAX_METHODNAME_LENGTH)) {
        int ret = login_processer(content, length, res, ORIGINAL_CONTENT_LENGTH);
    }
    else if (!strncmp(method, "register", MAX_METHODNAME_LENGTH)) {
        int ret = register_processer(content, length, res, ORIGINAL_CONTENT_LENGTH);
    }
    return res;
}
