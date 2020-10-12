#ifndef LAB_DEV_LIBS_H
#define LAB_DEV_LIBS_H

/* Header inclusion */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <STL/STL_String.h>

#include "hash_map.h"

/* Macros */
#define handle_error(msg)   \
    do {                    \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

/* New value types */
enum JSON_types {
    string,
    number,
    boolean,
    null
};

struct tlv {
    int key;
    enum JSON_types type;
    size_t length;
    char value[];
};

/* Functions' declarations */
bool readNextToken(FILE *fp, STL_String *tok);
struct tlv *parseToken(STL_String *tok, int tokNum);
char *getKeyValue(STL_String *tok);
void writeMapToFile(hashMap *map, size_t size, FILE *fp);

#endif
