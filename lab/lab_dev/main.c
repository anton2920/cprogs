#include <stdio.h>

#include "libs/libs.h"

static const char *outputFileName = "result.bin";

int main(int argc, const char *argv[]) {

    /* Initializing variables */
    auto FILE *fin, *fout; /* Files */

    /* Place to hold one KVP */
    auto STL_String tok;
    STL_String_init(&tok);
    auto char *keyValue;

    /* Hashmap and Dictionary */
    auto int tokNum = 1;
    auto hashMap dict[hashMap_size] = {};
    auto struct DataItem *result;

    /* VarCheck */
    if (argc < 2) {
        fprintf(stderr, "json: you must provide a file path\n");
        exit(-1);
    } else if (argc > 2) {
        fprintf(stderr, "json: you must provide one argument only\n");
        exit(-1);
    }

    /* Main part */

    /* Opening files */
    if ((fin = fopen(*(argv + 1), "r")) == NULL) {
        handle_error("fopen");
    }

    if ((fout = fopen(outputFileName, "wb")) == NULL) {
        handle_error("fopen");
    }

    /* Reading tokens */
    for ( ;; ) {

        /* Obtaining token from file stream */
        readNextToken(fin, &tok);

        /* Parse our token into TLV format */
        struct tlv *parsedToken = parseToken(&tok, tokNum); /* Function uses calloc(3) */

        /* Inserting unique string-int pair */
        if ((result = search(dict, hashMap_size,
                             keyValue = getKeyValue(&tok))) == NULL) { /* getKeyValue() uses calloc(3) */
            insert(dict, hashMap_size, keyValue , tokNum++);
        } else {
            /* If pair is presented in dict, get it's int value */
            parsedToken->key = result->value;

            /* Key value is not in use. We can free(3) it */
            free(keyValue);
        }

        if (fwrite(parsedToken, sizeof(struct tlv) + parsedToken->length, 1, fout) != 1) {
            handle_error("fwrite");
        }
        free(parsedToken); /* Cleaning up */

        /* Clearing the token-string for the next run */
        STL_String_clear(&tok);

        /* Checking whether we need to change the file */
        if (feof(fin)) {

            /* Storing our dictionary */
            writeMapToFile(dict, hashMap_size, fout);

            /* We're done, no more data left in the original file */
            break;
        }
    }

    /* Cleaning up the mess... */
    fclose(fin);
    fclose(fout);
    cleanMap(dict, hashMap_size);
    STL_String_delete(&tok);

    /* Parsing resulted file */
    restoreOriginalFile(outputFileName);

    /* Returning value */
    return 0;
}