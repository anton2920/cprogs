#include "lab.h"

int cal_sum(struct arr *mas) {

    /* Initializing variables */
    int i, j, sum = 0;

    /* Main part */
    for (i = 0; i < mas->n; ++i) {
        if (mas->array[i][i] >= 0) {
            continue;
        }
        for (j = 0; j < mas->m; ++j) {
            sum += mas->array[i][j];
        }
    }

    /* Returning value */
    return sum;
}