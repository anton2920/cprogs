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
static void *pivot_arr (void *arr, int nbytes, int low, int high, int (*cmp)(const void *, const void *)) {

    /* This functions is used for taking a choice for a pivot and rearranging
     * array, that elements smaller than a pivot go to left of pivot, and all greater
     * elements go to right of pivot */

    /* Initializing variables */
    auto char *p = (char *) arr;
    auto char *x = p + high * nbytes;
    register int i = low - 1, j, res = 0;

    /* Main part */
    for (j = low; j <= high - 1; ++j) {
        if ((*cmp)((const void *) (p + j * nbytes), (const void *) (x)) <= 0) {
            ++i;
            SWAP((p + i * nbytes), (p + j * nbytes), nbytes);
        }
    }
    SWAP((p + (i + 1) * nbytes), x, nbytes);

    /* Returning value */
    return (void *) (p + (i + 1) * nbytes);
}

static void merge(void *pbase, int nbytes, int left, int mid, int right, int (*cmp)(const void *, const void *)) {

    /* Initializing variables */
    auto char *p = (char *) pbase;
    register int i, j, k;
    auto int n1 = mid - left + 1, n2 = right - mid;

    auto char L[n1 * nbytes], R[n2 * nbytes];

    /* Main part */
    for (i = 0; i < n1; ++i) {
        COPY((L + i * nbytes), (p + (left + i) * nbytes), nbytes);
    }
    for (j = 0; j < n2; ++j) {
        COPY((R + j * nbytes), (p + (mid + 1 + j) * nbytes), nbytes);
    }

    for (i = 0, j = 0, k = left; i < n1 && j < n2; ) {
        if ((*cmp)((const void *) (L + i * nbytes), (const void *) (R + j * nbytes)) <= 0) {
            COPY((p + k * nbytes), (L + i * nbytes), nbytes);
            ++i;
        } else {
            COPY((p + k * nbytes), (R + j * nbytes), nbytes);
            ++j;
        }
        ++k;
    }

    for ( ; i < n1; ++i, ++k) {
        COPY((p + k * nbytes), (L + i * nbytes), nbytes);
    }

    for ( ; j < n2; ++j, ++k) {
        COPY((p + k * nbytes), (R + j * nbytes), nbytes);
    }
}

/* Advanced sorting algorithms */
void quick_sort(void *pbase, int n, int nbytes, int (*cmp)(const void *, const void *)) {

    /* Initializing variables */
    auto char *base_ptr = (char *) pbase, *piv = NULL;
    auto char *lo = base_ptr;
    auto char *hi = &lo[nbytes * (n - 1)];

    /* Auxiliary stack sh**t */
    auto char *stack[(hi - lo) + 1];
    register int top = -1;

    stack[++top * nbytes] = lo;
    stack[++top * nbytes] = hi;

    /* Main part */
    for ( ; top >= 0; ) {
        hi = stack[top-- * nbytes];
        lo = stack[top-- * nbytes];

        piv = pivot_arr(pbase, nbytes, (lo - base_ptr) / nbytes, (hi - base_ptr) / nbytes, cmp);

        if (piv - nbytes > lo) {
            stack[++top * nbytes] = lo;
            stack[++top * nbytes] = piv - nbytes;
        }

        if (piv + nbytes < hi) {
            stack[++top * nbytes] = piv + nbytes;
            stack[++top * nbytes] = hi;
        }
    }
}

void merge_sort(void *pbase, int n, int nbytes, int (*cmp)(const void *, const void *)) {

    /* Initializing variables */
    register int curr_size, left_start;

    auto int mid, right_end;

    /* Main part */
    for (curr_size = 1; curr_size <= n - 1; curr_size <<= 1) {
        for (left_start = 0; left_start < n - 1; left_start += curr_size << 1) {
            mid = left_start + curr_size - 1;
            right_end = MIN((left_start + (curr_size << 1) - 1), n - 1);

            if (mid >= right_end) {
                break;
            }
            merge(pbase, nbytes, left_start, mid, right_end, cmp);
        }
    }
}