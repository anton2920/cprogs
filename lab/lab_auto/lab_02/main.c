#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <STL/STL_Vector.h>
#include <stdlib.h>
#include <assert.h>

#define isSpecialChar(x) ((x) == '+' || (x) == '-' || (x) == '*' \
                            || (x) == '/' || (x) == '^' || (x) == '=' \
                            || (x) == '(' || (x) == ')')

typedef struct identifier {
    char *value;
    size_t size;
} identifier;

typedef struct lexema {
    unsigned int id;
    identifier value;
} lexema;

enum buf_size {
    N = 100
};

void removeWhitespaces(char *);
char *lexer(char *str, STL_Vector *vec);
lexema * contains(STL_Vector *vec, const identifier *tk);
identifier getLexToken(char *);
void printTable(STL_Vector *);
int containsLetters(const char *);

main() {

    /* Initializing variables */
    auto STL_Vector expression_lexems;
    auto char buf[N], *finalStr;
    STL_Vector_init(&expression_lexems, sizeof(lexema));

    /* Debug case */
    auto FILE *fp = fopen("testCase.txt", "r");

    /* Main part */
    printf("Type lexical expression: ");
    fgets(buf, N, (fp == NULL) ? stdout : fp);
    *(buf + strlen(buf) - 1) = '\0';

    printf("\nExpression: %s\n", buf);

    removeWhitespaces(buf);

    finalStr = lexer(buf, &expression_lexems);

    printf("Lexer's output: %s\n", finalStr);
    free(finalStr);

    printTable(&expression_lexems);
}

void removeWhitespaces(char *str) {

    /* Initializing variables */
    register int i, j, len = strlen(str);
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

lexema *contains(STL_Vector *vec, const identifier *tk) {

    /* Initializing varibles */
    register size_t i;
    lexema *iter;

    /* VarCheck */
    if (STL_Vector_empty(vec)) {
        return 0;
    }

    /* Main part */
    for (i = 0; i < STL_Vector_size(vec); ++i) {
        iter = STL_Vector_at(vec, i);
        if (!strncmp(iter->value.value, tk->value, iter->value.size)) {
            return iter;
        }
    }

    /* Returning value */
    return NULL;
}

/* Rules:
 * Identifier should be started with latin letter
 * Between identifiers should be some actions
 */

char *lexer(char *str, STL_Vector *vec) {

    /* Initializing variables */
    auto lexema elem, *ret;
    auto unsigned int lastId = 0;
    auto identifier token;
    auto char *currStr = str;

    /* For string purposes */
    auto char *bigBuf = calloc(2048, sizeof(char));
    auto char smallBuf[20];

    /* Main part */
    for ( ; *currStr; currStr += token.size) {
        token = getLexToken(currStr);
        if (token.value == NULL) {
            /* String purposes */
            sprintf(smallBuf, "%c ", *currStr);
            strcat(bigBuf, smallBuf);

            ++currStr;
            continue;
        }

        assert(!(isdigit(*token.value) && token.size > 1 && containsLetters(token.value)));
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
        strcat(bigBuf, smallBuf);
    }

    /* Returning value */
    return bigBuf;
}

identifier getLexToken(char *str) {

    /* Initializing variables */
    auto char *currStr;
    auto identifier token;

    /* Main part */
    for (currStr = str; !isSpecialChar(*currStr); ++currStr)
        ;

    if (!(token.size = currStr - str)) {
        token.value = NULL;
    } else {
        token.value = malloc(token.size);
        strncpy(token.value, str, token.size);
    }

    /* Returning value */
    return token;
}

int containsLetters(const char *str) {

    /* Main part */
    for ( ; *str; ++str) {
        if (isalpha(*str)) {
            return 1;
        }
    }

    /* Returning value */
    return 0;
}

int isDouble(const char *str) {

    /* Main part */
    if (containsLetters(str)) {
        return 1;
    }

    for ( ; *str; ++str) {
        if (*str == '.') {
            return 1;
        }
    }

    /* Returning value */
    return 0;
}

void printTable(STL_Vector *table) {

    /* Initializing variables */
    register size_t i;
    lexema *iter;

    /* Main part */
    printf("┌───────────┬────────────┬──────────────┐\n"
           "│     ID    │   Lexeme   │     TYPE     │\n"
           "├───────────┼────────────┼──────────────┤\n");
    for (i = 0; i < STL_Vector_size(table); ++i) {
        iter = STL_Vector_at(table, i);
        printf("│    %4d   │   %6s   │     %3s_%c    │\n", iter->id,
            iter->value.value, (containsLetters(iter->value.value)) ? "VAR" : "IMM",
            isDouble(iter->value.value) ? 'D' : 'I');
        if (i != STL_Vector_size(table) - 1) {
            printf("├───────────┼────────────┼──────────────┤\n");
        }
    }

    /* Final output */
    printf("└───────────┴────────────┴──────────────┘\n");
}