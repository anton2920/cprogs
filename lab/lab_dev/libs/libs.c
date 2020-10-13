#include <string.h>

#include "libs.h"

#define isdelim(x) ((x == ',') ? true : false)
#define isskip(x)   ((x) == '{' || (x) == '\n')

static void searchTilMap(FILE *fp);
static struct DataItem *searchValue(STL_Vector *vec, int value);
static void getRidOfKeys(STL_Vector *vec);

/* Function reads next JSON KVP from file stream */
void readNextToken(FILE *fp, STL_String *tok) {

    /* Initializing variables */
    auto int c;

    /* Main part */
    for (c = getc(fp); !isdelim(c) && c != EOF; c = getc(fp)) {
        if (isskip(c)) {
            continue;
        }

        if (c == '}') {
            for (c = getc(fp); c != '{' && c != EOF; c = getc(fp))
                ;
            break;
        }
        STL_String_push_back(tok, (char) c);
    }
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
        pred.length = (int) (strrchr(STL_String_c_str(tok) + colonPos, '"') - quote - 1);
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
    if ((ret = calloc(nchar + 1, sizeof(char))) == NULL) {
        handle_error("calloc");
    }
    memcpy(ret, quote + 1, nchar);

    /* Returning value */
    return ret;
}

/* Dump our dictionary to file in TLV encoding */
void writeMapToFile(hashMap *map, size_t size, FILE *fp) {

    /* Initializing variables */
    struct tlv *entry, nullTLV = {};
    auto size_t i, entryValueSize;

    if (fwrite(&nullTLV, sizeof(struct tlv), 0x1, fp) != 1) {
        handle_error("fwrite");
    }

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

static void searchTilMap(FILE *fp) {

    /* Initializing variables */
    auto struct tlv pred, nullTLV = {};

    /* Main part */
    do {
        if (fread(&pred, sizeof(struct tlv), 0x1, fp) != 0x1) {
            handle_error("fread");
        }
        fseek(fp, pred.length, SEEK_CUR);
    } while (memcmp(&pred, &nullTLV, sizeof(struct tlv)) != 0);
}

static struct DataItem *searchValue(STL_Vector *vec, int value) {

    /* Initializing variables */
    register size_t i;
    auto struct DataItem *data;

    /* Main part */
    for (i = 0; i < STL_Vector_size(vec); ++i) {
        data = STL_Vector_at(vec, i);
        if (data->value == value) {
            return data;
        }
    }

    /* Returning value */
    return NULL;
}

static void getRidOfKeys(STL_Vector *vec) {

    /* Initializing variables */
    register size_t i;
    auto struct DataItem *item;

    /* Main part */
    for (i = 0; i < STL_Vector_size(vec); ++i) {
        item = STL_Vector_at(vec, i);
        free(item->key);
    }
}

void restoreOriginalFile(const char *inputFileName) {

    /* Initializing variables */
    auto FILE *fin, *fout;

    auto struct tlv pred, nullTLV = {};

    auto char *mapKey;
    auto STL_Vector dict;
    STL_Vector_init(&dict, sizeof(struct DataItem));
    auto struct DataItem *mapEntry, element;

    auto char *tempString;
    auto double tempDouble;
    auto bool tempBool;


    /* I/O flow */
    if ((fin = fopen(inputFileName, "rb")) == NULL) {
        handle_error("fopen");
    }

    if ((fout = fopen("result.json", "w")) == NULL) {
        handle_error("fopen");
    }

    /* Main part */
    searchTilMap(fin);

    /* Fill in our dictionary */
    while (fread(&pred, sizeof(struct tlv), 0x1, fin)) {
        if ((mapKey = calloc(pred.length + 1, sizeof(char))) == NULL) {
            handle_error("malloc");
        }

        if (fread(mapKey, sizeof(char), pred.length, fin) != (size_t) pred.length) {
            handle_error("fread");
        }

        element.key = mapKey;
        element.value = pred.key;

        STL_Vector_push_back(&dict, &element);
    }

    rewind(fin);

    /* Forming up the output file */
    do {
        if (fread(&pred, sizeof(struct tlv), 0x1, fin) != 0x1) {
            handle_error("fread");
        }
        if (!memcmp(&pred, &nullTLV, sizeof(struct tlv))) {
            break;
        }

        mapEntry = searchValue(&dict, pred.key);

        switch (pred.type) {
            case string:
                if ((tempString = calloc(pred.length + 1, sizeof(char))) == NULL) {
                    handle_error("calloc");
                }
                if (fread(tempString, sizeof(char), pred.length, fin) != (size_t) pred.length) {
                    handle_error("fread");
                }
                fprintf(fout, "{ \"%s\": \"%s\" }\n", mapEntry->key, tempString);
                free(tempString);
                break;
            case number:
                if (fread(&tempDouble, sizeof(double), 0x1, fin) != 0x1) {
                    handle_error("fread");
                }
                fprintf(fout, "{ \"%s\": %lf }\n", mapEntry->key, tempDouble);
                break;
            case boolean:
                if (fread(&tempBool, sizeof(bool), 0x1, fin) != 0x1) {
                    handle_error("fread");
                }
                fprintf(fout, "{ \"%s\": %s }\n", mapEntry->key, (tempBool) ? "true" : "false");
                break;
            case null:
                fprintf(fout, "{ \"%s\": null }\n", mapEntry->key);
                break;
            default:
                break;
        }
    } while (1);

    /* Cleaning up the mess... */
    fclose(fin);
    fclose(fout);
    getRidOfKeys(&dict);
    STL_Vector_delete(&dict);
}