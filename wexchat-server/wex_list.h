#ifndef WEX_LIST_H_INCLUDED
#define WEX_LIST_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
//typedef unsigned char uchar, byte, BYTE;
//typedef unsigned short uint16, word_t, ushort;
//typedef unsigned __int32 uint, uint32, dword_t, size_t;
//typedef unsigned long    ulong;
//typedef __int16 int16;
//typedef __int32 int32;
//typedef __int64 int64, longlong;
//typedef    long    lresult;
//typedef unsigned __int64 uint64, qword_t, ulonglong;
#ifndef BOOL
    typedef int     BOOL;
    #define TRUE  1
    #define FALSE 0
#endif

#ifndef RESULT
    #define RESULT        lresult
    #define _SUCCESS    0
    #define _ERROR        -1
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef INOUT
#define INOUT
#endif

#ifndef OPTIONAL
#define OPTIONAL
#endif

#define SIZE_BYTE    1
#define SIZE_ACHAR    1
#define SIZE_WCHAR    2
#define SIZE_SHORT    2
#define SIZE_INT    4
#define SIZE_LONG    4
#define SIZE_FLT    4
#define SIZE_DBL    8
#define SIZE_WORD    2
#define SIZE_DWORD    4
#define SIZE_QWORD    8
#define SIZE_LINT    8
#define SIZE_INT64    8
#define SIZE_UUID    16


typedef struct _listnode_t
{
    struct _listnode_t    *next;
    union{
        void*            data;
        struct _list_t    *list;
        const char        *str;
        long            key;
    };
}listnode_t;

typedef struct _list_t
{
    size_t        size;    /* count of nodes */
    listnode_t    *head;
    listnode_t  *tail;
}list_t, *list_p;

/* A prototype of callbacked function called by list_destroy(), NULL for no use. */
typedef void(*pfcb_list_node_free)(listnode_t* node);

/* An example of  node data function implemented by callee:
void my_list_node_(listnode_t *node)
{
    (node->data);
}
*/

/* Appends a node to a list */
extern void
list_append_node(list_t *in_list, listnode_t *in_node);

/* Removes the first node from a list and returns it */
extern listnode_t*
list_remove_head(list_t *in_list);

/* Removes all nodes but for list itself */
extern void
list_remove_all(list_t *in_list, pfcb_list_node_free pfunc /* NULL for no use or a key node */);

/* Returns a copy of a list_t from heap */
extern list_t*
list_copy(list_t in_list);

/* Concatenates two lists into first list. NOT ing the second */
extern void
list_concat(list_t *first, list_t *second);

/* Allocates a new listnode_t from heap. NO memory allocated for input node_data */
extern listnode_t*
list_node_create(void* node_data);

/* Allocates a new listnode_t with a key node type */
extern listnode_t*
list_key_create(long node_key);

/* Allocates a empty list_t from heap */
extern list_t*
list_create();

/* s in_list's all nodes and destroys in_list from heap.
 * the callee is responsible for ing node data.
 * the node d-function(pfunc) is called by list_destroy.
 */
extern void
list_destroy(list_t *in_list, pfcb_list_node_free pfunc /* NULL for no use or a key node */);

/* Gets count of nodes in the list */
extern size_t
list_size(const list_t* in_list);

/* Gets node by index 0-based. 0 is head */
extern listnode_t*
list_node_at(const list_t* in_list, int index);

#endif // WEX_LIST_H_INCLUDED
