#include <stdio.h>
#include <stdlib.h>
#include "wexlog.h"
#include "wex_hashmap.h"

extern unsigned int hashcode_int(void *key) {
    int k = *(int*)key;
    return k < 0? 131 - k: 131 + k;
}

extern int equals_int(void *key1, void *key2) {
    int k1 = *(int*)key1;
    int k2 = *(int*)key2;
    return k1 == k2? 1: 0;
}

extern unsigned int hashcode_str(void *key) {
    unsigned int hashcode = 0;
    char *str = (char*)key;
    while (*str) {
        hashcode = (*str++) + (hashcode << 6) + (hashcode << 16) - hashcode;
    }
    hashcode &= 0x7FFFFFFF;
    return hashcode;
}

extern int equals_str(void *key1, void *key2) {
    char *k1 = (char*)key1;
    char *k2 = (char*)key2;
    while (1) {
        if (*k1 != *k2) {
            return 0;
        }
        if (*k1) {
            break;
        }
    }
    return 1;
}

extern SHashMap *shashmap_init(unsigned int (*hashcode)(void *key),
        int (*equals)(void *key1, void *key2)) {

    SHashMap *map = malloc(sizeof(SHashMap));
    if (map == NULL) {
        perror("malloc shashmap error");
        exit(0);
    }
    map->hashcode = hashcode;
    map->equals = equals;
    map->size = 0;
    map->table_size = 131;
    map->table_array = calloc(map->table_size, sizeof(Entry));
    if (map->table_array == NULL) {
//        perror("calloc shashmap table array error");
//        exit(0);
        wexlog(wex_log_warning, "malloc entry error");
    }
    return map;
}

extern void shashmap_put(SHashMap *map, void *key, void *val) {

    int index = (*(map->hashcode))(key) % map->table_size;
    Entry *table = map->table_array + index;
    Entry *entry = malloc(sizeof(Entry));
    if (entry == NULL) {
//        perror("malloc entry error");
//        exit(0);
        wexlog(wex_log_warning, "malloc entry error");
    }
    entry->key = key;
    entry->val = val;
    entry->next = table->next;
    table->next = entry;
}

extern void *shashmap_get(SHashMap *map, void *key) {

    int index = (*(map->hashcode))(key) % map->table_size;
    Entry *entry = (map->table_array + index)->next;
    while (entry != NULL) {
        //int v =  ((*map->equals)(key, entry->key));
        //int v =  ((*map->equals)(key, entry->key));4
        int v = ((*map->equals)(key, entry->key));
        if ((*map->equals)(key, entry->key)) {
            return entry->val;
        }
        entry = entry->next;
    }
    return NULL;
}

extern void shashmap_free(SHashMap *map) {

    for (int i = 0; i < map->table_size; i++) {
        Entry *entry = (map->table_array + i)->next;
        while (entry != NULL) {
            Entry *temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp->val);
            free(temp);
        }
    }
    free(map->table_array);
    free(map);
}

//test main
//int main(int argc, char *argv[]) {
//    SHashMap *map = shashmap_init(hashcode_str, equals_str);
//    char *s1 = "asdfsfdsfsdf";
//    char *s2 = "adsfsdf56s165fs16516d5sf";
//    char *s3 = "adfasfe324324541313123123124";
//    shashmap_put(map, "MAX_THREAD_QUEUE_COUNT", s1);
//    shashmap_put(map, "MAX_THREAD_QUEUE_SIZE", s2);
//    shashmap_put(map, "SERVER_PORT", s3);
//    printf("res:%s\n", shashmap_get(map, "MAX_THREAD_QUEUE_COUNT"));
//    printf("res:%s\n", shashmap_get(map, "MAX_THREAD_QUEUE_SIZE"));
//    printf("res:%s\n", shashmap_get(map, "SERVER_PORT"));
//    shashmap_free(map);
//}

