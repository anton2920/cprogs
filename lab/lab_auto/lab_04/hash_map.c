#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "hash_map.h"

extern char *strdup(const char *__s);

static size_t hash_code(const char *str, size_t size) {

    /* Initializing variables */
    auto size_t hash = 5381;
    auto char c;

    /* Main part */
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    /* Returning value */
    return hash % size;
}

struct DataItem *hash_search(const hashMap *hashArray, size_t size, const char *key) {

    /* Initializing variables */
    auto size_t hashIndex;

    /* Main part */
    for (hashIndex = hash_code(key, size); hashArray[hashIndex] != NULL; hashIndex = (hashIndex + 1) % size) {
        if (!strcmp(hashArray[hashIndex]->key, key))
            return hashArray[hashIndex];
    }

    return NULL;
}

void hash_insert(hashMap *hashArray, size_t size, const char *key, lexema_t *data) {

    /* Initializing variables */
    auto struct DataItem *item = (struct DataItem *) malloc(sizeof(struct DataItem));
    auto size_t hashIndex;

    /* VarCheck */
    assert(item != NULL);

    /* Main part */

    /* Copying value */
    item->key = strdup(key);
    assert(key != NULL);

    item->value = calloc(1, sizeof(lexema_t));;
    assert(item->value != NULL);

    memcpy(item->value, data, sizeof(lexema_t));

    /* Inserting unique key */
    hashIndex = hash_code(key, size);
    if (hashArray[hashIndex] == NULL) {
        hashArray[hashIndex] = item;
    } /*else {
        free(key);
        free(item);
    }*/
}

void hash_cleanup(hashMap *map, size_t size) {

    /* Initializing variables */
    register size_t i;

    /* Main part */
    for (i = 0; i < size; ++i) {
        if (*(map + i) != NULL) {
            free(map[i]->key);
            free(map[i]->value);

            free(*(map + i));
            map[i] = NULL;
        }
    }
}
