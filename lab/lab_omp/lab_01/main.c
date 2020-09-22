#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void task1(void);
void task2(void);
void task3(void);
void task4(void);
void task5(const char *);
void task6(void);

int main(int argc, const char *argv[]) {

    /* Task #1 */
    /* task1(); */

    /* Task #2 */
    /* task2(); */

    /* Task #3 */
    /* task3(); */

    /* Task #4 */
    /* task4(); */

    /* Task #5 */
    task5(*(argv + 1));

    /* Task #6 */
    /* task6(); */

    /* Returning value */
    return 0;
}

void task1(void) {

    /* I/O flow */
    printf("Sequential section #1\n");

    /* Parallel section */
#pragma omp parallel
{
    printf("Parallel section\n");
}

    /* Final output */
    printf("Sequential section #2\n");
}

void task2(void) {

    /* I/O flow */
    printf("Num of threads: %d\n", omp_get_max_threads());

    /* Parallel section */
#pragma omp parallel
{
    printf("Thread #%d\n", omp_get_thread_num());
}
}

void task3(void) {

    /* Parallel region */
    /* Using environmental variables */
    printf("OMP_NUM_THREADS = %s\n", getenv("OMP_NUM_THREADS"));
#pragma omp parallel
{
    printf("Parallel region #%d\n", omp_get_thread_num());
}

    printf("Pragma option\n");
#pragma omp parallel num_threads(3)
{
    printf("Parallel region #%d\n", omp_get_thread_num());
}

    printf("Function call\n");
    omp_set_num_threads(4);
#pragma omp parallel
{
    printf("Parallel region #%d\n", omp_get_thread_num());
}
}

void task4(void) {

    /* I/O flow */
    printf("Static mode\n");
    omp_set_num_threads(128);

#pragma omp parallel
{
    if (!omp_get_thread_num()) {
        printf("Num of threads: %d\n", omp_get_num_threads());
    }
}

    printf("Dynamic mode\n");
    omp_set_dynamic(1);
#pragma omp parallel
{
    if (!omp_get_thread_num()) {
        printf("Num of threads: %d\n", omp_get_num_threads());
    }
}
}

void task5(const char *arg) {

    if (!strcmp("parallel", arg)) {
#pragma omp parallel
{
    if (!omp_get_thread_num()) {
        printf("Num of threads: %d\n", omp_get_num_threads());
    }
}
    } else if (!strcmp("serial", arg)) {
        printf("Num of threads: %d\n", omp_get_num_threads());
    }
}

void task6(void) {

    /* Sub #1 */
#ifdef _OPENMP
    printf("OpenMP is supported\n");
#endif

    /* Sub #2 */
    printf("Num of available cores: %d\n", omp_get_num_procs());

    /* Sub #3 */
    omp_set_num_threads(8);
    printf("Num of threads: %d\n", omp_get_num_threads());

    /* Sum #4-#6 */
    omp_set_num_threads(4);
    enum MAXES {
        N = 1000000,
        N1 = N / 4
    };
    register int i;

    clock_t t0 = clock();
    for (i = 0; i < N; ++i) {
        int j = i + 1;
    }

    clock_t t1 = clock() - t0;
    printf("Sequential time: %ld\n", t1);

    t0 = clock();
#pragma omp parallel
{
    for (i = 0; i < N1; ++i) {
        int j = i + 1;
    }
}
    clock_t t2 = clock() - t0;
    printf("Parallel time: %ld\n%d\n", t2);

    printf("Acceleration: %lf\n", (double) t1 / t2);
}
