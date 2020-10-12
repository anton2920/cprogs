#include <stdio.h>

#include "libs/libs.h"

/* Every produced file starts with... */
static const char *fileNamePrefix = "parsedFileA";

/* Arbitrary constant to fix hashmap size */
enum {
    hashMap_size = 0xFFFF
};

int main(int argc, const char *argv[]) {

    /* Initializing variables */
    auto FILE *fin, *fout; /* Files */
    auto bool needToClose = false;

    /* Place to hold one KVP */
    auto STL_String tok;
    STL_String_init(&tok);

    /* Current file to store parsed tokens */
    auto char currentFile = 'A';
    auto STL_String currentFileName;
    STL_String_init(&currentFileName);

    /* Hashmap and Dictionary */
    auto int tokNum = 1;
    auto hashMap dict[hashMap_size] = {};


    /* VarCheck */
    if (argc < 2) {
        fprintf(stderr, "json: you must provide a file path\n");
        exit(-1);
    } else if (argc > 2) {
        fprintf(stderr, "json: you must provide one argument only\n");
        exit(-1);
    }

    /* Main part */

    /* Opening input file */
    if ((fin = fopen(*(argv + 1), "r")) == NULL) {
        handle_error("fopen");
    }

    /* Prepare output file name */
    STL_String_append_str(&currentFileName, fileNamePrefix);
    if ((fout = fopen(STL_String_c_str(&currentFileName), "wb")) == NULL) {
        handle_error("fopen");
    }

    /* Reading tokens */
    for ( ;; ) {

        /* Obtaining token from file stream */
        needToClose = readNextToken(fin, &tok);

        /* Parse our token into TLV format */
        struct tlv *parsedToken = parseToken(&tok, tokNum); /* Function uses calloc(3) */
        if (fwrite(parsedToken, sizeof(struct tlv) + parsedToken->length, 1, fout) != 1) {
            handle_error("fwrite");
        }
        free(parsedToken); /* Cleaning up */

        /* Adding string-integer pair to our dictionary */
        insert(dict, hashMap_size, getKeyValue(&tok) , tokNum++);

        /* Clearing the token-string for the next run */
        STL_String_clear(&tok);

        /* Checking whether we need to change the file */
        if (needToClose || feof(fin)) {

            /* Storing our dictionary */
            writeMapToFile(dict, hashMap_size, fout);
            cleanMap(dict, hashMap_size);

            /* We're done with this file. We can safely close it */
            fclose(fout);

            /* Checking whether we need to finish */
            if (!feof(fin)) {

                /* Updating file name */
                ++currentFile;
                if (currentFile < 'Z') {
                    STL_String_pop_back(&currentFileName);
                } else {
                    STL_String_pop_back(&currentFileName);
                    currentFile = 'A';
                    STL_String_push_back(&currentFileName, currentFile);
                }
                STL_String_push_back(&currentFileName, currentFile);

                /* Opening new file */
                if ((fout = fopen(STL_String_c_str(&currentFileName), "wb")) == NULL) {
                    handle_error("fopen");
                }
                tokNum = 1;
            } else {

                /* We're done, no more data left in the original file */
                break;
            }
        }
    }

    /* Cleaning up the mess... */
    fclose(fin);
    cleanMap(dict, hashMap_size);
    STL_String_delete(&tok);
    STL_String_delete(&currentFileName);

    /* Returning value */
    return 0;
}