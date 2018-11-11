#include <stdio.h>

int to_dec(int num, int base);

/* From base-x to base-10 */
main() {

    /* Initializing variables */
    int a, b, flag = 0, a1;

    /* I/O flow && VarCheck */
    do {
        printf("Type b (b < 9): ");
        scanf("%d", &b);
    } while (b >= 9 || b < 2);
    do {
        printf("Type a: ");
        scanf("%d", &a);
        a1 = a;
        while (a1 != 0) {
            if (a % 10 < b) {
                flag = 1;
            } else {
                flag = 0;
                break;
            }
            a1 /= 10;
        }
    } while (flag == 0);
    
    /* Final output*/
    printf("Number %d in base-10 system equals to %d\n", a, (a >= 0) ? (to_dec(a, b)) : (-1 * (to_dec(-a, b))));
}


int to_dec(int num, int base) {

    /* Initializing variables */
    int res, power;
    res = 0;
    power = 1;

    /* Main part */
    while (num != 0) {
        res = res + ((num % 10) * power);
        num = num / 10;
        power *= base;
    }

    return res;
}