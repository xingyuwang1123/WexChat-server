#ifndef WEX_LOGIC_GROUP_H_INCLUDED
#define WEX_LOGIC_GROUP_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

int creategroupbyuid_processer(char *content, size_t length, char *res, size_t res_length);

int getgroupinfobyid_processer(char *content, size_t length, char *res, size_t res_length);

int doapplygroup_processer(char *content, size_t length, char *res, size_t res_length);

int getallgroupsbyuid_processer(char *content, size_t length, char *res, size_t res_length);

int getallgroupmemberbugid_processer(char *content, size_t length, char *res, size_t res_length);

int getallgroupapplyuserbygid_processer(char *content, size_t length, char *res, size_t res_length);

int rejectgroupapply_processer(char *content, size_t length, char *res, size_t res_length);

int acceptgroupapply_processer(char *content, size_t length, char *res, size_t res_length);

int quitgroupbyid_processer(char *content, size_t length, char *res, size_t res_length);

int cleargroupbyid_processer(char *content, size_t length, char *res, size_t res_length);

#endif // WEX_LOGIC_GROUP_H_INCLUDED
