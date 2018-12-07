#include <stdio.h>

/* N-member of fibonacci sequence */
main() {

    /* Initializing variables */
    int n, counter, ans, pre1, pre2;
    pre1 = 1;
    pre2 = 1;
    counter = 3;

    /* I/O flow && VarCheck*/
    do {
        printf("Type N: ");
        scanf("%d", &n);
    } while (n <= 0);

    /* Main part */
    if (n == 1 || n == 2) {
        printf("The %d-member of fibonacci sequence: %d\n", n, 1);
    } else {
        while (counter <= n) {
            ans = pre1 + pre2;
            ++counter;
            pre2 = pre1;
            pre1 = ans;
        }
        printf("The %d-member of fibonacci sequence: %d\n", n, ans);
    }
}