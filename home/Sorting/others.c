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

/* Miscellaneous routines */
void copy_arr(void *a, const void *b, int n, int nbytes) {

    /* Initializing variables */
    auto int i;
    auto char *arr = (char *) a;
    auto char *brr = (char *) b;

    /* Main part */
    for (i = 0; i < n; ++i) {
        COPY((arr + i * nbytes), (brr + i * nbytes), nbytes);
    }
}

void *binary_search(const void *key, const void *pbase, int n, int nbytes, int (*cmp)(const void *, const void *)) {

    /* Initializing variables */
    auto const char *p = (char *) pbase, *pivot = NULL;
    int res;

    /* Main part */
    for ( ; n > 0; n >>= 1) {
        pivot = pbase + (n >> 1) * nbytes;
        if (!(res = (*cmp)(key, (const void *) pivot))) {
            return (void *) pivot;
        }

        if (res > 0) {
            pbase = pivot + nbytes;
            --n;
        }
    }

    /* Returning value */
    return NULL;
}