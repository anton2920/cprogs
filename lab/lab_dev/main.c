#include <stdio.h>

#include "libs/libs.h"
#include "tree/tree.h"

void print_element(const tree_node *elem);

main() {

    /* Initializing variables */
    auto tree t;
    Tree_init(&t);
    auto int i;

    /* Main part */
    for (i = 0; i < 10; ++i) {
        add_element(&t, &i, sizeof(i));
    }

    /* Final output */
    Tree_print(&t, print_element);
}

void print_element(const tree_node *_elem) {

    /* Initializing variables */
    auto int *elem = (int *) _elem->value;

    /* I/O flow */
    printf("%d\n", *elem);
}