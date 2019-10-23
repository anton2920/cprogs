#include "libs.h"
#include "tree.h"

main() {

    /* Initializing variables */
    auto tree t;
    Tree_init(&t);

    /* I/O flow */
    fillInTree(&t);

    /* Main part */
    checkTree(&t);

    Tree_delete(&t);
}