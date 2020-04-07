#ifndef WEX_LOGIC_USER
#define WEX_LOGIC_USER
#include <stdio.h>
#include <stdlib.h>

int login_processer(char *content, size_t length, char *res, size_t res_length);

int register_processer(char *content, size_t length, char *res, size_t res_length);

int getheadername_processer(char *content, size_t length, char *res, size_t res_length);

int getalluserinfo_processer(char *content, size_t length, char *res, size_t res_length);

int updateinfobyuid_processer(char *content, size_t length, char *res, size_t res_length);

#endif
