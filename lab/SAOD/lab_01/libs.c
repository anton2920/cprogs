#include "libs.h"

/* Time complexity: O(m ^ n), space complexity: O(n) */
unsigned long int findRecursive(int m, int n, int x) {

    /* Initializing variables */
    auto unsigned long int res = 0;
    register int i;

    /* Main part */
    if ((x && !n) || (!x && n)) {
        return 0;
    } else if (!x)
        return 1;

    /* When x is so high that sum can not go beyond x even when we get maximum value in every dice throw */
    if (m * n <= x)
        return (m * n == x) ? 1 : 0;

    /* When x is too low */
    if (n >= x)
        return (n == x) ? 1 : 0;

    for (i = 1; i <= m; i++)
        res += findRecursive(m, n - 1, x - i);

    /* Returning value */
    return res;
}

/* Time complexity: O(m × n × x), space complexity: O(n × x) */
unsigned long int findIterative(int m, int n, int x) {

    /* Initializing variables */
    register int i, j, k;
    auto unsigned long int table[n + 1][x + 1];
    memset(table, 0, sizeof(table));

    /* Main part */

    /* When x is so high that sum can not go beyond x even when we get maximum value in every dice throw */
    if (m * n <= x)
        return (m * n == x) ? 1 : 0;

    /* When x is too low */
    if (n >= x)
        return (n == x) ? 1 : 0;

    /* Table entries for only one dice */
    for (j = 1; j <= m && j <= x; j++)
        table[1][j] = 1;

    /* Fill the rest of the table. i — number of dice, j — sum */
    for (i = 2; i <= n; i++) {
        for (j = 1; j <= x; j++) {
            for (k = 1; k <= m && k < j; k++) {
                table[i][j] += table[i - 1][j - k];
            }
        }
    }

    /* Returning value */
    return table[n][x];
}

/* Time complexity: O(n × x), space complexity: O(n × x) */
unsigned long int findOptimized(int m, int n, int x) {

    /* Initializing variables */
    register int i, j;
    auto unsigned long int mem[n + 1][x + 1];
    memset(mem, 0, sizeof mem);
    mem[0][0] = 1;

    /* Main part */

    /* When x is so high that sum can not go beyond x even when we get maximum value in every dice throw */
    if (m * n <= x)
        return (m * n == x) ? 1 : 0;

    /* When x is too low */
    if (n >= x)
        return (n == x) ? 1 : 0;

    for (i = 1; i <= n; i++) {
        for (j = i; j <= x; j++) {
            mem[i][j] = mem[i][j - 1] + mem[i - 1][j - 1];

            if (j - m - 1 >= 0) {
                mem[i][j] -= mem[i - 1][j - m - 1];
            }
        }
    }

    /* Returning value */
    return mem[n][x];
}

void prt_ln(void) {

    /* Final output */
    printf(" ------------------------------------------------------------\n");
}

int menu_continue(void) {

    /* Initializing variables */
    int func;

    /* I/O flow */
    while (1) {
        printf("| Continue? [y/N]: ");
        switch ((func = getchar())) {
            case 'y': case 'Y':
                if ((getchar()) != '\n') {
                    while ((getchar()) != '\n')
                        ;
                    prt_ln();
                    continue;
                }
                prt_ln();
                return 1;
            case 'n': case 'N': case '\n':
                if (func == 'n' || func == 'N') {
                    if ((getchar()) != '\n') {
                        while ((getchar()) != '\n')
                            ;
                        prt_ln();
                        continue;
                    }
                }
                prt_ln();
                return 0;
            default:
                while ((getchar()) != '\n')
                    ;
                prt_ln();
                continue;
        }
    }
}