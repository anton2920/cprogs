#ifndef PROJECT_PROJECT_H
#define PROJECT_PROJECT_H

#define TITLE ("Sets calculator")
#define NAME (100)

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

/* main.c */
void lclear(void);

/* menu.c */
int set_sets(char *, char *, char *);
void rep_str(char *);
int check(char *);

/* menu2.c */
int set_expr(char *);

#endif
