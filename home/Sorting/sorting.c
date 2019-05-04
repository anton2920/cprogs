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