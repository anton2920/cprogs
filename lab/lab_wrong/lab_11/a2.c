#include <stdio.h>
#include <math.h>

float f(float x, int i);
long int fact(int n);

/* Sum of number sequence */
main() {

    /* Initializing variables */
    float sum, x, e;
    int counter;
    sum = 0;

    /* I/O flow */
    printf("Type X: ");
    scanf("%f", &x);
    printf("Type accuracy: ");
    scanf("%f", &e);


    /* Main part */
    for (counter = 1; f(x, counter) > e; ++counter) {
        printf("Element %d = %f\n", counter, f(x, counter));
        sum = sum + f(x, counter);
    }

    /* Final output */
    printf("Sum = %f\n", sum);
}

float f(float x, int i) {
    return 3 * pow(x, i) / fact(x + 2);
}

long int fact(int n) {

    /* Initializing variables */
    long int fact;
    int counter;
    fact = 1;

    /* Main part */
    for (counter = 1; counter <= n; ++counter) {
        fact = fact * counter;
    }

    return fact;

}