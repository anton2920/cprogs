#ifndef PROJECT_PROJECT_H
#define PROJECT_PROJECT_H

/* Definitions */
#define TITLE ("Sets calculator")
#define NAME (100)
#define NATURAL_ALL ("{x ∈ N | -∞ < x < +∞ }")
#define ABS(X) ((X) < 0) ? (-(X)) : (X)
#define ERROR_MSG ("Error! Illegal expression!")
#define ERROR_MSG_FILE ("Error! Couldn\'t open file!")
#define NONE_STR ("awhbfdj")
#define HELP_FILE ("files/help.txt")

/* For correct terminal clearing */
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
void lclear(void); /* Clears console after completing */

/* menu.c */
int set_sets(char *, char *, char *); /* First menu. Gets valid sets */
void rep_str(char *); /* Removes white spaces from (char *) */
int check(char *); /* Returns zero if input is invalid */
int numcmp(char *, char *); /* Compares two (char *) numerically */
void output(char *, const char *, const char *, const char *); /* Makes up a set */
void str_err(const char *); /* Pops an error message */
void file_get_str(char *, const char *); /* Gets string from file. Calls str_err, if file opening error occurs or string is not valid at some point */
char *find_str(FILE *, char *, const char *, const char *); /* Finds a first string, that contains (char *) pattern but doesn't contain (char *) and (char *) patterns */
void rand_get_str(char *); /* Fill the set up with N pseudo-random numbers from A to B */
int str_chr_cnt(const char *, char); /* Counts the number of occurences of (char) in (const char *) */
int str_get_num(const char *); /* Returns the first integer from (const char *) if (const char *) is valid*/
int numlen(int); /* Returns length of a number. Add one, if number is negative */
void get_set(char *, const int *, const int *); /* Gets (const int *) elements from (const int *) and puts it into (char *) */
int num_cmp(const void *, const void *); /* Compares two integers */
char *get_elem(const int *); /* Returns (char *) to first emlement of (const int *) */
int numlen_int(int); /* Returns length of a number */
int find_sht(const int *, int, int); /* Return zero if element (int) doesn't occur in (const int *) with length (int) */
void fix_str_rpt(char *); /* Removes repeating elements */

/* menu2.c */
int set_expr(char *); /* Second menu. Gets a valid expression */
int check2(char *); /* Returns zero if expression isn't valid */

/* menu3.c */
int prt_res(char *); /* Third menu. Outputs the result */
int cont(void); /* Fourth (last) menu. «Continue» option */

/* tree.c */
struct tnode { /* Struct for binary tree */
	char *op;
	struct tnode *parent;
	struct tnode *left;
	struct tnode *right;
};
struct tnode *talloc(void); /* Allocates memory from heap to one node of binary tree */
struct tnode *maketree(struct tnode *, char *, int *); /* Returns a pointer to binary tree */

#endif
