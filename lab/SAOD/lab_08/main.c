#include <stdio.h>

#include "libs.h"

int main() {

    /* Initializing variables */
    auto int *p, n;

    /* I/O flow */
    printf("Type the number of elements: ");
    scanf("%d", &n);

    /* Main part */
    if ((p = calloc(n, sizeof(int))) == NULL) {
        return -1;
    }

    generateArray(p, n);

    printArray(stdout, p, n);

    partitioning(p, n);

    printArray(stdout, p, n);

    /* Final output */
    printf("Number of swaps: %d\n", moveCount);

    /* Returning value */
    return 0;
}