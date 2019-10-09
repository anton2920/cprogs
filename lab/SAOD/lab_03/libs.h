#ifndef LAB_DEV_LIBS_H
#define LAB_DEV_LIBS_H

/* Header inclusions */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/anton/C/home/STL2/src/STL.h"

/* Macro definitions */


/* Type definitions */
struct poly {
    int coefficient;
    size_t power;
};

/* Functions declarations */
void read_polynomials(STL_List *, FILE *);
void print_polynomials(STL_List *, FILE *);
void add_polynomials(STL_List *result, STL_List *this, STL_List *other);
void multiply_polynomials(STL_List *result, STL_List *this, STL_List *other);

#endif