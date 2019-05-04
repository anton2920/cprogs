/*
Sorting library — free shared library, that contains a few general-purpose sorting algorithms
Copyright © Pavlovsky Anton, 2019

This file is part of Sorting library.

Sorting library is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Sorting library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Sorting library. If not, see <https://www.gnu.org/licenses/>.
*/

#include "sorting.h"

/* String to ... */
double atof(const char *n) {

    /* Initializing variables */
    auto int a = 0, b = 0, sign = 1;
    auto bool comma = false;

    /* Main part */
    while (*n) {
        if (*n == '-') {
            sign = -1;
        } else if (*n == '+') {
            sign = 1;
        } else if (*n == '.') {
            comma = true;
        }
        if (isdigit(*n)) {
            if (comma) {
                b *= 10;
                b += *n - '0';
            } else {
                a *= 10;
                a += *n - '0';
            }
        }
        ++n;
    }

    a *= sign;

    /* Returning value */
    return (b == 0) ? (double) a : (double) a / (double) b;
}

int atoi(const char *n) {

    /* Initializing variables */
    auto int a = 0, sign = 1;

    /* Main part */
    while (*n) {
        if (*n == '-') {
            sign = -1;
            continue;
        } else if (*n == '+') {
            sign = 1;
            continue;
        }

        if (isdigit(*n)) {
            a *= 10;
            a += *n - '0';
            ++n;
        } else {
            break;
        }
    }

    /* Returning value */
    return a * sign;
}

/* Basic functions for compare */
int strcmp(const char *str1, const char *str2) {

    /* Compares two strings lexicographically */

    /* Main part */
    for ( ; *str1 && *str2; ++str1, ++str2) {
        if (*str1 != *str2) {
            break;
        }
    }

    /* Returning value */
    return (*str1 > *str2) ? GREATER : (*str1 < *str2) ? LESS : EQUALS;
}

int numcmp(const char *num1, const char *num2) {

    /* Compares two strings numerically */

    /* Initializing variables */
    auto double d1 = atof(num1), d2 = atof(num2);

    /* Returning value */
    return (d1 > d2) ? GREATER : (d1 < d2) ? LESS : EQUALS;
}

int inumcmp(const void *num1, const void *num2) {

    /* Compares integers */

    /* Initializing variables */
    auto int d1 = *((int *) num1), d2 = *((int *) num2);

    /* Returning value */
    return (d1 > d2) ? GREATER : (d1 < d2) ? LESS : EQUALS;
}

int dnumcmp(const void *num1, const void *num2) {

    /* Compares doubles */

    /* Initializing variables */
    auto double d1 = *((double *) num1), d2 = *((double *) num2);

    /* Returning value */
    return (d1 > d2) ? GREATER : (d1 < d2) ? LESS : EQUALS;
}

/* Miscellaneous routines */


/* Basic sorting algorithms */
void bubble_sort(void *pbase, int n, int nbytes, int (*cmp)(const void *, const void *)) {

    /* Initializing variables */
    register int i, j;
    auto char *p = (char *) pbase;
    auto bool is_swapped;

    /* Main part */
    for (i = 1; i < n; ++i) {
        is_swapped = false;
        for (j = 0; j < n - i; ++j) {
            if ((*cmp)((const void *) (p + j * nbytes), (const void *) (p + (j + 1) * nbytes)) > 0) {
                SWAP((p + j * nbytes), (p + (j + 1) * nbytes), nbytes);
                is_swapped = true;
            }
        }

        if (!is_swapped) {
            break;
        }
    }
}

void selection_sort(void *pbase, int n, int nbytes, int (*cmp)(const void *, const void *)) {

    /* Initializing variables */
    register int i, j, min_index = 0;
    auto char *p = (char *) pbase;

    /* Main part */
    for (i = 0; i < n - 1; ++i) {
        min_index = i;
        for (j = i + 1; j < n; ++j) {
            if ((*cmp)((const void *) (p + j * nbytes), (const void *) (p + min_index * nbytes)) < 0) {
                min_index = j;
            }
        }

        if (i != min_index) {
            SWAP((p + i * nbytes), (p + min_index * nbytes), nbytes);
        }
    }
}

void insertion_sort(void *pbase, int n, int nbytes, int (*cmp)(const void *, const void *)) {

    /* Initializing variables */
    register int i, j;
    auto char *p = (char *) pbase;

    /* Main part */
    for (i = 1; i < n; ++i) {
        for (j = i - 1; j >= 0 &&
            (*cmp)((const void *) (p + (j + 1) * nbytes), (const void *) (p + j * nbytes)) < 0; --j) {
            SWAP((p + (j + 1) * nbytes), (p + j * nbytes), nbytes);
        }
    }
}

/* Advanced sorting algorithms */
