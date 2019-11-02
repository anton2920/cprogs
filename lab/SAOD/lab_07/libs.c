#include <stdio.h>
#include <string.h>

#include "libs.h"

static int inumcmp(const void *_self, const void *_other) {

    /* Initializing variables */
    auto int *self = (int *) _self, *other = (int *) _other;

    /* Main part */
    if (*self < *other) {
        return -1;
    } else if (*self > *other) {
        return 1;
    } else {
        return 0;
    }
}

void fillInTree(tree *t, int n) {

    /* Initializing variables */
    auto int val, i;

    /* Main part */
    for (i = 0; i < n; ++i) {
        val = rand() % 100;
        printf("%d ", val);
        Tree_insert(t, &val, sizeof(val), inumcmp);
    }
    printf("\n\n");
}

void node_print(const tree_node *node) {

    /* Initializing variables */
    auto int *val = node->value;

    /* Main part */
    printf("%d\n", *val);
}

void deleteRand(tree *t) {

    /* Initializing variables */
    auto tree_node *curr;
    auto enum way w;
    auto int val;

    /* Main part */
    for (curr = Tree_begin(t); ;) {
        w = rand() % 3 + 1;
        if (w == LEFT && curr->left != NULL) {
            curr = curr->left;
        } else if (w == RIGHT && curr->right != NULL) {
            curr = curr->right;
        } else {
            val = *((int *) Tree_get_value(curr));
            Tree_erase(t, &val, inumcmp);
            break;
        }
    }

    /* Final output */
    printf("\n\nDeleted item: %d\n\n", val);
}