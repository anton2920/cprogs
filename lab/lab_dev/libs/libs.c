#include <string.h>

#include "libs.h"

#define isdelim(x) ((x == ',') ? true : false)
#define isskip(x)   ((x) == '{' || (x) == '}')


/* Function reads next JSON KVP from file stream
 * Returns whether we need to change this file
 */
bool readNextToken(FILE *fp, STL_String *tok) {

    /* Initializing variables */
    auto int c;

    /* Main part */
    for (c = getc(fp); !isdelim(c) && c != EOF; c = getc(fp)) {
        if (isskip(c)) {
            continue;
        }

        if (c == '\n') {
            for (c = getc(fp); c != '{' && c != EOF; c = getc(fp))
                ;
            return true;
        }
        STL_String_push_back(tok, (char) c);
    }

    /* Returning value */
    return false;
}

/* Removes redundant backslashes */
void playWithBackslashes(STL_String *str) {

    /* Initializing variables */
    auto char *iter;

    /* Main part */
    for (iter = STL_String_begin(str); iter != STL_String_end(str); ++iter) {
        if (*iter == '\\' && *(iter + 1) != '\\') {
            STL_String_erase(str, iter - STL_String_begin(str), 1lu);
        }
    }
}

/* Parse tokens into TLV structure */
struct tlv *parseToken(STL_String *tok, int tokNum) {

    /* Initializing variables */
    auto struct tlv *ret, pred;
    auto size_t colonPos = STL_String_find(tok, ":");

    /* Temporary "containers" for our data types */
    auto char *quote;
    auto double num;
    auto bool tbool = false;

    /* Main part */
    playWithBackslashes(tok);

    /* Guessing data type by its representation in JSON file */
    if ((quote = strchr(STL_String_c_str(tok) + colonPos, '"')) != NULL) { /* String */
        pred.type = string;
        pred.length = strrchr(STL_String_c_str(tok) + colonPos, '"') - quote - 1;
    } else if (STL_String_find(tok, "true") != STL_String_npos()) { /* Bool */
        pred.type = boolean;
        pred.length = sizeof(bool);
        tbool = true;
    } else if (STL_String_find(tok, "false") != STL_String_npos()) {
        pred.type = boolean;
        pred.length = sizeof(bool);
        tbool = false;
    } else if (STL_String_find(tok, "null") != STL_String_npos()) { /* Null */
        pred.type = null;
        pred.length = 0;
    } else { /* Number (double) */
        sscanf(STL_String_c_str(tok) + colonPos + 1, "%lf", &num); /* Unsafe */
        pred.type = number;
        pred.length = sizeof(double);
    }

    /* Allocating memory for flexible-sized structure */
    if ((ret = calloc(1, sizeof(struct tlv) + pred.length)) == NULL) {
        handle_error("calloc");
    }
    ret->type = pred.type;
    ret->length = pred.length;
    ret->key = tokNum;
    switch (ret->type) {
        case string:
            memcpy(ret->value, quote + 1, ret->length);
            break;
        case number:
            memcpy(ret->value, &num, sizeof(double));
            break;
        case boolean:
            memcpy(ret->value, &tbool, sizeof(bool));
            break;
        default:
            break;
    }

    /* Returning value */
    return ret;
}

/* Returns allocated (char *) to our key value */
char *getKeyValue(STL_String *tok) {

    /* Initializing variables */
    auto size_t colonPos = STL_String_find(tok, ":");
    auto char *quote = strchr(STL_String_c_str(tok), '"'), *colon = STL_String_begin(tok) + colonPos;
    auto size_t nchar;
    auto char *ret;

    /* Main part */
    while (*colon-- != '"')
        ;
    nchar = colon - quote;
    if ((ret = calloc(nchar, sizeof(char))) == NULL) {
        handle_error("calloc");
    }
    memcpy(ret, quote + 1, nchar);

    /* Returning value */
    return ret;
}

/* Dump our dictionary to file in TLV encoding */
void writeMapToFile(hashMap *map, size_t size, FILE *fp) {

    /* Initializing variables */
    struct tlv *entry;
    auto size_t i, entryValueSize;

    for (i = 0; i < size; ++i) {
        if (map[i] != NULL) {

            /* Finding our data length */
            entryValueSize = strlen(map[i]->key);

            /* Allocating memory */
            if ((entry = calloc(1, sizeof(struct tlv) + entryValueSize)) == NULL) {
                handle_error("calloc");
            }

            /* Setting up our TLV structure */
            entry->length = entryValueSize;
            entry->type = string;
            entry->key = map[i]->value;
            memcpy(entry->value, map[i]->key, entryValueSize);

            /* Writing results */
            if (fwrite(entry, sizeof(struct tlv) + entry->length, 1, fp) != 1) {
                handle_error("fwrite");
            }
            free(entry);
        }
    }
}