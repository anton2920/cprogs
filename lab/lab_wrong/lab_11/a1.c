#include <stdio.h>
#include <math.h>

float f(float x, int i);

/* Sum of number sequence */
main() {

    /* Initializing variables */
    float sum, x;
    int n, counter;
    sum = 0;

    /* I/O flow && VarCheck*/
    do {
        printf("Type N: ");
        scanf("%d", &n);
    } while (n <= 0);
    printf("Type X: ");
    scanf("%f", &x);


    /* Main part */
    for (counter = 1; counter <= n; ++counter) {
        printf("Element %d = %f\n", counter, f(x, counter));
        sum = sum + f(x, counter);
    }

    /* Final output */
    printf("Sum = %f\n", sum);
}

float f(float x, int i) {
    return pow(-1, i) * exp(-i * x);
}