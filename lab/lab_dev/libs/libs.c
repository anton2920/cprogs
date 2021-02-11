#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "libs.h"
#include "tree.h"

#define isSpecialChar(x) ((x) == '+' || (x) == '-' || (x) == '*'        \
                            || (x) == '/' || (x) == '^' || (x) == '('   \
                            || (x) == ')' || (x) == ';' || (x) == ':'   \
                            || (x) == '<' || (x) == '>' || (x) == '=')

static char *digits_allowed_chars = "0123456789.e-+";
static char *letters = "abcdefghijklmnopqrstuvwxyz";
static char *romans = "XVI";
static char *comparison_operators = "<=>";

void remove_whitespaces(char *str)
{
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

void get_token_type(identifier_t *token)
{
    /* Initializing variables */
    const char *types[] = { "IMMEDIATE_INTEGER", "IMMEDIATE_DOUBLE", "VARIABLE", "ROMAN_NUMBER",
                            "CONDITIONAL_STATEMENT" };

    /* Main part */
    do {
        if (STL_String_find_first_of(&token->name, digits_allowed_chars) == 0 &&
            *STL_String_c_str(&token->name) != 'e') {
            if (STL_String_find_first_not_of(&token->name, digits_allowed_chars) == STL_String_npos()) {
                if (STL_String_find(&token->name, ".") != STL_String_npos()) {
                    token->etype = IMMEDIATE_DOUBLE;
                    break;
                } else {
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
            token->etype = ROMAN_NUMBER;
            break;
            /*} else if (STL_String_find_first_of(&token->name, comparison_operators) != STL_String_npos() &&
                       STL_String_length(&token->name) == 1) {
                token->etype = COMPARISON_OPERATOR;
                break;
            } else if (STL_String_find(&token->name, ":=") != STL_String_npos() &&
                       STL_String_length(&token->name) == 1) {
                token->etype = ASSIGNMENT_OPERATOR;
                break;*/
        } else if ((STL_String_find(&token->name, "if") != STL_String_npos() &&
                    STL_String_length(&token->name) == 2) ||
                   ((STL_String_find(&token->name, "else") != STL_String_npos() &&
                     STL_String_length(&token->name) == 4) ||
                    (STL_String_find(&token->name, "then") != STL_String_npos() &&
                     STL_String_length(&token->name) == 4))) {
            token->etype = CONDITIONAL_STATEMENT;
            break;
        } else {
            token->etype = VARIABLE;
        }
    } while (0);

    token->type = types[token->etype];
}

void getLexToken(char *str, identifier_t *token)
{
    /* Initializing variables */
    auto char *currStr, tmp;
    STL_String_init(&token->name);

    /* Main part */
    for (currStr = str; !isSpecialChar(*currStr) && *currStr; ++currStr);

    tmp = *currStr;
    *currStr = '\0';
    STL_String_append_str(&token->name, str);
    if (!STL_String_empty(&token->name)) {
        get_token_type(token);
    }
    *currStr = tmp;
}

int is_roman(STL_String *str)
{
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

void insert_whitespaces(STL_String *dest, const char *src)
{
    /* Main part */
    if (*src == '\n') {
        ++src;
    }

    for (; isspace(*src) && *src; ++src) {
        STL_String_push_back(dest, *src);
    }
}

/* Allocates memory with calloc(3). Needs free(3) after */
size_t get_parse_token(const char *str, char **tok)
{
    /* Initializing variables */
    const char *str_end = str;
    size_t len;

    /* Main part */
    while (!isspace(*str_end++) && *str_end)
        ;

    len = str_end - str - 1;
    if (len) {
        *tok = calloc(len + 1, sizeof(char));
        memcpy(*tok, str, len);
    }

    /* Returning value */
    return len;
}

void line_list_to_tree(tree_t *tree, STL_List *line_list)
{
    /* Initializing variables */


    /* Main part */

}
