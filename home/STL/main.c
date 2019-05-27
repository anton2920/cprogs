#include "STL.h"

int to_bin(int);

main() {

    /* Initializing variables */
    auto List a;
    auto int i, digit;

    /* Main part */
    List_init(&a);

    for (i = 0; i < 10; ++i) {
        List_Queue_pushl(&a, (const void *) &i);
    }

    for (i = 0; i < 10; ++i) {
        LIST_QUEUE_POPL(&a, digit);
        printf("%d = %d\n", digit, to_bin(digit));
    }

    List_delete(&a);

    /* Returning value */
    return 0;
}

int to_bin(int num) {

    /* Initializing variables */
    auto int number = 0, multiplier = 1;

    /* Main part */
    for ( ; num; num >>= 1, multiplier *= 10) {
        number += (num % 2) * multiplier;
    }

    /* Returning value */
    return number;
}