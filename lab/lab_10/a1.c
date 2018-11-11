#include <stdio.h>

/* Maximum digits sum */
main() {

    /* Initializing variables */
    int a, b, i, sum, max = 0, msum = 0;

    /* I/O flow && VarCheck */
    do {
        printf("Type a [left border]: ");
        scanf("%d", &a);
    } while (a <= 0);
    do {
        printf("Type b [right border]: ");
        scanf("%d", &b);
    } while (b <= 0 || b <= a);

    /* Main part */
    for (i = a; a <= b; i = ++a) {
        while (i != 0) {
            sum += i % 10;
            i /= 10;
        }
        if (sum > msum) {
            max = a;
            msum = sum;
        }
        sum = 0;
    }

    /* Final output */
    printf("The maximum digit sum is in number %d and it equals to %d\n", max, msum);
}