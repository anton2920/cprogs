#include <stdio.h>
#include <omp.h>
#include <math.h>

double func(double x);

main() {

    /* Initializing variables */
    auto double h, x, step = 1e-7, res;

    /* Main part */

    /* Left triangles */
    for (x = 0, res = 0; x <= 2; x += step) {
        res += func(x);
    }
    res *= h;
    printf("Left triangles: %lf\n", res);

    /* Right triangles */
    for (x = 0 + step, res = 0; x <= 2; x += step) {
        res += func(x);
    }
    res *= h;
    printf("Right triangles: %lf\n", res);

    /* Returning value */
    return 0;
}

double func(double x) {

    /* Returning value */
    return exp(tan(x / 3) + 0.2);
}