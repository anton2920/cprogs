#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <STL/STL_Vector.h>
#include <stdlib.h>
#include <assert.h>

#include "libs/libs.h"
#include "libs/hash_map.h"

#define isSpecialChar(x) ((x) == '+' || (x) == '-' || (x) == '*'        \
                            || (x) == '/' || (x) == '^' || (x) == '('   \
                            || (x) == ')' || (x) == ';' || (x) == ':'   \
                            || (x) == '<' || (x) == '>' || (x) == '=')

static char *digits_allowed_chars = "0123456789.e-+";
static char *letters = "abcdefghijklmnopqrstuvwxyz";
static char *romans = "XVI";
static char *comparison_operators = "<=>";

void remove_whitespaces(char *str);
void lexer(FILE *fp, hashMap *map, STL_String *final_string);
identifier_t getLexToken(char *str);
void printTable(hashMap *map);
int is_roman(STL_String *str);
void insert_whitespaces(STL_String *dest, const char *src);

main() {

    /* Initializing variables */
    /*auto STL_Vector expression_lexems;
    STL_Vector_init(&expression_lexems, sizeof(lexema_t));*/
    hashMap expression_lexems[MAP_SIZE] = {};

    auto STL_String final_string;
    STL_String_init(&final_string);

    /* Debug case */
    auto FILE *fp = fopen("testCase.txt", "r");
    assert(fp != NULL);

    /* Main part */
    lexer(fp, expression_lexems, &final_string);

    printf("\nLexer's output:\n%s\n", STL_String_c_str(&final_string));

    STL_String_delete(&final_string);

    printTable(expression_lexems); /* This clears STL_String memory */

    hash_cleanup(expression_lexems, MAP_SIZE);
}

void remove_whitespaces(char *str) {

    /* Initializing variables */
    register size_t i, j, len = strlen(str);
    auto size_t removed = 0, len2 = len;

    /* Main part */
    for (i = 0; i < len2; ++i) {
        if (isspace(*(str + i))) {
            ++removed;
            --len2;
            for (j = i; j < len - 1; ++j) {
                *(str + j) = *(str + j + 1);
            }
            --i;
        }
    }

    *(str + len - removed) = '\0';
}

/*lexema_t *contains(STL_Vector *vec, identifier_t *tk) {

    *//* Initializing varibles *//*
    register size_t i;
    lexema_t *iter;

    *//* VarCheck *//*
    if (STL_Vector_empty(vec)) {
        return 0;
    }

    *//* Main part *//*
    for (i = 0; i < STL_Vector_size(vec); ++i) {
        iter = STL_Vector_at(vec, i);
        if (!STL_String_compare(&tk->name, &iter->value.name)) {
            return iter;
        }
    }

    *//* Returning value *//*
    return NULL;
}*/

/* Rules:
 * Identifiers can't begin with digit
 * There are if–then and if–then–else statements, which are separated by ;
 * Allowed operators are: <, >, = and :=
 * If token consists only of X, V, and/or I, than it's a Roman number
 */

void lexer(FILE *fp, hashMap *map, STL_String *final_string) {

    /* Initializing variables */
    struct DataItem *search;
    auto lexema_t elem, *ret;
    auto unsigned int lastId = 0;
    auto identifier_t token;
    auto char *currStr;

    /* For string purposes */
    auto char *bigBuf = calloc(2048, sizeof(char));
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
            token = getLexToken(currStr);
            if (STL_String_empty(&token.name)) {
                /* String purposes */
                char *fmt = (*currStr == ';') ? "\b%c" : (*currStr == ':') ? "%c" : "%c ";
                sprintf(smallBuf, fmt, *currStr);
                STL_String_append_str(final_string, smallBuf);

                STL_String_delete(&token.name);
                STL_String_delete(&token.type);

                ++currStr;
                continue;
            }

            if ((search = hash_search(map, MAP_SIZE, STL_String_c_str(&token.name))) == NULL)
            {
                elem.value = token;
                elem.id = lastId++;
                hash_insert(map, MAP_SIZE, STL_String_c_str(&token.name), &elem);
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

void get_token_type(identifier_t *token) {

    /* Main part */
    do {
        if (STL_String_find_first_of(&token->name, digits_allowed_chars) == 0 &&
            *STL_String_c_str(&token->name) != 'e') {
            if (STL_String_find_first_not_of(&token->name, digits_allowed_chars) == STL_String_npos()) {
                if (STL_String_find(&token->name, ".") != STL_String_npos()) {
                    STL_String_append_str(&token->type, "IMMEDIATE_DOUBLE");
                    token->etype = IMMEDIATE_DOUBLE;
                    break;
                } else {
                    STL_String_append_str(&token->type, "IMMEDIATE_INTEGER");
                    token->etype = IMMEDIATE_INTEGER;
                    break;
                }
            } else {
                fprintf(stderr, "%s: WRONG VARIABLE NAME!\n", STL_String_c_str(&token->name));
                exit(-1);
            }
        }

        if (STL_String_find_first_not_of(&token->name, romans) == STL_String_npos() &&
                is_roman(&token->name)) {
            STL_String_append_str(&token->type, "ROMAN_NUMBER");
            token->etype = ROMAN_NUMBER;
            break;
        /*} else if (STL_String_find_first_of(&token->name, comparison_operators) != STL_String_npos() &&
                   STL_String_length(&token->name) == 1) {
            STL_String_append_str(&token->type, "COMPARISON_OPERATOR");
            token->etype = COMPARISON_OPERATOR;
            break;
        } else if (STL_String_find(&token->name, ":=") != STL_String_npos() &&
                   STL_String_length(&token->name) == 1) {
            STL_String_append_str(&token->type, "ASSIGNMENT_OPERATOR");
            token->etype = ASSIGNMENT_OPERATOR;
            break;*/
        } else if ((STL_String_find(&token->name, "if") != STL_String_npos() &&
                    STL_String_length(&token->name) == 2) ||
                   ((STL_String_find(&token->name, "else") != STL_String_npos() &&
                    STL_String_length(&token->name) == 4) ||
                   (STL_String_find(&token->name, "then") != STL_String_npos() &&
                    STL_String_length(&token->name) == 4))) {
            STL_String_append_str(&token->type, "CONDITIONAL_STATEMENT");
            token->etype = CONDITIONAL_STATEMENT;
            break;
        } else {
            STL_String_append_str(&token->type, "VARIABLE");
            token->etype = VARIABLE;
        }
    } while (0);
}

identifier_t getLexToken(char *str) {

    /* Initializing variables */
    auto char *currStr, tmp;
    auto identifier_t token;
    STL_String_init(&token.name);
    STL_String_init(&token.type);

    /* Main part */
    for (currStr = str; !isSpecialChar(*currStr) && *currStr; ++currStr)
        ;

    tmp = *currStr;
    *currStr = '\0';
    STL_String_append_str(&token.name, str);
    if (!STL_String_empty(&token.name)) {
        get_token_type(&token);
    }
    *currStr = tmp;

    /* Returning value */
    return token;
}

void printTable(hashMap *map) {

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
                   STL_String_c_str(&iter->value.name), STL_String_c_str(&iter->value.type));
            STL_String_delete(&iter->value.name);
            STL_String_delete(&iter->value.type);
        }
    }

    /* Final output */
    printf("└───────────┴────────────┴────────────────────────┘\n");
}

int is_roman(STL_String *str) {

    /* Main part */
    /* Rule 1. The roman digits I and X
     * are repeated upto three times in succession to form the numbers.
     */
    if (STL_String_find(str, "XXXX") != STL_String_npos() ||
        STL_String_find(str, "IIII") != STL_String_npos()) {
        return 0;
    }

    /* The digits V, L and D are not repeated.
     * The repetition of V, L and D is invalid in the formation of numbers.
     */
    if (strchr(STL_String_c_str(str), 'V') != strrchr(STL_String_c_str(str), 'V')) {
        return 0;
    }

    /* Rule 3. V is never written to the left of X. */
    if (STL_String_find(str, "IXX") != STL_String_npos() ||
        STL_String_find(str, "VX") != STL_String_npos()) {
        return 0;
    }

    /* Returnining value */
    return 1;
}

void insert_whitespaces(STL_String *dest, const char *src) {

    /* Main part */
    if (*src == '\n') {
        ++src;
    }

    for ( ; isspace(*src) && *src; ++src) {
        STL_String_push_back(dest, *src);
    }
}