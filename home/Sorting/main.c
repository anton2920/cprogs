#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"
#include <sys/time.h>

#define N (20)
#define LIM (100)

void rand_arrays(int *, int *, int *, int *, int *, int);
void rand_darrays(double *, double *, double *, double *, double *, int);

main() {

    /* Initializing variables */
    auto int i;
    auto int a[N], b[N], c[N], d[N], e[N];
    /* auto double a[N], b[N], c[N], d[N], e[N]; */
    auto struct timeval stop, start;
    auto double time_in_mill, time_in_mill2;

    srand(time(NULL) / 2);
    rand_arrays(a, b, c, d, e, N);
    /* rand_darrays(a, b, c, d, e, N); */

    /* I/O flow */
    printf("Source array: \t");
    for (i = 0; i < N; ++i) {
        printf("%d ", *(a + i));
    }
    fflush(stdout);

    gettimeofday(&start, NULL);
    bubble_sort((void *) a, N, sizeof(int), inumcmp);
    gettimeofday(&stop, NULL);

    time_in_mill = (start.tv_sec) * 1000 + (start.tv_usec) / 1000 ;
    time_in_mill2 = (stop.tv_sec) * 1000 + (stop.tv_usec) / 1000 ;

    printf("\n\nBubble sort: \t\t");
    for (i = 0; i < N; ++i) {
        printf("%d ", *(a + i));
    }
    printf("\nTime: %lf\n", time_in_mill2 - time_in_mill);
    fflush(stdout);

    gettimeofday(&start, NULL);
    selection_sort((void *) b, N, sizeof(int), inumcmp);
    gettimeofday(&stop, NULL);

    time_in_mill = (start.tv_sec) * 1000 + (start.tv_usec) / 1000 ;
    time_in_mill2 = (stop.tv_sec) * 1000 + (stop.tv_usec) / 1000 ;

    printf("\nSelection sort: \t");
    for (i = 0; i < N; ++i) {
        printf("%d ", *(b + i));
    }
    printf("\nTime: %lf\n", time_in_mill2 - time_in_mill);
    fflush(stdout);

    gettimeofday(&start, NULL);
    insertion_sort((void *) c, N, sizeof(int), inumcmp);
    gettimeofday(&stop, NULL);

    time_in_mill = (start.tv_sec) * 1000 + (start.tv_usec) / 1000 ;
    time_in_mill2 = (stop.tv_sec) * 1000 + (stop.tv_usec) / 1000 ;

    printf("\nInsertion sort: \t");
    for (i = 0; i < N; ++i) {
        printf("%d ", *(c + i));
    }
    printf("\nTime: %lf\n", time_in_mill2 - time_in_mill);
    fflush(stdout);

    gettimeofday(&start, NULL);
    quick_sort((void *) d, N, sizeof(int), inumcmp);
    gettimeofday(&stop, NULL);

    time_in_mill = (start.tv_sec) * 1000 + (start.tv_usec) / 1000 ;
    time_in_mill2 = (stop.tv_sec) * 1000 + (stop.tv_usec) / 1000 ;

    printf("\nQuick sort: \t\t");
    for (i = 0; i < N; ++i) {
        printf("%d ", *(d + i));
    }
    printf("\nTime: %lf\n", time_in_mill2 - time_in_mill);
    fflush(stdout);

    gettimeofday(&start, NULL);
    merge_sort((void *) e, N, sizeof(int), inumcmp);
    gettimeofday(&stop, NULL);

    time_in_mill = (start.tv_sec) * 1000 + (start.tv_usec) / 1000 ;
    time_in_mill2 = (stop.tv_sec) * 1000 + (stop.tv_usec) / 1000 ;

    printf("\nMerge sort: \t\t");
    for (i = 0; i < N; ++i) {
        printf("%d ", *(e + i));
    }
    printf("\nTime: %lf\n", time_in_mill2 - time_in_mill);
    fflush(stdout);

    /* Final output */
    printf("\n");

    /* Returning value */
    return 0;
}

void rand_arrays(int *a, int *b, int *c, int *d, int *e, int n) {

    /* Initializing variables */
    register int i, curr_val;

    for (i = 0; i < n; ++i) {
        curr_val = (rand() % (2 * LIM + 1)) - LIM;
        *(a + i) = *(b + i) = *(c + i) = *(d + i) = *(e + i) = curr_val;
    }
}

void rand_darrays(double *a, double *b, double *c, double *d, double *e, int n) {

    /* Initializing variables */
    register int i;
    auto double curr_val;

    for (i = 0; i < n; ++i) {
        curr_val = ((rand() % (2 * LIM + 1)) - LIM) * 1.0 / ((rand() % (2 * LIM + 1)) - LIM);
        *(a + i) = *(b + i) = *(c + i) = *(d + i) = *(e + i) = curr_val;
    }
}