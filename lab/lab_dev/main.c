#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "libs/libs.h"
#include "libs/hash_map.h"
#include "libs/tree.h"

void printTable(hashMap *map);
void lexer(FILE *fp, hashMap *map, STL_String *final_string);
void parser(STL_List *ast_list, STL_String *str);

main()
{
    /* Initializing variables */
    hashMap expression_lexems[MAP_SIZE] = {};

    STL_String final_string;
    STL_String_init(&final_string);

    STL_List ast_list;
    STL_List_init(&ast_list);

    /* Debug case */
    FILE *fp = fopen("testCase.txt", "r");
    /*assert(fp != NULL);*/

    /* Main part */

    /* Lexical analysis */
    lexer(fp, expression_lexems, &final_string);
    fclose(fp);

    printf("\nLexer's output:\n\n%s\n", STL_String_c_str(&final_string));
    printTable(expression_lexems); /* This clears STL_String memory */

    /* Parsing */
    parser(&ast_list, &final_string);
    STL_String_delete(&final_string);
    hash_cleanup(expression_lexems, MAP_SIZE);
    /* print_tree() */

    /* Generating code */
    /* TODO: codegen() */

    /*AST_Cleanup(&ast_list);*/
    STL_List_delete(&ast_list);

    /* Optimizing */

    /* Returning value */
    return 0;
}

void printTable(hashMap *map)
{
    /* Initializing variables */
    register size_t i;
    struct DataItem *itm;
    lexema_t *iter;

    /* Main part */
    printf("┌───────────┬────────────┬────────────────────────┐\n"
           "│     ID    │   Lexeme   │          TYPE          │\n");
    for (i = 0; i < MAP_SIZE; ++i) {
        itm = map[i];
        if (itm != NULL) {
            if (i != MAP_SIZE - 1) {
                printf("├───────────┼────────────┼────────────────────────┤\n");
            }
            iter = itm->value;
            printf("│    %4d   │   %6s   │  %-21s │\n", iter->id,
                   STL_String_c_str(&iter->value.name), iter->value.type);
            STL_String_delete(&iter->value.name);
        }
    }

    /* Final output */
    printf("└───────────┴────────────┴────────────────────────┘\n");
}

/* Rules:
 * Identifiers can't begin with digit
 * There are if–then and if–then–else statements, which are separated by ;
 * Allowed operators are: <, >, = and :=
 * If token consists only of X, V, and/or I, than it's a Roman number
 */
void lexer(FILE *fp, hashMap *map, STL_String *final_string)
{
    /* Initializing variables */
    struct DataItem *search;
    auto lexema_t elem, *ret;
    auto unsigned int lastId = 0;
    auto identifier_t token;
    auto char *currStr;

    /* For string purposes */
    auto char *bigBuf = calloc(N, sizeof(char));
    auto char smallBuf[20];

    /* Main part */
    printf("Program: \n");
    while (!feof(fp)) {
        if (lastId) {
            STL_String_push_back(final_string, '\n');
        }
        if (fgets(bigBuf, N, (fp == NULL) ? stdin : fp) == NULL) {
            break;
        }
        *(bigBuf + strlen(bigBuf)) = '\0';

        printf("%s", bigBuf);

        if (isspace(*bigBuf)) {
            insert_whitespaces(final_string, bigBuf);
        }

        remove_whitespaces(bigBuf);
        for (currStr = bigBuf; *currStr; currStr += STL_String_length(&token.name)) {
            getLexToken(currStr, &token);
            if (STL_String_empty(&token.name)) {
                /* String purposes */
                char *fmt = (*currStr == ';') ? "\b%c" : (*currStr == ':') ? "%c" : "%c ";
                sprintf(smallBuf, fmt, *currStr);
                STL_String_append_str(final_string, smallBuf);

                STL_String_delete(&token.name);

                ++currStr;
                continue;
            } else if ((search = hash_search(map, MAP_SIZE, STL_String_c_str(&token.name))) == NULL) {
                elem.value = token;
                elem.id = lastId++;
                hash_insert(map, MAP_SIZE, STL_String_c_str(&token.name), &elem);
            } else {
                STL_String_delete(&token.name);
            }

            /* String purposes */
            if (search == NULL) {
                sprintf(smallBuf, "<id%u> ", elem.id);
            } else {
                ret = search->value;
                sprintf(smallBuf, "<id%u> ", ret->id);
            }
            STL_String_append_str(final_string, smallBuf);
        }
    }

    free(bigBuf);
}

void parser(STL_List *ast_list, STL_String *str)
{
    /* Initializing variables */
    STL_List line_list;
    tree_t tree;
    size_t len;
    char line[N], *curr_line, *tok;
    const char *curr_str;

    STL_List_init(&line_list);
    Tree_init(&tree);

    /* Main part */
    for (curr_str = STL_String_c_str(str); curr_str > STL_String_end(str); curr_str += curr_line - line) {
        while (isspace(*curr_str++))
            ;
        if (curr_str > STL_String_end(str)) {
            break;
        }
        sscanf(curr_str, "%[^\n]", line);
        for (curr_line = line; *curr_line; curr_line += len) {
            len = get_parse_token(curr_line, &tok);
            if (!len) {
                ++curr_line;
            } else {
                STL_List_push_back(&line_list, &tok, len);
                free(tok);
            }
        }

        line_list_to_tree(&tree, &line_list);
        STL_List_push_back(ast_list, &tree, sizeof(tree_t));
    }
}
