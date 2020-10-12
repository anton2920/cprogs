#ifndef LAB_DEV_HASH_MAP_H
#define LAB_DEV_HASH_MAP_H

/* Header inclusion */
#include <stddef.h>


/* New value types */
struct DataItem {
    char *key;
    int value;
};

typedef struct DataItem *hashMap;

/* Functions' declarations */
struct DataItem *search(const hashMap *map, size_t size, const char *key);
void insert(hashMap *map, size_t size, char *key, int data);
void cleanMap(hashMap *map, size_t size);

#endif
