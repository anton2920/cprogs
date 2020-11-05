#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <STL/STL_Vector.h>
#include <STL/STL_String.h>
#include <stdlib.h>
#include <assert.h>

#define isSpecialChar(x) ((x) == '+' || (x) == '-' || (x) == '*'        \
                            || (x) == '/' || (x) == '^' || (x) == '('   \
                            || (x) == ')' || (x) == ';' || (x) == ':'   \
                            || (x) == '<' || (x) == '>' || (x) == '=')

static char *digits_allowed_chars = "0123456789.e-+";
static char *letters = "abcdefghijklmnopqrstuvwxyz";
static char *romans = "XVI";
static char *comparison_operators = "<=>";

typedef enum language_types {
    IMMEDIATE_INTEGER,
    IMMEDIATE_DOUBLE,
    VARIABLE,
    ROMAN_NUMBER,
    CONDITIONAL_STATEMENT,
    COMPARISON_OPERATOR,
    ASSIGNMENT_OPERATOR
} lang_type_t;

typedef struct identifier {
    STL_String name;
    STL_String type;
    lang_type_t etype;
} identifier_t;

typedef struct lexema {
    unsigned int id;
    identifier_t value;
} lexema_t;

enum {
    N = 100
};

void removeWhitespaces(char *);
void lexer(FILE *fp, STL_Vector *vec, STL_String *final_string);
lexema_t *contains(STL_Vector *vec, identifier_t *tk);
identifier_t getLexToken(char *);
void printTable(STL_Vector *);
int is_roman(STL_String *str);
void insert_whitespaces(STL_String *dest, const char *src);

main() {

    /* Initializing variables */
    auto STL_Vector expression_lexems;
    STL_Vector_init(&expression_lexems, sizeof(lexema_t));
    auto STL_String final_string;
    STL_String_init(&final_string);

    /* Debug case */
    auto FILE *fp = fopen("testCase.txt", "r");
    assert(fp != NULL);

    /* Main part */
    lexer(fp, &expression_lexems, &final_string);

    printf("\nLexer's output:\n\n%s\n", STL_String_c_str(&final_string));

    STL_String_delete(&final_string);

    printTable(&expression_lexems); /* This clears STL_String memory */

    STL_Vector_delete(&expression_lexems);
}

void removeWhitespaces(char *str) {

    /* Initializing variables */
    register int i, j;
    register size_t len = strlen(str);
    auto int removed = 0, len2 = len;

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

lexema_t *contains(STL_Vector *vec, identifier_t *tk) {

    /* Initializing varibles */
    register size_t i;
    lexema_t *iter;

    /* VarCheck */
    if (STL_Vector_empty(vec)) {
        return 0;
    }

    /* Main part */
    for (i = 0; i < STL_Vector_size(vec); ++i) {
        iter = STL_Vector_at(vec, i);
        if (!STL_String_compare(&tk->name, &iter->value.name)) {
            return iter;
        }
    }

    /* Returning value */
    return NULL;
}

/* Rules:
 * Identifiers can't begin with digit
 * There are if–then and if–then–else statements, which are separated by ;
 * Allowed operators are: <, >, = and :=
 * If token consists only of X, V, and/or I, than it's a Roman number
 */

void lexer(FILE *fp, STL_Vector *vec, STL_String *final_string) {

    /* Initializing variables */
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

        removeWhitespaces(bigBuf);
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

            if ((ret = contains(vec, &token)) == NULL) {
                elem.value = token;
                elem.id = lastId++;
                STL_Vector_push_back(vec, &elem);
            }

            /* String purposes */
            if (ret == NULL) {
                sprintf(smallBuf, "<id%u> ", elem.id);
            } else {
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
                   (STL_String_find(&token->name, "then") != STL_String_npos()) &&
                    STL_String_length(&token->name) == 4)) {
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

void printTable(STL_Vector *table) {

    /* Initializing variables */
    register size_t i;
    lexema_t *iter;

    /* Main part */
    printf("┌───────────┬────────────┬────────────────────────┐\n"
           "│     ID    │   Lexeme   │          TYPE          │\n"
           "├───────────┼────────────┼────────────────────────┤\n");
    for (i = 0; i < STL_Vector_size(table); ++i) {
        iter = STL_Vector_at(table, i);
        printf("│    %4d   │   %6s   │  %-21s │\n", iter->id,
               STL_String_c_str(&iter->value.name), STL_String_c_str(&iter->value.type));
        if (i != STL_Vector_size(table) - 1) {
            printf("├───────────┼────────────┼────────────────────────┤\n");
        }
        STL_String_delete(&iter->value.name);
        STL_String_delete(&iter->value.type);
    }

    /* Final output */
    printf("└───────────┴────────────┴────────────────────────┘\n");
}

int is_roman(STL_String *str) {

    /* Initializing variables */
    char *iter;

    /* Main part */
    for (iter = STL_String_begin(str); iter != STL_String_end(str); ++iter) {

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