#ifndef WEX_LIST_H_INCLUDED
#define WEX_LIST_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

//创建一个结构体表示链表中的节点
typedef struct node
{
	struct node *link;//指针域，注意这里类型是node，而不是T_NODE
	void *var;//数据域
}T_NODE;

typedef void (*var_deleter)(void *ptr);

//初始化一个链表，并将第一个值传入(有的实现头结点不插入数据,自己选择)
T_NODE *list_init(void *var);

void print_list(    T_NODE *list_head);

//计算链表的长度
int list_lenth(T_NODE *list_head);

//单个数据插入，尾插法
int list_tail_insert(T_NODE *list_head,void *var);

//单个数据插入，头插法
T_NODE *list_head_insert(T_NODE *list_head,void *var);

//指定位置插入,可以插入头，尾，或者头尾之间任意位置
T_NODE *list_specific_insert(T_NODE *list_head,int location,void *var);

//从链表头开始删除整个链表
T_NODE *del_list(T_NODE *list_head, var_deleter deleter);

//修改链表中的指定元素值
void change_specific_var(T_NODE *list_head,void *old_var,void *new_var, var_deleter deleter);

//删除链表中的指定元素值
T_NODE * del_specific_var(T_NODE *list_head,void *del_var, var_deleter deleter);

#endif // WEX_LIST_H_INCLUDED
