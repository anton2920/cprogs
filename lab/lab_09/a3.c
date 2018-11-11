#include <stdio.h>
#include <math.h>

float f(float x);

/* Segment function pt. 2 */
main() {

    /* Initializing variables */
    float a, b, c, counter;

    /* I/O flow */
    printf("Type left border of X: ");
    scanf("%f", &a);
    do {
        printf("Type step: ");
        scanf("%f", &c);
    } while (c == 0);
    do {
        printf("Type right border of X: ");
        scanf("%f", &b);
    } while ((c > 0) ? b < a : a < b);

    /* Main part */
    for (counter = a; (a < b) ? counter <= b : counter >= b; counter = counter + c) {
        printf("f(%6.3f) = %6.3f\n", counter, f(counter));
    }
}

float f(float x) {

    /* Main part */
    if (x < 0) {
        return 0.0;
    } else if (x < 1) {
        return 1.0 / (x + 4.0);
    } else {
        return exp(x);
    }
}