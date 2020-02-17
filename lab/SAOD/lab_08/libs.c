#include <time.h>

#include "libs.h"

int moveCount = 0;

void partitioning(int *x, int n) {

    /* Initializing variables */
    auto int a, b, c, d, l, h, s, v;

    /* VarCheck */
    if (n <= 1) {
        return;
    }

    /* Main part */
    v = WHITE;
    a = b = 0;
    c = d = n - 1;
    for (;;) {
        while (b <= c && x[b] <= v) {
            if (x[b] == v && *(x + a) == v) {
                ++a;
            } else if (x[b] == v) {
                iswap(a++, b, x);
            }
            ++b;
        }
        while (c >= b && x[c] >= v) {
            if (x[c] == v && *(x + d) == v) {
                --d;
            } else if (x[c] == v) {
                iswap(d--, c, x);
            }
            --c;
        }
        if (b > c) {
            break;
        }
        iswap(b++, c--, x);
    }
    s = min(a, b - a);
    for (l = 0, h = b - s; s; s--) {
        iswap(l++, h++, x);
    }
    s = min(d - c, n - 1 - d);
    for (l = b, h = n - s; s; s--) {
        iswap(l++, h++, x);
    }
}

inline void iswap(int a, int b, int *pInt) {

    /* Initializing variables */
    ++moveCount;

    /* Main part */
    __asm__ volatile ("nop"
                : "=d" (*(pInt + a)), "=a" (*(pInt + b))
                : "a" (*(pInt + a)), "d" (*(pInt + b)));
}

inline int min(int a, int b) {

    /* Returning value */
    return (a > b) ? b : a;
}

void generateArray(int *x, int n) {

    /* Initializing variables */
    auto int i;
    srand(time(NULL));

    /* Main part */
    for (i = 0; i < n; ++i) {
        *(x + i) = rand() % 3;
    }
}

void printArray(FILE *fp, int *x, int n) {

    /* Initializing variables */
    auto int i;

    /* I/O flow */
    for (i = 0; i < n; ++i) {
        fprintf(fp, "%d ", *(x + i));
    }

    /* Final output */
    fprintf(fp, "\n");
}
