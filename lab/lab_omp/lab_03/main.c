#include <stdio.h>
#include <omp.h>
#include <time.h>

void task1(void);
void task2(void);
void task3(void);
void task4(void);

int main(int argc, const char *argv[]) {

    /* Task #1 */
    /*task1();*/

    /* Task #2 */
    /*task2();*/

    /* Task #3 */
    /*task3();*/

    /* Task #4 */
    task4();

    /* Returning value */
    return 0;
}

#include <stdlib.h>

void task1(void) {

    /* Initializing varibles */
    enum array_size {
        N = 25
    };
    auto int a[N], b[N], c[N];
    register int i;

    /* Main part */
    srand(time(NULL));

    for (i = 0; i < N; ++i) {
        *(a + i) = (rand() % 100) + 1;
        *(b + i) = (rand() % 100) + 1;
    }

    /* Parallel region */
#pragma omp parallel
{
#pragma omp for
    for (i = 0; i < N; ++i) {
        *(c + i) = *(a + i) + *(b + i);
        printf("Thread #%d:\t%d + %d = %d\n", omp_get_thread_num(), *(a + i), *(b + i), *(c + i));
    }
}
}

void task2(void) {

    /* Initializing variables */
    enum array_size {
        N = 25
    };
    auto int a[N], b[N], sum = 0;
    register int i;

    /* Main part */
    /*srand(time(NULL));*/

    for (i = 0; i < N; ++i) {
        *(a + i) = (rand() % 100) + 1;
        *(b + i) = (rand() % 100) + 1;
    }

    /* Parallel region */
#pragma omp parallel for reduction(+:sum)
    for (i = 0; i < N; ++i) {
        sum += *(a + i) * *(b + i);
    }

    /* Final output */
    printf("Sum = %d\n", sum);
}

void task3(void) {

    /* Initializing variables */
    enum Matrix_sizes {
        Nvec = 5,
        Nrow = Nvec,
        Ncol = 5
    };

    register int i, j;
    auto int a[Nvec], b[Nrow][Ncol], c[Nvec], sum = 0;

    /* Main part */
    printf("Vector: \n");
    for (i = 0; i < Nvec; ++i) {
        *(a + i) = (rand() % 100) + 1;
        printf("%4d", *(a + i));
    }

    printf("\n\nArray: \n");
    for (i = 0; i < Nrow; ++i) {
        for (j = 0; j < Ncol; ++j) {
            b[i][j] = (rand() % 100) + 1;
            printf("%4d", b[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    /* Parallel region */
#pragma omp parallel for
    for (j = 0; j < Ncol; ++j) {
        sum = 0;
        for (i = 0; i < Nrow; ++i) {
            sum += *(a + i) * b[i][j];
        }
        *(c + j) = sum;
        printf("Thread #%d: c[%d] = %d\n", omp_get_thread_num(), j, sum);
    }

    printf("\nProduct: \n");
    for (i = 0; i < Nvec; ++i) {
        printf("%d\t", *(c + i));
    }

    /* Final output */
    printf("\n");
}

void task4(void) {

    /* Initializing variables */
    register int i, j;

    /* Main part */
    omp_set_num_threads(9);

    /* Parallel region */
#pragma omp parallel for ordered
    for (i = 1; i <= 9; ++i) {
#pragma omp ordered
        for (j = 1; j <= 9; ++j) {
            printf("%3d", i * j);
        }
        printf("\n");
    }
}