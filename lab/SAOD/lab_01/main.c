#include "libs.h"
#include <sys/time.h>

main() {

    /* Initializing variables */
    auto int n, m;
    auto unsigned long int ways;
    auto struct timeval stop, start;
    auto double time_in_mill, time_in_mill2;

    /* Main part */
    do {
        do {
            printf("| Type n (number of dices): ");
            scanf("%d", &n);
        } while (n <= 0);

        do {
            printf("| Type m (desirable sum): ");
            scanf("%d", &m);
        } while (m <= 0);

        prt_ln();

        /* Main part */
        gettimeofday(&start, NULL);
        ways = findRecursive(faces, n, m);
        gettimeofday(&stop, NULL);

        time_in_mill = (double) (start.tv_sec) * 1000 + (double) (start.tv_usec) / 1000;
        time_in_mill2 = (double) (stop.tv_sec) * 1000 + (double) (stop.tv_usec) / 1000;

        printf("| Recursive approach:\t%lu, time elapsed: %lf\n", ways, time_in_mill2 - time_in_mill);

        gettimeofday(&start, NULL);
        ways = findIterative(faces, n, m);
        gettimeofday(&stop, NULL);

        time_in_mill = (double) (start.tv_sec) * 1000 + (double) (start.tv_usec) / 1000;
        time_in_mill2 = (double) (stop.tv_sec) * 1000 + (double) (stop.tv_usec) / 1000;

        printf("| Iterative approach:\t%lu, time elapsed: %lf\n", ways, time_in_mill2 - time_in_mill);

        gettimeofday(&start, NULL);
        ways = findOptimized(faces, n, m);
        gettimeofday(&stop, NULL);

        time_in_mill = (double) (start.tv_sec) * 1000 + (double) (start.tv_usec) / 1000;
        time_in_mill2 = (double) (stop.tv_sec) * 1000 + (double) (stop.tv_usec) / 1000;

        printf("| Optimized approach:\t%lu, time elapsed: %lf\n", ways, time_in_mill2 - time_in_mill);

        prt_ln();
        while (getchar() != '\n')
            ;
    } while (menu_continue());
}