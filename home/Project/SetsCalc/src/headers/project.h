/* 
SetsCalc — powerful sets calculator
Copyright © 2018 Anton

This file is part of SetsCalc.

SetsCalc is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

SetsCalc is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with SetsCalc. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef PROJECT_PROJECT_H
#define PROJECT_PROJECT_H

/* Definitions */
#define TITLE ("Sets calculator")
#define NAME (1024)
#define INT_ALL ("{x ∈ N | -∞ < x < +∞ }")
#define ABS(X) ((X) < 0) ? (-(X)) : (X)
#define ERROR_MSG ("Error! Illegal expression!")
#define ERROR_MSG_FILE ("Error! Couldn\'t open file!")
#define ERROR_TREE ("Error! Binary tree problems!")
#define NONE_STR ("awhbfdj")
#define HELP_FILE ("files/help.txt")
#define LEFT_TREE (p->left = maketree(p->left, exprl, sets))
#define RIGHT_TREE (p->right = maketree(p->right, exprr, sets))

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
#include "../../config.h"

/* main.c */
void lclear(void); /* Clears console after completing */

/* menu.c */
int set_sets(char *, char *, char *); /* First menu. Gets valid sets */
void rep_str(char *); /* Removes white spaces from (char *) */
int check(char *); /* Returns zero if input is invalid */
int numcmp(char *, char *); /* Compares two (char *) numerically */
void output(char *, const char *, const char *, const char *); /* Makes up a set */
void str_err(const char *); /* Pops an error message with text (const char *) */
void file_get_str(char *, const char *); /* Gets string from file. Calls str_err, if file opening error occurs or string is not valid at some point */
char *find_str(FILE *, char *, const char *, const char *); /* Finds a first string, that contains (char *) pattern but doesn't contain (char *) and (char *) patterns */
void rand_get_str(char *); /* Fill the set up with N pseudo-random numbers from A to B */
int str_chr_cnt(const char *, char); /* Counts the number of occurrences of (char) in (const char *) */
int str_get_num(const char *); /* Returns the first integer from (const char *) if (const char *) is valid*/
int numlen(int); /* Returns length of a number. Add one, if number is negative */
void get_set(char *, const int *, const int *); /* Gets (const int *) elements from (const int *) and puts it into (char *) */
int num_cmp(const void *, const void *); /* Compares two integers */
char *get_elem(const int *); /* Returns (char *) to first element of (const int *) */
int numlen_int(int); /* Returns length of a number */
int find_sht(const int *, int, int); /* Return zero if element (int) doesn't occur in (const int *) with length (int) */
void fix_str_rpt(char *); /* Removes repeating elements */

/* menu2.c */
int set_expr(char *); /* Second menu. Gets a valid expression */
int check2(const char *); /* Returns zero if expression isn't valid */
void expr_err(const char *); /* Pops an error message with text (const char *) */

/* menu3.c */
int prt_res(const char *); /* Third menu. Outputs the result */
int cont(void); /* Fourth (last) menu. «Continue» option */

/* tree.c */
struct tnode { /* Structure for binary tree */
	char *op;
	struct tnode *left;
	struct tnode *right;
};
struct set { /* Structure for sets */
	char *a;
	char *b;
	char *c;
};
struct tnode *talloc(void); /* Allocates memory from heap to one node of binary tree */
struct tnode *maketree(struct tnode *, char *, const struct set *); /* Returns a pointer to binary tree */
int de_par(char *); /* Returns zero if none parentheses were removed */
char *find_op(const char *); /* Returns (char *) to necessary operator from (const char *) */
int isop(char); /* Returns zero if (char) isn't an operator */
char *derefer(const char *, const struct set *); /* Returns set (const char *) */
int check_prec(const char *); /* Returns correct operator precedence */

/* math.c */
char *sum(const char *, const char *, int); /* Sums two sets [(const char *) and (const char *)] */
void to_neg(char *); /* Changes (char *)'s sign from + to - or vice versa */
void to_opp(char *, int); /* Converts (char *) to (int) type (zero — inclusive, one — exclusive) */
char *mul(char *, char *, int); /* Multiplies two sets [(const char *) and (const char *)] */
char *sub(char *, char *, int); /* Subtracts two sets [(const char *) and (const char *)] */

#endif
