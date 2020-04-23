#ifndef WEX_LOGIC_USER
#define WEX_LOGIC_USER
#include <stdio.h>
#include <stdlib.h>

int login_processer(char *content, size_t length, char *res, size_t res_length, int socket);

int register_processer(char *content, size_t length, char *res, size_t res_length);

int getheadername_processer(char *content, size_t length, char *res, size_t res_length);

int getalluserinfo_processer(char *content, size_t length, char *res, size_t res_length);

int updateinfobyuid_processer(char *content, size_t length, char *res, size_t res_length);

int getcutinbyuid_processer(char *content, size_t length, char *res, size_t res_length);

int getallfriendsbyuid_processer(char *content, size_t length, char *res, size_t res_length);

int updatecutinbyuid_processer(char *content, size_t length, char *res, size_t res_length);

int applyfriend_processer(char *content, size_t length, char *res, size_t res_length);

int getallapply_processer(char *content, size_t length, char *res, size_t res_length);

int rejectapply_processer(char *content, size_t length, char *res, size_t res_length);

int acceptapply_processer(char *content, size_t length, char *res, size_t res_length);

int deletefriend_processer(char *content, size_t length, char *res, size_t res_length);

int changeheaderbyuid_processer(char *content, size_t length, char *res, size_t res_length);

#endif
