#include <stdio.h>
#include <omp.h>
#include <math.h>

#define A       0.0
#define B       2.0

#define EPS     1e-6

double func(double x);
double lrect(double (*f)(double), long n);
double mrect(double (*f)(double), long n);
double rrect(double (*f)(double), long n);
double trapezoid(double (*f)(double), long n);
double simpson(double (*f)(double), long n);

main()
{
    /* I/O flow */
    printf("Integrator! Accuracy: %e\n\n", EPS);

    /* Main part */
    omp_set_dynamic(1);

#pragma omp parallel num_threads(5)
{
    long nsteps = 1000;
    double sum = 0, prev;
    double (*method)(double (*)(double), long);
    char *method_string;
    double time;

    switch (omp_get_thread_num()) {
        case 0:
            method = lrect;
            method_string = "Left rectangles";
            break;
        case 1:
            method = rrect;
            method_string = "Right rectangles";
            break;
        case 2:
            method = mrect;
            method_string = "Middle rectangles";
            break;
        case 3:
            method = trapezoid;
            method_string = "Trapezoid";
            break;
        case 4:
            method = simpson;
            method_string = "Simpson's";
            break;
        default:
            break;
    }

    do {
        prev = sum;

        time = omp_get_wtime();
        sum = (*method)(func, nsteps);
        time = omp_get_wtime() - time;

        if (fabs(sum - prev) <= EPS) {
            break;
        } else {
            nsteps *= 2;
        }
    } while (1);

    printf("%20s: %20.19lf (%-10ld in time %lf)\n", method_string, sum, nsteps, time);
}

    /* Returning value */
    return 0;
}

double func(double x)
{
    /* Returning value */
    return exp(tan(x / 3) + 0.2); /* Should be: 3.59512486 */
}

double lrect(double (*f)(double), long n)
{
    /* Initializing variables */
    register long i;
    double x;
    double sum = 0.0, step;

    step = (B - A) / ((double) n);

    /* Main part */
#pragma omp parallel for reduction(+:sum)
    for (i = 0; i < n; ++i) {
        x = A + (double) i * step;
        sum += f(x);
    }

    /* Returning value */
    return sum * step;
}

double rrect(double (*f)(double), long n)
{
    register long i;
    double x;
    double sum = 0.0, step;

    step = (B - A) / ((double) n);

    /* Main part */
#pragma omp parallel for reduction(+:sum)
    for (i = 0; i < n; ++i) {
        x = A + (double) (i + 1) * step;
        sum += f(x);
    }

    /* Returning value */
    return sum * step;
}

double mrect(double (*f)(double), long n)
{
    /* Initializing variables */
    register long i;
    double x;
    double sum = 0.0, step;

    step = (B - A) / ((double) n);

    /* Main part */
#pragma omp parallel for reduction(+:sum)
    for (i = 0; i < n; ++i) {
        x = A + ((double) i + 0.5) * step;
        sum += f(x);
    }

    /* Returning value */
    return sum * step;
}

double trapezoid(double (*f)(double), long n)
{
    register long i;
    double x0, x1;
    double sum = 0.0, step;

    step = (B - A) / ((double) n);

    /* Main part */
#pragma omp parallel for reduction(+:sum)
    for (i = 0; i < n; i++) {
        x0 = A + (double) i * step;
        x1 = A + (double) (i + 1) * step;
        sum += f(x0) + f(x1);
    }

    /* Returning value */
    return sum * (step / 2);
}

double simpson(double (*f)(double), long n)
{
    register long i;
    double x_lo, x_hi, x_mid;
    double sum = 0.0, step;

    step = (B - A) / ((double) n);

    /* Main part */
#pragma omp parallel for reduction(+:sum)
    for (i = 0; i < n; i++) {
        x_lo = A + (double) i * step;
        x_hi = A + (double) (i + 1) * step;
        x_mid = (x_lo + x_hi) / 2;

        sum += f(x_lo) + 4 * f(x_mid) + f(x_hi);
    }

    /* Returning value */
    return sum * (step / 6.0);
}
