#include <stdio.h>

/* Sum of first N members of sequence */
main() {

    /* Initializing variables */
    float sum;
    int n, counter;
    sum = 0;

    /* I/O flow && VarCheck*/
    do {
        printf("Type N (N > 0): ");
        scanf("%d", &n);
    } while (n <= 0);

    /* Main part */
    for (counter = 1; counter <= n; ++counter) {
        sum = sum + (1.0 / (counter * (counter + 1)));
    }

    /* Final output */
    printf("The sum of first %d members of sequence: %f\n", n, sum);
}