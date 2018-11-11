#include <stdio.h>
#include <math.h>

/* Sum of number sequence */
main() {

    /* Initializing variables */
    float sum, x, x2;
    int n, counter, mn_one = 1;
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
        sum += mn_one * sin(counter * x2);
        mn_one *= -1;
        x2 *= x;
    }

    /* Final output */
    printf("Sum = %f\n", sum);
}