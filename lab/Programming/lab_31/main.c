#include <stdio.h>
#include <STL.h>

main() {

    /* Initializing variables */
    auto List a;
    auto int digit, number = 0;

    /* Main part */
    List_init(&a);
    printf("Type a number: ");
    for ( ; (digit = getchar()) != 0xA; ) {
        digit -= '0';
        List_Stack_pushl(&a, (const void *) &digit);
    }

    if (!(a.size % 2)) {
        LIST_STACK_POPL(&a, digit);
        number += digit;
        number *= 10;
    }

    printf("\nDigits on odd places (backwards): ");

    for ( ; a.size; ) {
        LIST_STACK_POPL(&a, digit);
        number += digit;
        number *= 10;
        printf("%d ", digit);

        if (a.size) {
            LIST_STACK_POPL(&a, digit);
            number += digit;
            number *= 10;
        }
    }
    number /= 10;

    printf("\nNumber (backwards): %d\n", number);

    List_delete(&a);

    /* Returning value */
    return 0;
}