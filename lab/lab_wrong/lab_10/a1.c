#include <stdio.h>

/* Counting numbers */
main() {

    /* Initializing variables */
    int a, b, n, counterc, num, counter;
    counter = 0;

    /* I/O flow && VarCheck */
    do {
        printf("Type «start» point: ");
        scanf("%d", &a);
    } while (a <= 0);
    do {
        printf("Type «end» point: ");
        scanf("%d", &b);
    } while (b <= 0);
    do {
        printf("Type digit: ");
        scanf("%d", &n);
    } while (n < 0 && n > 9);

    /* Main part */
    for (counterc = a; counterc <= b; ++counterc) {
        num = counterc;
        while (num != 0) {
            if (num % 10 == n) {
                ++counter;
            }
            num = num / 10;
        }
    }

    /* Final output */
    printf("Digit «%d» was found %d times\n", n, counter);

}