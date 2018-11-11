#include <stdio.h>
#include <math.h>

/* Member of a number set (cycled version) */
main() {

    /* Initializing variables */
    float a, b, c, n;

    /* I/O flow */
    printf("Type the element a: ");
    scanf("%f", &a);
    printf("Type the step b: ");
    scanf("%f", &b);
    printf("Type the first element c: ");
    scanf("%f", &c);

    /* Main part */
    n = (a - c) / b + 1;
    if (floor(n) == ceil(n)) {
        printf("The «a» element is in the number set\n");
    } else {
        printf("The «a» element is not in the number set\n");
    }
}