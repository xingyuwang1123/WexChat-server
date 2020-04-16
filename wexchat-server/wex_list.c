#include "wex_list.h"
#include "wex_entity.h"



//初始化一个链表，并将第一个值传入(有的实现头结点不插入数据,自己选择)
T_NODE *list_init(void *var)
{
	//创建根节点
	T_NODE *head = (T_NODE *)malloc(sizeof(T_NODE));
	if(NULL == head)
	{
		printf("错误。申请内存失败，创建节点失败\n");
		exit(1);
	}

	//初始化头节点
	head->var = var;
	head->link = NULL;
	return head;
}

void print_list(T_NODE *list_head)
{
	int i =  0;
	if(NULL == list_head)
	{
		printf("链表为空\n");
		return;
	}

	//指针域为NULL，表示这是最后一个节点，但是该节点是有效节点，所以这里用do while
	do
	{
		printf("链表节点%d的值是：%p\n",++i,list_head->var);
		list_head = list_head->link;
	}while(list_head);
}

//计算链表的长度
int list_lenth(T_NODE *list_head)
{
	int lenth = 0;
	while(list_head)
	{
		lenth++;
		list_head = list_head->link;
	}
	return lenth;
}

//单个数据插入，尾插法
int list_tail_insert(T_NODE *list_head,void *var)
{
	T_NODE *list_new_node = (T_NODE *)malloc(sizeof(T_NODE));
	if(NULL == list_new_node)
	{
		printf("error,malloc failed\n");
		return -1;
	}

	while(list_head->link)
	{
		list_head = list_head->link;
	}

	list_new_node->var = var;//将值给该节点，并将上一个节点的指针域指向该节点地址
	list_new_node->link = NULL;
	list_head->link = list_new_node;

	return 0;
}

//单个数据插入，头插法
T_NODE *list_head_insert(T_NODE *list_head,void *var)
{
	T_NODE *list_new_node = (T_NODE *)malloc(sizeof(T_NODE));

	if(NULL == list_new_node)
	{
		printf("error,malloc failed\n");
		return NULL;
	}

	list_new_node->link = list_head;
	list_new_node->var = var;
	list_head = list_new_node;

	return list_head;
}

//指定位置插入,可以插入头，尾，或者头尾之间任意位置
T_NODE *list_specific_insert(T_NODE *list_head,int location,void *var)
{
	int len = list_lenth(list_head);
	int i = 1;//为保持人的习惯，第1个位置表示1而不是0
	T_NODE *node_last = NULL;
	T_NODE *node_temp = list_head;

	//位置是1，插在链表的开头，用头插法
	if(1 == location)
	{
		list_head = list_head_insert(list_head, var);
		return list_head;
	}

	//位置比链表长度大1，插在链表尾部
	if((len + 1 ) == location)
	{
		list_tail_insert(list_head, var);
		return list_head;
	}

	//指定的位置最大是链表长度加1，location=1表示头，location=len+1，表示插在尾部
	if((location > (len + 1)) ||(location < 1))
	{
		printf("插入失败。请检查链表长度，指定插入位置不对\n");
		return list_head;
	}

	//这里采用头插法插入，也可以采用尾插法
	while(i < location)
	{
		node_last = node_temp;
		node_temp = node_temp->link;
		i++;
	}

	node_temp = list_head_insert(node_temp, var);
	node_last->link = node_temp;

	return list_head;
}

//从链表头开始删除整个链表
T_NODE *del_list(T_NODE *list_head, var_deleter deleter)
{
	T_NODE *node_temp = NULL;
	int flag = 0;

	while(list_head->link)
	{
		node_temp = list_head->link;
		if (flag) deleter(list_head->var);
		free(list_head);
		list_head = node_temp;
		flag = 1;
	}
	if (flag) deleter(list_head->var);
	free(list_head);
    //list_head = NULL;
	//printf("整个删除链表成功\n");

	return NULL;
}

//修改链表中的指定元素值
void change_specific_var(T_NODE *list_head,void *old_var,void *new_var, var_deleter deleter)
{
	while (NULL != list_head)
	{
		if(old_var == list_head->var)
		{
            deleter(list_head->var);
			list_head->var = new_var;
			//printf("将%d修改为%d成功\n",old_var,new_var);
			return;
		}
		list_head = list_head->link;
	}
	printf("将%p修改为%p失败\n",old_var,new_var);
}

//删除链表中的指定元素值
T_NODE * del_specific_var(T_NODE *list_head,void *del_var, var_deleter deleter)
{
	T_NODE *list_temp = NULL;
	T_NODE *list_head_temp = list_head;

	while(NULL != list_head)
	{
		if(del_var == list_head->var)
		{
			//如果删除的是头结点
			if(NULL == list_temp)
			{
				list_temp = list_head;
				list_head = list_head->link;
                deleter(list_temp->var);
				free(list_temp);

				return list_head;
			}
			else//删除的不是头结点
			{
				list_temp->link = list_head->link;
				deleter(list_head->var);
				free(list_head);
				return list_head_temp;
			}
		}
		list_temp = list_head;
		list_head = list_head->link;
	}
	return list_head_temp;
}

//int main() {
//    wex_entity_frienditem *item = wex_entity_frienditem_alloc();
//    wex_entity_frienditem *item2 = wex_entity_frienditem_alloc();
//    wex_entity_frienditem *item3 = wex_entity_frienditem_alloc();
//    T_NODE *node = list_init(item);
//    list_tail_insert(node, item2);
//    list_tail_insert(node,  item3);
//    print_list(node);
//    del_list(node, &wex_entity_frienditem_free);
//    print_list(node);
//    return 0;
//}
