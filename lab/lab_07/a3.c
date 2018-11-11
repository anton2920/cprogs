#include <stdio.h>

int to_system(int num, int base);

/* From base-10 to base-x */
main() {

    /* Initializing variables */
    int a, b;

    /* I/O flow && VarCheck */
    printf("Type a: ");
    scanf("%d", &a);
    do {
        printf("Type b (b < 9): ");
        scanf("%d", &b);
    } while (b >= 9 || b < 2);

    /* Final output*/
    printf("Number %d in system with base %d equals to %d\n", a, b, (a >= 0) ? (to_system(a, b)) : (-1 * (to_system(-a, b))));
}


int to_system(int num, int base) {

    /* Initializing variables */
    int res, power10;
    res = 0;
    power10 = 1;

    /* Main part */
    while (num != 0) {
        res = res + ((num % base) * power10);
        num = num / base;
        power10 *= 10;
    }

    return res;
}