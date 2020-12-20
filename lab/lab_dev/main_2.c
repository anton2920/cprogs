#include <stdio.h>
#include <assert.h>

main()
{
    FILE *fin = fopen("INPUT.TXT", "r");
    FILE *fout = fopen("OUTPUT.TXT", "w");
    int got = 0;
    long i, j, n, sum;

    assert(fin != NULL);
    assert(fout != NULL);

    fscanf(fin, "%ld", &n);

    for (i = 1; i <= n && !got; ++i) {
        sum = 0;
        for (j = i; j <= n && !got; ++j) {
            sum += j;
            if (sum == n) {
                got = 1;
            } else if (sum > n) {
                break;
            }
        }
    }

    /*printf("[%ld..%ld]\n", i - 1, j - 1);*/
    fprintf(fout, "%ld", j - i + 1);
}