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