#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"
#include <sys/time.h>

#define N (99999)
#define LIM (1000000)

void rand_array(int *, int, int);

main() {

    /* Initializing variables */
    auto int i;
    auto int a[N], b[N], c[N], d[N], e[N];
    /* auto double a[N], b[N], c[N], d[N], e[N]; */

    srand(time(NULL) / 2);

    /* I/O flow */


    gettimeofday(&start, NULL);
    quick_sort((void *) d, N, sizeof(int), inumcmp);
    gettimeofday(&stop, NULL);

    time_in_mill = (start.tv_sec) * 1000 + (double) (start.tv_usec) / 1000;
    time_in_mill2 = (stop.tv_sec) * 1000 + (double) (stop.tv_usec) / 1000;

    printf("\nQuick sort: \t\t");
    /*for (i = 0; i < N; ++i) {
        printf("%d ", *(d + i));
    }*/
    printf("\nTime: %.2lf ms\n", time_in_mill2 - time_in_mill);
    fflush(stdout);

    gettimeofday(&start, NULL);
    merge_sort((void *) e, N, sizeof(int), inumcmp);
    gettimeofday(&stop, NULL);

    time_in_mill = (start.tv_sec) * 1000 + (double) (start.tv_usec) / 1000;
    time_in_mill2 = (stop.tv_sec) * 1000 + (double) (stop.tv_usec) / 1000;

    printf("\nMerge sort: \t\t");
    /*for (i = 0; i < N; ++i) {
        printf("%d ", *(e + i));
    }*/
    printf("\nTime: %.2lf ms\n", time_in_mill2 - time_in_mill);
    fflush(stdout);

    /* Final output */
    printf("\n");

    /* Returning value */
    return 0;
}

void rand_array(int *a, int n, int lim) {

    /* Initializing variables */
    auto int i;

    /* Main part */
    for (i = 0; i < n; ++i) {
        *(a + i) = rand() % (2 * lim + 1) - lim;
    }
}

void demo_basic_sort(bool is_print) {

    /* Initializing variables */
    auto int i, source[N], a[N];
    auto struct timeval stop, start;
    auto double time_in_mill, time_in_mill2;

    /* Main part */
    rand_array(source, N, LIM);
    copy_arr((void *) a, (const void *) source, N, sizeof(int));

    if (is_print) {
        printf("Source array: \t");
        for (i = 0; i < N; ++i) {
            printf("%d ", *(a + i));
        }
        fflush(stdout);
    }

    gettimeofday(&start, NULL);
    bubble_sort((void *) a, N, sizeof(int), inumcmp);
    gettimeofday(&stop, NULL);

    time_in_mill = (start.tv_sec) * 1000 + (double) (start.tv_usec) / 1000;
    time_in_mill2 = (stop.tv_sec) * 1000 + (double) (stop.tv_usec) / 1000;

    printf("\n\nBubble sort: \t\t");
    /*for (i = 0; i < N; ++i) {
        printf("%d ", *(a + i));
    }*/
    printf("\nTime: %.2lf ms\n", time_in_mill2 - time_in_mill);
    fflush(stdout);

    gettimeofday(&start, NULL);
    selection_sort((void *) b, N, sizeof(int), inumcmp);
    gettimeofday(&stop, NULL);

    time_in_mill = (start.tv_sec) * 1000 + (double) (start.tv_usec) / 1000;
    time_in_mill2 = (stop.tv_sec) * 1000 + (double) (stop.tv_usec) / 1000;

    printf("\nSelection sort: \t");
    /*for (i = 0; i < N; ++i) {
        printf("%d ", *(b + i));
    }*/
    printf("\nTime: %.2lf ms\n", time_in_mill2 - time_in_mill);
    fflush(stdout);

    gettimeofday(&start, NULL);
    insertion_sort((void *) c, N, sizeof(int), inumcmp);
    gettimeofday(&stop, NULL);

    time_in_mill = (start.tv_sec) * 1000 + (double) (start.tv_usec) / 1000;
    time_in_mill2 = (stop.tv_sec) * 1000 + (double) (stop.tv_usec) / 1000;

    printf("\nInsertion sort: \t");
    /*for (i = 0; i < N; ++i) {
        printf("%d ", *(c + i));
    }*/
    printf("\nTime: %.2lf ms\n", time_in_mill2 - time_in_mill);
    fflush(stdout);
}