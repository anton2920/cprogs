#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"
#include <sys/time.h>

#define N (20)
#define LIM (50)

void rand_array(int *, int, int);
void demo_basic_sort(int *, __bool);
void demo_adv_sort(int *, __bool);

main() {

    /* Initializing variables */
    auto int i;
    auto int source[N];
    __bool is_print = __true;

    srand(time(NULL) / 2);

    /* I/O flow */
    rand_array(source, N, LIM);
    if (is_print) {
        printf("Source array: \t\t");
        for (i = 0; i < N; ++i) {
            printf("%d ", *(source + i));
        }
        fflush(stdout);
    }

    /* Main part */
    demo_basic_sort(source, is_print);
    demo_adv_sort(source, is_print);

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
        /* *(a + i) = lim--; */
    }
}

void demo_basic_sort(int *source, __bool is_print) {

    /* Initializing variables */
    auto int i, a[N];
    auto struct timeval stop, start;
    auto double time_in_mill, time_in_mill2;

    /* Main part */
    copy_arr((void *) a, (const void *) source, N, sizeof(int));
    gettimeofday(&start, NULL);
    bubble_sort((void *) a, N, sizeof(int), inumcmp);
    gettimeofday(&stop, NULL);

    time_in_mill = (start.tv_sec) * 1000 + (double) (start.tv_usec) / 1000;
    time_in_mill2 = (stop.tv_sec) * 1000 + (double) (stop.tv_usec) / 1000;

    printf("\n\nBubble sort: \t\t");
    if (is_print) {
        for (i = 0; i < N; ++i) {
            printf("%d ", *(a + i));
        }
    }
    printf("\nTime: %.2lf ms\n", time_in_mill2 - time_in_mill);
    fflush(stdout);

    copy_arr((void *) a, (const void *) source, N, sizeof(int));
    gettimeofday(&start, NULL);
    selection_sort((void *) a, N, sizeof(int), inumcmp);
    gettimeofday(&stop, NULL);

    time_in_mill = (start.tv_sec) * 1000 + (double) (start.tv_usec) / 1000;
    time_in_mill2 = (stop.tv_sec) * 1000 + (double) (stop.tv_usec) / 1000;

    printf("\nSelection sort: \t");
    if (is_print) {
        for (i = 0; i < N; ++i) {
            printf("%d ", *(a + i));
        }
    }
    printf("\nTime: %.2lf ms\n", time_in_mill2 - time_in_mill);
    fflush(stdout);

    copy_arr((void *) a, (const void *) source, N, sizeof(int));
    gettimeofday(&start, NULL);
    insertion_sort((void *) a, N, sizeof(int), inumcmp);
    gettimeofday(&stop, NULL);

    time_in_mill = (start.tv_sec) * 1000 + (double) (start.tv_usec) / 1000;
    time_in_mill2 = (stop.tv_sec) * 1000 + (double) (stop.tv_usec) / 1000;

    printf("\nInsertion sort: \t");
    if (is_print) {
        for (i = 0; i < N; ++i) {
            printf("%d ", *(a + i));
        }
    }
    printf("\nTime: %.2lf ms\n", time_in_mill2 - time_in_mill);
    fflush(stdout);

    copy_arr((void *) a, (const void *) source, N, sizeof(int));
    gettimeofday(&start, NULL);
    shell_sort((void *) a, N, sizeof(int), inumcmp);
    gettimeofday(&stop, NULL);

    time_in_mill = (start.tv_sec) * 1000 + (double) (start.tv_usec) / 1000;
    time_in_mill2 = (stop.tv_sec) * 1000 + (double) (stop.tv_usec) / 1000;

    printf("\nShell sort: \t\t");
    if (is_print) {
        for (i = 0; i < N; ++i) {
            printf("%d ", *(a + i));
        }
    }
    printf("\nTime: %.2lf ms\n", time_in_mill2 - time_in_mill);
    fflush(stdout);
}

void demo_adv_sort(int *source, __bool is_print) {

    /* Initializing variables */
    auto int i, a[N];
    auto struct timeval stop, start;
    auto double time_in_mill, time_in_mill2;

    /* Main part */
    copy_arr(a, source, N, sizeof(int));
    gettimeofday(&start, NULL);
    quick_sort((void *) a, N, sizeof(int), inumcmp);
    gettimeofday(&stop, NULL);

    time_in_mill = (start.tv_sec) * 1000 + (double) (start.tv_usec) / 1000;
    time_in_mill2 = (stop.tv_sec) * 1000 + (double) (stop.tv_usec) / 1000;

    printf("\nQuick sort: \t\t");
    if (is_print) {
        for (i = 0; i < N; ++i) {
            printf("%d ", *(a + i));
        }
    }
    printf("\nTime: %.2lf ms\n", time_in_mill2 - time_in_mill);
    fflush(stdout);

    copy_arr(a, source, N, sizeof(int));
    gettimeofday(&start, NULL);
    merge_sort((void *) a, N, sizeof(int), inumcmp);
    gettimeofday(&stop, NULL);

    time_in_mill = (start.tv_sec) * 1000 + (double) (start.tv_usec) / 1000;
    time_in_mill2 = (stop.tv_sec) * 1000 + (double) (stop.tv_usec) / 1000;

    printf("\nMerge sort: \t\t");
    if (is_print) {
        for (i = 0; i < N; ++i) {
            printf("%d ", *(a + i));
        }
    }
    printf("\nTime: %.2lf ms\n", time_in_mill2 - time_in_mill);
    fflush(stdout);
}