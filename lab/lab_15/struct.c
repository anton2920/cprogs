#include "a1.h"

/* Functions definitions */
void struct_init(struct goods *mas) {

    /* Initializing variables */
    int i;

    /* Main part */
    for (i = 0; i < MAXSIZE; ++i, ++mas) {
        lstrcpy("", mas->name);
        mas->price = 0;
    }
}

struct goods min(const struct goods *mas, const int *n) {

    /* Initializing variables */
    int i;
    struct goods min = *mas++;

    /* Main part */
    for (i = 1; i < *n; ++i, ++mas) {
        if (mas->price < min.price) {
            min = *mas;
        }
    }

    /* Returning value */
    return min;
}

struct goods max(const struct goods *mas, const int *n) {

    /* Initializing variables */
    int i;
    struct goods max = *mas;

    /* Main part */
    for (i = 0; i < *n; ++i, ++mas) {
        if (mas->price > max.price) {
            max = *mas;
        }
    }

    /* Returning value */
    return max;
}