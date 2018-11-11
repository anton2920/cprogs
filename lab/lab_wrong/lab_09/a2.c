#include <stdio.h>
#include <math.h>

float f(float x);

/* Segment function pt. 2 */
main() {

    /* Initializing variables */
    float a, b, c, counter;

    /* I/O flow */
    printf("Type the «start» point: ");
    scanf("%f", &a);
    printf("Type the «end» point: ");
    scanf("%f", &b);
    printf("Type step: ");
    scanf("%f", &c);

    /* Main part */
    for (counter = a; counter <= b; counter = counter + c) {
        printf("f(%f) = %f\n", counter, f(counter));
    }
}

float f(float x) {

    /* Main part */
    if (x <= 0) {
        return 5.0;
    } else if ((x > 0) && (x <= 1)) {
        return (x*x*x + 1) / (2 * x + 3);
    } else {
        return 5 * log(x);
    }
}