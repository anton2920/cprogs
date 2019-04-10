#ifndef LAB_DEV_SOURCE_H
#define LAB_DEV_SOURCE_H

/* Header inclusion */
#include <stdio.h>
#include <stdlib.h>

/* Types */
typedef enum {
    false,
    true
} bool;

union mas_p {
    /* Single pointers */
    void *vd_p;
    int *i_p;
    double *d_p;
    char *c_p;

    /* Double pointers */
    void **vd_pp;
    int **i_pp;
    double **d_pp;
    char **c_pp;
};

enum type {
    void_p,
    int_p,
    double_p,
    char_p,
    void_pp,
    int_pp,
    double_pp,
    char_pp
};

struct array {
    int rows;
    int columns;
    size_t size_of_elem;
    enum type t;
    union mas_p mas;
};

union sum {
    int i_sum;
    double d_sum;
    int c_sum;
};

/* source.c */
bool check_args(int, char *[]);
bool create_array(struct array *);
void set_ts(int, struct array *, int);
void input_param(struct array *, int);
void input_array(struct array *);
void print_array(struct array *);
void sum_of_row(struct array *);
void delete_array(struct array *);
void arr_err(void);

#endif //LAB_DEV_SOURCE_H
