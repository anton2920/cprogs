#ifndef LAB_DEV_HASH_MAP_H
#define LAB_DEV_HASH_MAP_H

/* Header inclusion */
#include <stddef.h>

#include "libs.h"

/* New value types */
struct DataItem {
    char *key;
    lexema_t *value;
};

typedef struct DataItem *hashMap;

/* Functions' declarations */
struct DataItem *hash_search(const hashMap *hashArray, size_t size, const char *key);
void hash_insert(hashMap *hashArray, size_t size, const char *key, lexema_t *data);
void hash_cleanup(hashMap *map, size_t size);

#endif
