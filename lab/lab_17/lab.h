#ifndef LAB_17_DEV_LAB_H
#define LAB_17_DEV_LAB_H

#define MAXSIZE (1024)
#define NAME (21)

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

struct arr {
    int array[MAXSIZE][MAXSIZE]; /* Array itself */
    int n; /* Number of rows */
    int m; /* Number of columns */
};

/* menu.c */
void prt_ln(void);
void no_cmd(void);
int quit_m(void);
int menu(int *, int *);
int menu2(void);
void menu2_5(int *, int *);
int menu3(void);

/* rwr.c */
void read_key(struct arr *);
void read_rand(struct arr *);
void read_file(struct arr *);
void read_formula(struct arr *);
void write_scr(const struct arr *);
void write_file(const struct arr *);

#endif