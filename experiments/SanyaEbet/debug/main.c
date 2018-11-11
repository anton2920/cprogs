#include <stdio.h>
#include "libs/input.h"

main() {

    /* Initializing variables */
    int a;

    /* I/O flow */
    printf("Type A: ");
    getint(&a);

    /* Final output */
    printf("The number is %d\n", a);
}