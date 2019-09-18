#ifndef LAB_DEV_SOURCE_H
#define LAB_DEV_SOURCE_H

/* Header inclusion */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

/* Types */
typedef enum {
    false,
    true
} bool;

struct string {
    char *str;
    int let_num;
};

/* source.c */
bool create_string(char **);
void str_err(void);
void read_text(struct string *);
char read_letter(void);
void find_letter(char, struct string *);
void print_let_num(char, int);
void delete_string(char *);

#endif //LAB_DEV_SOURCE_H