#ifndef LAB_DEV_LIBS_H
#define LAB_DEV_LIBS_H

/* Header inclusions */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

/* Macro definitions */
#define isoperator(x) ((x) == '+' || (x) == '-' || (x) == '*' || (x) == '/')

/* Type definitions */
enum token_const {
    max_num_len = 18
};

enum tt {
    op,
    num
};

struct token {
    enum tt type;
    union {
        long num_val;
        struct {
            char op_val;
            void *beg;
        };
    };
};

/* Functions declarations */
FILE *getFd(void);
struct token *tryParseForOp(const char *, size_t);
struct token *token_alloc(size_t);
struct token *getFirstNum(struct token *, const char *, size_t);
struct token *getSecondNum(struct token *, const char *, size_t);
long eval(struct token *, struct token *, struct token *);

#endif
