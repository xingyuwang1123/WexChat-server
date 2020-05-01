#ifndef WEX_QUERY_H_INCLUDED
#define WEX_QUERY_H_INCLUDED

#include "wex_entity.h"
#include "wex_list.h"

int register_query(wex_entity_user *user);

int login_query(const char *username, const char *password, int *res);

int query_id_by_username(const char *username, const char *password, char *res);

int query_headername_by_uid(const char *uid, char *header, char *name);

int query_alluserinfo_by_uid(const char *uid, wex_entity_user *user);

int update_userinfo_by_uid(wex_entity_user *user);

int update_header_by_uid(const char *uid, const char *header);

int query_cutin_by_uid(const char *uid, char *cutin);

int query_allfriends_by_uid(const char *uid, T_NODE *friend_head);

int update_cutin_by_uid(const char *uid, const char *cutin);

int create_apply_query(const char *fromuid, const char *touid, const char *applyinfo);

int query_allapply_by_uid(const char *uid, T_NODE *apply_list);

int delete_friends_apply(const char *fromuid, const char *touid);

int create_friends_query(const char *fromuid, const char *touid, const char *cutin);

int delete_friends_query(const char *fromuid, const char *touid);

int create_message_query(wex_entity_msgitem *item);

int create_group_query(wex_entity_groupitem *item);

int query_groupinfo_by_id(const char *gid, wex_entity_groupitem *item);

int create_groupapply_query(const char *gid, const char *uid, const char *appinfo);

int query_allgroupinfo_by_uid(const char *uid, T_NODE *head);

int query_all_groupmember_by_id(const char *gid, T_NODE *head);

int query_groupmember_uid_by_id(const char *gid, T_NODE *head);

int query_all_groupapplyuser_by_id(const char *gid, T_NODE *head);

int delete_group_apply_by_id(const char *gid, const char *uid);

int accept_group_apply_by_id(const char *gid, const char *uid);

int delete_groupmember_by_id(const char *gid, const char *uid);

int delete_group_by_id(const char *gid, const char *uid);



#endif // WEX_QUERY_H_INCLUDED
