#include <time.h>

#include "libs/libs.h"
#include "tree/tree.h"

int main() {

    /* Initializing variables */
    auto tree t, new_t;
    Tree_init(&t);
    Tree_init(&new_t);
    auto FILE *fp = fopen("input.txt", "r");
    auto double mean1, mean2;
    srand(time(NULL) / 2);

    /* VarCheck */
    if (fp == NULL) {
        return -1;
    }

    /* I/O flow */
    fillInTree(&t, NULL);

    /* Main part */
    mean1 = doAccess(&t);

    rearrange(&new_t, &t);

    Tree_delete(&t);

    /* Returning value */
    return 0;
}