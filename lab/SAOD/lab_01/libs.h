#ifndef LAB_DEV_LIBS_H
#define LAB_DEV_LIBS_H

/* Header inclusions */
#include <stdio.h>
#include <string.h>

/* Constants */
enum consts {
    faces = 6
};

/* libs.c */
unsigned long int findRecursive(int m, int n, int x);
unsigned long int findIterative(int m, int n, int x);
unsigned long int findOptimized(int m, int n, int x);

void prt_ln(void);
int menu_continue(void);

#endif
