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
    int num_num;
};

struct word {
    char *str;
    int wd_len;
};

/* source.c */

/* task #7 */
bool check_args(int, char *[]);
bool create_string(char **);
void read_text(struct string *);
void find_digits(struct string *);
void rm_ch(char *, int);
void print_text(char *);
void print_num_num(int);
void delete_string(char *);

/* task #16 */
void read_str(char **);
void rm_sp(char *);
void print_str(char *);

/* task #25 */
int find_occ(char *, struct word *);
struct word get_next_word(struct word *);
void find_sht(char *, char *);

#endif //LAB_DEV_SOURCE_H
