#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

void task_1(void);
void task_2(void);
void task_3(void);

main()
{
    /* Main part */
    /*task_1();*/

    /*task_2();*/

    task_3();

    /* Returning value */
    return 0;
}

static void setv(int *vec, size_t n)
{
    /* Initializing variables */
    register size_t i;

    /* Main part */
    for (i = 0; i < n; ++i) {
        *(vec + i) = rand() % 100;
    }
}

static void printv(const char *str, const int *vec, size_t n)
{
    /* Initializing variables */
    register size_t i;

    /* I/O flow */
    printf("%10s", str);

    /* Main part */
    for (i = 0; i < n; ++i) {
        printf("%5d", *(vec + i));
    }

    /* Final output */
    printf("\n");
}

void task_1(void)
{
    /* Initializing variables */
    enum {
        N = 10
    };
    int v1[N], v2[N], sum[N];

    /* Main part */
    srand((time(NULL) << 16) - 1);

    setv(v1, N);
    setv(v2, N);

#pragma omp parallel sections
{
    #pragma omp section
    {
        register size_t i;
        for (i = 0; i < N / 2; ++i) {
            *(sum + i) = *(v1 + i) + *(v2 + i);
        }
    }

    #pragma omp section
    {
        register size_t i;
        for (i = N / 2; i < N; ++i) {
            *(sum + i) = *(v1 + i) + *(v2 + i);
        }
    }
}

    printv("Vector 1: ", v1, N);
    printv("Vector 2: ", v2, N);
    printv("Sum vec: ", sum, N);
}

static int cmp(const int *a, const int *b)
{
    /* Returning value */
    return (*a < *b) ? -1 : (*a > *b) ? 1 : 0;
}

static int is_sorted(int *arr, size_t n, int (*cmp)(const int *, const int *))
{
    /* Initializing variables */
    register size_t i;

    /* Main part */
    for (i = 1; i < n; ++i) {
        if (cmp(arr + i, arr + i - 1) < 0) {
            i = i;
            return 0;
        }
    }

    /* Returning value */
    return 1;
}

static long find_sum(const int *arr, size_t n)
{
    /* Initializing variables */
    register long sum = 0;
    register size_t i;

    /* Returning value */
    for (i = 0; i < n; ++i) {
        sum += *(arr + i);
    }

    /* Returning value */
    return sum;
}

/* In-place merge */
static void merge(int *arr, size_t l1, size_t m1, size_t r1, int (*cmp)(const int *, const int *))
{
    /* Initializing variables */
    size_t l2 = m1 + 1;
    int value;
    size_t index;

    /* Main part */
    if (*(arr + m1) <= *(arr + l2))
        return;

    while (l1 <= m1 && l2 <= r1)
    {
        if (cmp(arr + l1, arr + l2) <= 0)
        {
            ++l1;
        }
        else
        {
            value = *(arr + l2);
            index = l2;

            while (index != l1)
            {
                *(arr + index) = *(arr + index - 1);
                --index;
            }
            *(arr + l1) = value;

            ++l1;
            ++m1;
            ++l2;
        }
    }
}

static void merge_sort(int *arr, size_t l, size_t r, int (*cmp)(const int *, const int *))
{
    /* Initializing variables */
    size_t m;

    /* Main part */
    if (l < r)
    {
        m = l + (r - l) / 2;

        /* Recursively sorting smaller chunks */
        merge_sort(arr, l, m, cmp);
        merge_sort(arr, m + 1, r, cmp);
        merge(arr, l, m, r, cmp);
    }
}

void print_results(const char *used_case, const char *status, double res)
{
    /* Final output */
    printf("%10s... %5s in time %10.9lf\n", used_case, status, res);
}

void task_2(void)
{
    /* Initializing variables */
    enum {
        N = 1000000
    };
    int a[N];
    long sum;
    double t1, t2;
    const char *estr;
    size_t i, nthreads;

    /* Main part */
    setv(a, N);
    sum = find_sum(a, N);

    /* Sequential */
    t1 = omp_get_wtime();
    merge_sort(a, 0, N - 1, cmp);
    t2 = omp_get_wtime();

    if (is_sorted(a, N, cmp) && find_sum(a, N) == sum) {
        estr = "OK";
    } else {
        estr = "FAIL";
    }

    print_results("Sequential", estr, t2 - t1);

    /* Parallel */
    setv(a, N); /* Scrambling again... */
    sum = find_sum(a, N);
    t1 = omp_get_wtime();
#pragma omp parallel num_threads(8) shared(a)
{
    nthreads = omp_get_num_threads();
    size_t j = omp_get_thread_num();
    size_t lsect = N / nthreads;
    size_t l = j * lsect;
    size_t r = (j == nthreads - 1) ? N - 1 : ((j + 1) * lsect) - 1;

    /*printf("Thread #%d [%lu..%lu]\n", j, l, r);*/

    merge_sort(a, l, r, cmp);
}

    /* Merging resulting chunks */
    {
        int lsect = N / nthreads;
        for (i = 1; i < nthreads; ++i) {
            size_t m = i * lsect - 1;
            size_t r = (i == nthreads - 1) ? N - 1 : ((i + 1) * lsect) - 1;

            /*printf("Merging #%lu [%lu..%lu..%lu]\n", i, 0lu, m, r);*/

            merge(a, 0, m, r, cmp);
        }
    }
    t2 = omp_get_wtime();

    if (is_sorted(a, N, cmp) && find_sum(a, N) == sum) {
        estr = "OK";
    } else {
        estr = "FAIL";
    }

    print_results("Parallel", estr, t2 - t1);
}

void swap(int *arr, size_t ind_a, size_t ind_b)
{
    /* Initializing variables */
    int temp;

    /* Main part */
    temp = *(arr + ind_a);
    *(arr + ind_a) = *(arr + ind_b);
    *(arr + ind_b) = temp;
}

void quick_sort(int *arr, size_t l, size_t r, int (*cmp)(const int *, const int *))
{
    /* Initializing variables */
    size_t i, j, pivot;

    /* Main part */
    if (l < r)
    {
        pivot = l;
        i = l;
        j = r;

        while (i < j)
        {
            while (cmp(arr + i, arr + pivot) <= 0 && i < r) {
                i++;
            }
            while (cmp(arr + j, arr + pivot) > 0) {
                j--;
            }
            if (i < j)
            {
                swap(arr, i, j);
            }
        }
        swap(arr, pivot, j);

        /* Recursively sorting smaller chunks */
        quick_sort(arr, l, j - 1, cmp);
        quick_sort(arr, j + 1, r, cmp);
    }
}

/* Returns position of the first pivot */
size_t get_first_pivot(int *arr, size_t r)
{
    /* Initializing variables */
    size_t i, j, pivot;

    pivot = i = 0;
    j = r;

    /* Main part */
    while (i < j)
    {
        while (cmp(arr + i, arr + pivot) <= 0 && i < r) {
            i++;
        }
        while (cmp(arr + j, arr + pivot) > 0) {
            j--;
        }
        if (i < j)
        {
            swap(arr, i, j);
        }
    }
    swap(arr, pivot, j);

    /* Returning value */
    return j;
}

void task_3(void)
{
    /* Initializing variables */
    enum {
        N = 1000000,
    };
    int a[N];
    long sum;
    double t1, t2;
    const char *estr;
    size_t i;

    /* Main part */
    setv(a, N);
    sum = find_sum(a, N);

    /* Sequential */
    t1 = omp_get_wtime();
    quick_sort(a, 0, N - 1, cmp);
    t2 = omp_get_wtime();

    if (is_sorted(a, N, cmp) && find_sum(a, N) == sum) {
        estr = "OK";
    } else {
        estr = "FAIL";
    }

    print_results("Sequential", estr, t2 - t1);

    /* Parallel */
    setv(a, N); /* Scrambling again... */
    sum = find_sum(a, N);
    i = get_first_pivot(a, N - 1);
    t1 = omp_get_wtime();
#pragma omp parallel num_threads(2) shared(a)
{
    int j = omp_get_thread_num();
    size_t l = (j) ? i + 1 : 0;
    size_t r = (j) ? N - 1 : i - 1;

    quick_sort(a, l, r, cmp);
}
    t2 = omp_get_wtime();

    if (is_sorted(a, N, cmp) && find_sum(a, N) == sum) {
        estr = "OK";
    } else {
        estr = "FAIL";
    }

    print_results("Parallel", estr, t2 - t1);
}
