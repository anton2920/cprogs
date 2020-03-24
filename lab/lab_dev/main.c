#include <stdio.h>
#include <stdlib.h>

int numcmp(const void *_self, const void *_other) {

    /* Initializing variables */
    auto const int *self = (const int *) _self, *other = (const int *) _other;

    /* Returning value */
    return (*self > *other) ? 1 : (*self < *other) ? -1 : 0;
}

int dblLinear(int n) {

    /* Initializing variables */
    auto int *a = (int *) calloc(n, sizeof(int)), i, len, tmp;
    *a = 1;

    /* VarCheck */
    if (a == NULL) {
        return 0;
    }

    /* Main part */
    fprintf(stderr, "1");
    for (len = 1, i = 0; len < n; ++i) {
        *(a + len++) = 2 * *(a + i) + 1;
        if (len >= n) {
            break;
        }
        *(a + len++) = 3 * *(a + i) + 1;
        fprintf(stderr, " %d %d", *(a + len - 2), *(a + len - 1));
        qsort(a, len, sizeof(int), numcmp);
    }
    qsort(a, len, sizeof(int), numcmp);
    fprintf(stderr, " %d %d", *(a + len - 2), *(a + len - 1));

    tmp = *(a + n - 1);
    free(a);

    /* Returning value */
    return tmp;
}

int main() {

    /* Initializing variables */
    auto int ans = dblLinear(20);
    fflush(stderr);

    /* Final output */
    printf("\nAnswer: %d\n", ans);

    /* Returning value */
    return 0;
}