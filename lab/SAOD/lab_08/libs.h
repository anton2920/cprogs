#ifndef LAB_DEV_LIBS_H
#define LAB_DEV_LIBS_H

/* Header inclusion */
#include <stdio.h>
#include <stdlib.h>

/* New datatypes */
enum COLORS {
    RED = 0,
    WHITE,
    BLUE
};

/* Variable declaration */
extern int moveCount;

/* Functions' declarations */
int min(int a, int b);
void iswap(int a, int b, int *pInt);
void generateArray(int *x, int n);
void printArray(FILE *fp, int *x, int n);

void partitioning(int *x, int n);

#endif
