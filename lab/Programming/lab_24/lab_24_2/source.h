#ifndef LAB_DEV_SOURCE_H
#define LAB_DEV_SOURCE_H

/* Header inclusion */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Types */
typedef enum {
    false,
    true
} bool;

struct student {
    int num_of_mks;
    int *mks_pt;
    double ar_mean;
    bool lt3;
    bool gs_mks;
};

struct group_l {
    int number;
    struct student **mas;
};

/* source.c */
bool create_st_l(struct group_l *);
bool read_stuff(struct group_l *);
void arr_err(void);
void read_arr(struct group_l *);
void find_ar_mean(struct group_l *);
void find_lt3(struct group_l *);
void find_gs_mks(struct group_l *);
void delete_arr(struct group_l *);

#endif //LAB_DEV_SOURCE_H
