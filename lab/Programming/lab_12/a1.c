#include <stdio.h>

int ladder(int, int);

main() {

    /* Initializing variables */
    int n;

    /* I/O flow && VarCheck */
    do {
        printf("Type N: ");
        scanf("%d", &n);
    } while (n < 0);

    /* Final output */
    printf("Answer: %d\n", ladder(n, n - 1));
}

int ladder(int number, int num_base) {

    /* Main part */
    if (number <= 2 || num_base <= 1) {
        return 0;
    } else if (number - num_base >= num_base) {
        return ladder(number, num_base - 1) + ladder(number - num_base, number - num_base - 1 - (number - 2 * num_base));
    } else if (number - num_base < 3) {
        return 1 + ladder(number, num_base - 1);
    }  else if (number - num_base >= 3) {
        return 1 + ladder(number, num_base - 1) + ladder(number - num_base, number - num_base - 1);
    } else {
        return 0;
    }
}