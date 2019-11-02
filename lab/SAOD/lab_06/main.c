#include <time.h>

#include "libs.h"
#include "tree.h"

int main() {

    /* Initializing variables */
    auto tree t, new_t;
    Tree_init(&t);
    Tree_init(&new_t);
    auto FILE *fp = fopen("input.txt", "r");
    /* srand(time(NULL) / 2); */

    /* VarCheck */
    if (fp == NULL) {
        return -1;
    }

    /* I/O flow */
    fillInTree(&t, fp);

    /* Main part */
    doAccess2(Tree_begin(&t));
    printf("Old tree: \n");
    Tree_print(&t, print_node);

    rearrange(&new_t, &t);
    printf("\n\nNew tree: \n");
    Tree_print(&new_t, print_node);

    Tree_delete(&t);
    Tree_delete(&new_t);

    /* Returning value */
    return 0;
}