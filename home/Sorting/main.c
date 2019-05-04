#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"

#define N (10)

main() {

    /* Initializing variables */
    auto int i;
    auto int a[N], b[N], c[N];

    /* Random stuff */
    srand(time(NULL));

    /* I/O flow */
    printf("Source array: \t");
    for (i = 0; i < N; ++i) {
        printf("%d ", *(a + i));
    }

    bubble_sort((int *) a, N, sizeof(int), inumcmp);
    printf("\nBubble sort: \t");
    for (i = 0; i < N; ++i) {
        printf("%d ", *(a + i));
    }
    fflush(stdout);

    selection_sort((int *) b, N, sizeof(int), inumcmp);
    printf("\nSelect sort: \t");
    for (i = 0; i < N; ++i) {
        printf("%d ", *(b + i));
    }
    fflush(stdout);

    insertion_sort((int *) c, N, sizeof(int), inumcmp);
    printf("\nInsert sort: \t");
    for (i = 0; i < N; ++i) {
        printf("%d ", *(c + i));
    }
    fflush(stdout);

    /* Final output */
    printf("\n");

    /* Returning value */
    return 0;
}

void rand_array(int *a, int *b, int *c) {

    /* Initializing variables */
}