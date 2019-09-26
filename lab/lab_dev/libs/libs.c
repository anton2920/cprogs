#include "libs.h"

FILE *getFd(void) {

    /* Initializing variables */
    auto char name[20];

    /* I/O flow */
    printf("Type the file name: ");
    scanf("%s", name);

    /* Returning value */
    return fopen(name, "r");
}

struct token *tryParseForOp(const char *str, size_t length) {

    /* Initializing variables */
    auto size_t i;
    auto struct token *tmp;

    /* Main part */
    for (i = 0; i < length; ++i) {
        if (isoperator(*(str + i))) {
            tmp = token_alloc(1);
            tmp->type = op;
            tmp->op_val = *(str + i);
            tmp->beg = (void *) (str + i);
            return tmp;
        }
    }

    /* Returning value */
    return NULL;
}

struct token *token_alloc(size_t nelem) {

    /* Returning value */
    return (struct token *) malloc(sizeof(struct token) * nelem);
}

struct token *getFirstNum(struct token *op, const char *string, size_t index) {

    /* Initializing variables */
    auto size_t i;
    auto struct token *num1;
    auto char tmp[max_num_len] = "", *test;
    auto size_t length;

    /* Main part */
    for (i = index - 1; i && isdigit(*(string + i)) && index - i <= max_num_len; --i)
        ; /* While i > 0, our char is digit and we don't exceed maximum number length */

    if (!(length = (i) ? (index - i - 1) : (index))) {
        return NULL; /* No digits were found */
    }

    strncpy(tmp, (i) ? (string + i + 1) : (string), length);

    num1 = token_alloc(1);
    num1->type = num;
    num1->num_val = strtol(tmp, &test, 10);
    if (test == NULL) {
        free(num1);
        return NULL; /* We have missed some deprecated symbols */
    }

    /* Returning value */
    return num1;
}

struct token *getSecondNum(struct token *op, const char *string, size_t index) {

    /* Initializing variables */
    auto size_t i;
    auto struct token *num2;
    auto char tmp[max_num_len] = "", *test;
    auto size_t length;

    /* Main part */
    for (i = index + 1; i < strlen(string) && isdigit(*(string + i)) && i - index <= max_num_len; ++i)
        ; /* While i < strlen(string), our char is digit and we don't exceed maximum number length */

    if (!(length = i - index - 1)) {
        return NULL; /* No digits were found */
    }

    strncpy(tmp, string + i - length, length);

    num2 = token_alloc(1);
    num2->type = num;
    num2->num_val = strtol(tmp, &test, 10);
    if (op->op_val == '/' && !num2->num_val) {
        free(num2);
        return NULL; /* Zero division error */
    }

    if (test == NULL) {
        free(num2);
        return NULL; /* We have missed some deprecated symbols */
    }

    /* Returning value */
    return num2;
}

long eval(struct token *num1, struct token *op, struct token *num2) {

    /* Initializing variables */
    register long res = 0;

    /* Main part */
    switch (op->op_val) {
        case '+':
            res = num1->num_val + num2->num_val;
            break;
        case '-':
            res = num1->num_val - num2->num_val;
            break;
        case '*':
            res = num1->num_val * num2->num_val;
            break;
        case '/':
            res = num1->num_val / num2->num_val;
            break;
        default:
            break;
    }

    /* Returning value */
    return res;
}