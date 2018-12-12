#ifndef PROJECT_PROJECT_H
#define PROJECT_PROJECT_H

#define TITLE ("Sets calculator")
#define NAME (100)
#define NATURAL_ALL ("{x ∈ N | -∞ < x < +∞ }")
#define ABS(X) ((X) < 0) ? (-(X)) : (X)
#define ERROR_MSG ("Error! Illegal expression!")
#define ERROR_MSG_FILE ("Error! Couldn\'t open file!")
#define NONE_STR ("awhbfdj")

#ifdef _WIN32
#define COMM ("cls")
#endif

#ifdef __unix__
#define COMM ("clear")
#endif

#include <stdio.h>
#include <dialog.h>
#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

/* main.c */
void lclear(void);

/* menu.c */
int set_sets(char *, char *, char *);
void rep_str(char *);
int check(char *);
int numcmp(char *, char *);
void output(char *, const char *, const char *, const char *);
void str_err(const char *);
void file_get_str(char *, const char *);
char *find_str(FILE *, char *, const char *, const char *);
void rand_get_str(char *);
int str_chr_cnt(const char *, char);
int str_get_num(const char *);
int numlen(int);
void get_set(char *str, const int *, const int *);
int num_cmp(const void *, const void *);
char *get_elem(const int *);
int numlen_int(int);

/* menu2.c */
int set_expr(char *);
int check2(char *);

/* menu3.c */
int prt_res(char *);
int cont(void);

/* tree.c */
struct tnode {
	char *op;
	struct tnode *parent;
	struct tnode *left;
	struct tnode *right;
};
struct tnode *talloc(void);
struct tnode *maketree(struct tnode *, char *, int *);

#endif
