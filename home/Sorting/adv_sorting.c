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
        if ((res = (*cmp)((const void *) (p + j * nbytes), (const void *) (x))) < 0 || !res) {
            ++i;
            SWAP((p + i * nbytes), (p + j * nbytes), nbytes);
        }
    }
    SWAP((p + (i + 1) * nbytes), x, nbytes);

    /* Returning value */
    return (void *) (p + (i + 1) * nbytes);
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