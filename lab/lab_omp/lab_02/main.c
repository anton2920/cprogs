#include <stdio.h>
#include <omp.h>
#include <time.h>

void task1(void);
void task2(void);
void task3(void);
void task4(void);
void task5(void);
void task6(void);
void task7(void);
void task8(void);

int main() {

    /* Task #1 */
    /*task1();*/

    /* Task #2 */
    /*task2();*/

    /* Task #3 */
    /*task3();*/

    /* Task #4 */
    /*task4();*/

    /* Task #5 */
    /*task5();*/

    /* Task #6 */
    /*task6();*/

    /* Task #7 */
    /*task7();*/

    /* Task #8 */
    task8();

    /* Returning value */
    return 0;
}

#include <pthread.h>
struct twodbls {
    double a;
    double b;
    int maxIter;
};

void *multiplicationTest(void *__arg) {

    /* Initializing variables */
    struct twodbls *arg = (struct twodbls *) __arg;
    register int i;

    /* Main part */
    for (i = 0; i < arg->maxIter; ++i) {
        double c = arg->a * arg->b;
    }

    /* Exiting */
    pthread_exit(0);
}

void task1(void) {

    /* Initializing varibles */
    auto double a, b;
    enum consts {
        iterations = 1000000,
        iterations2 = iterations / 2
    };
    register int i;
    auto clock_t t0, t1, t2;

    /* I/O flow */
    printf("Type a: ");
    scanf("%lf", &a);

    printf("Type b: ");
    scanf("%lf", &b);

    for (i = 0, t0 = clock(); i < iterations; ++i) {
        auto double c = a * b;
    }
    t1 = clock() - t0;
    printf("Sequential time: %ld\n", t1);

    /* Parallel region */
    t0 = clock();
#pragma omp parallel
{
    for (i = 0; i < iterations2; ++i) {
        auto double c = a * b;
    }
}
/*    struct twodbls arg = {a, b, iterations2};
    pthread_t t[2];
    pthread_create(t, NULL, multiplicationTest, &arg);
    pthread_create(t + 1, NULL, multiplicationTest, &arg);

    pthread_join(*t, 0);
    pthread_join(*(t + 1), 0);*/

    t2 = clock() - t0;
    printf("Parallel time: %ld\n", t2);
}

void task2(void) {

    /* Initializing variables */
    auto clock_t t0, t1;

    /* Parallel region */
    t0 = clock();
#pragma omp parallel
{}
    t1 = clock() - t0;

    printf("Parallel region costs: %ld\n", t1);
}

void task3(void) {

    /* Main part */
    omp_set_num_threads(3);

    /* Parallel region */
#pragma omp parallel
{
    printf("Begin %d\n", omp_get_thread_num());

#pragma omp single nowait
    printf("One thread %d\n", omp_get_thread_num());

    printf("End %d\n", omp_get_thread_num());
}
}

void task4(void) {

    /* Main part */
    omp_set_num_threads(3);

    /* Parallel region */
#pragma omp parallel
{
    printf("Begin %d\n", omp_get_thread_num());
#pragma omp master
{
    printf("Master thread\n");
}
    printf("Middle %d\n", omp_get_thread_num());
#pragma omp master
{
    printf("Master thread\n");
}
    printf("End %d\n", omp_get_thread_num());
}
}

void task5(void) {

    /* Main part */
    auto int n = 5;
    omp_set_num_threads(2);

    /* I/O flow */
    printf("n = %d\n", n);

    /* Parallel region */
#pragma omp parallel private(n)
{
    printf("Thread #%d, n = %d\n", omp_get_thread_num(), n);
#pragma omp barrier
    n = omp_get_thread_num();
#pragma omp single
    printf("Assignment done!\n");
    printf("Thread #%d, n = %d\n", omp_get_thread_num(), n);
}

    /* Final output */
    printf("n = %d\n", n);
}

void task6(void) {

    /* Initializing variables */
    auto int m[5] = {};
    register int i;

    /* I/O flow */
    for (i = 0; i < 5; ++i) {
        printf("m[%d] = %d\n", i, *(m + i));
    }
    printf("\nParallel region: \n");

    /* Main part */
    omp_set_num_threads(2);

    /* Parallel region */
#pragma omp parallel
{
    *(m + omp_get_thread_num()) = 1;
}

    for (i = 0; i < 5; ++i) {
        printf("m[%d] = %d\n", i, *(m + i));
    }
}

void task7(void) {

    /* Initializing variables */
    auto int i = 0;

    /* Main part */

    /* Parallel region */
    printf("Before: i = %d\n", i);
#pragma omp parallel num_threads(4) reduction(+:i)
{
    i = 1;
}
    printf("After: i = %d\n", i);
}

void task8(void) {

    /* Initializing variables */
    auto int sum = 0;

    /* Main part */

    /* Parallel region */
#pragma omp parallel num_threads(9) reduction(+:sum)
{
    register int num;
    if (!((num = omp_get_thread_num()) & 1)) {
        sum = num;
    }
}
    printf("Sum = %d\n", sum);
}