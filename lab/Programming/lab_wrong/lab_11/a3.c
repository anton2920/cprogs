#include <stdio.h>
#include <math.h>

float f(float x, int i);
long int fact(int n);

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
        sum = sum + f(x, counter);
    }

    /* Final output */
    printf("Sum = %f\n", sum);
}

float f(float x, int i) {
    return ((pow(i, i) + fact(i) - pow(x, i) + pow((x + 1), i))) / (fact(x + i) + fact(2 * i));
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