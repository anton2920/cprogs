#include <stdio.h>
#include "libs/input.h"

main() {

    /* Initializing variables */
    int a = 1;

    /* Main part */
    printf("Type numbers: ");
    for ( ; a; ) {
        getint(&a);
        printf("The number is %d\n", a);
    }
}