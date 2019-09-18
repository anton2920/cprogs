#include <stdio.h>
#include <stdlib.h>

/* Product of even-positioned digits */
main() {

    /* Initializing variables */
    int a, a1, product, numnum;
    product = 1;
    numnum = 0;

    /* I/O flow && VarCheck */
    do {
        printf("Type a: ");
        scanf("%d", &a);
    } while (a <= 0);

    /* Main part */
    a1 = abs(a);
    while (a1 != 0) {
        a1 = a1 / 10;
        ++numnum;
    }
    if (numnum % 2 == 0) {
        product = product * (a % 10);
        a = a / 10;
    }
    a = a / 10;
    while (a != 0) {
        product = product * (a % 10);
        a = a / 100;
    }

    /* Final output */
    if (product == 1 && numnum == 1) {
        printf("The product is: 0\n");
    } else {
        printf("The product is: %d\n", product);
    }
}