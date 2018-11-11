#include <stdio.h>

/* Function declaration */
long int fact(long int n);

/* Sum of number sequence */
main() {

    /* Initializing variables */
    float sum, e, x2, slog;
    long int i, x, fac;
    sum = 0;

    /* I/O flow */
    printf("Type X: ");
    scanf("%ld", &x);
    printf("Type accuracy: ");
    scanf("%f", &e);


    /* Main part */
    x2 = x * x;
    fac = fact(x);
    do {
        slog = fac * x2;
        x2 *= x * x;
        sum += slog;
    } while (slog >= e);

    /* Final output */
    printf("Sum = %f\n", sum);
}

long int fact(long int n) {

    /* Initializing variables */
    long int fact;
    int counter;
    fact = 1;

    /* Main part */
    for (counter = 1; counter <= n; ++counter) {
        fact = fact * counter;
    }

    /* Returning value */
    return fact;

}