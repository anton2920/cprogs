#include <STL.h>

#define KIB (1024)

main() {

    /* Initializing variables */
    auto Stack a;
    auto int digit, num, back_num = 0;

    /* Main part */
    Stack_init(&a, KIB);
    printf("Type a number: ");
    for ( ; (digit = getchar()) != 0xA; ) {
        digit -= '0';
        Stack_pushl(&a, (const void *) &digit);
    }

    if (!((num = Stack_get_size(&a) / SIZE_OF_LONG) % 2)) {
        back_num += STACK_POP_LONG(&a);
        back_num *= 10;
    }

    printf("\nDigits on odd places (backwards): ");

    for ( ; num > 0; num -= 2) {
        printf("%d ", (digit = STACK_POP_LONG(&a)));
        back_num += digit;
        back_num *= 10;
        fflush(stdout);
        if (Stack_get_size(&a)) {
            back_num += STACK_POP_LONG(&a);
            back_num *= 10;
        }
    }

    back_num /= 10;

    /* Final output */
    printf("\nNumber (backwards): %d\n", back_num);

    Stack_delete(&a);
}