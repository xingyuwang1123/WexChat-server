#ifndef WEX_HASHMAP_H_INCLUDED
#define WEX_HASHMAP_H_INCLUDED
/*
 * 求 int 型哈希值
 */
extern unsigned int hashcode_int(void *key);

/*
 * int 型指针比较
 */
extern int equals_int(void *key1, void *key2);

/*
 * 求 string 型哈系值
 */
extern unsigned int hashcode_str(void *key);

/*
 * string 型比较
 */
extern int equals_str(void *key1, void *key2);

/*
 * 哈希表节点结构定义
 */
typedef struct st_entry {
    void *key;    // key
    void *val;    // val
    struct st_entry *next; // 解决冲突/列表方式
} Entry;

/*
 * 哈希表结构定义
 */
typedef struct {

    int size;    // 当前有效大小
    int table_size;    // 哈系表数组大小
    Entry *table_array;    // 哈系表数组
    unsigned int (*hashcode)(void *key); // 键值哈希值函数
    int (*equals)(void *key1, void *key2); // 键比较函数
} SHashMap;

/*
 * 哈希表创建及初始化
 */
extern SHashMap *shashmap_init(unsigned int (*hashcode)(void *key),
        int (*equals)(void *key1, void *key2));

/*
 * 向哈希表添加键值对
 */
extern void shashmap_put(SHashMap *map, void *key, void *val);

/*
 * 根据键获取值
 */
extern void *shashmap_get(SHashMap *map, void *key);

/*
 * 销毁哈希表
 */
extern void shashmap_free(SHashMap *map);

#endif // WEX_HASHMAP_H_INCLUDED
