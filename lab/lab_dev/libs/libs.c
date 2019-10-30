#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "libs.h"

static int inumcmp(const void *_self, const void *_other) {

    /* Initializing variables */
    auto int *self = (int *) _self, *other = (int *) _other;

    if (*self < *other) {
        return -1;
    } else if (*self > *other) {
        return 1;
    } else {
        return 0;
    }
}

void fillInTree(tree *t, FILE *fp) {

    /* Initializing variables */
    auto struct element a;
    a.naccess = 0;
    auto size_t n, i;

    /* Main part */
    if (fp == NULL) {
        n = (rand() % (100 - 50 + 1)) + 50;
        for (i = 0; i < n; ++i) {
            a.key = rand() % 101;
            Tree_insert(t, &a, sizeof(struct element), inumcmp);
        }
    } else {
        for ( ; !feof(fp); ) {
            fscanf(fp, "%d", &a.key);
            Tree_insert(t, &a, sizeof(struct element), inumcmp);
        }
    }
}

static void incAcc(tree_node *node) {

    /* Initializing variables */
    auto struct element *elem;

    /* Main part */
    elem = node->value;
    ++elem->naccess;
}

double doAccess(tree *t) {

    /* Initializing variables */
    auto size_t i, n;
    auto enum way w;
    auto tree_node *curr = Tree_begin(t);
    auto double mean = 0.0;
    auto size_t length;

    /* Main part */
    n = (rand() % (5000 - 1000 + 1)) + 1000;

    for (i = 0, length = 0; i < n; ) {
        w = rand() % 3;
        if (w == LEFT && Tree_get_left_child(curr) != NULL) {
            curr = Tree_get_left_child(curr);
            ++length;
        } else if (w == RIGHT && Tree_get_right_child(curr) != NULL) {
            curr = Tree_get_right_child(curr);
            ++length;
        } else {
            incAcc(curr);
            curr = Tree_begin(t);
            ++i;
            mean += (double) length;
            length = 0;
        }
    }

    /* Returning value */
    return mean;
}

static tree_node *cmpAcc(tree_node *_self, tree_node *_other) {

    /* Initializing variables */
    auto struct element *self = (struct element *) _self->value;
    auto struct element *other = (struct element *) _other->value;

    /* Main part */
    if (self->naccess < other->naccess) {
        return _other;
    } else {
        return _self;
    }
}

static tree_node *findMaxAcc(tree_node *node) {

    /* Initializing variables */
    auto tree_node *max, *a, *b;

    /* Main part */
    if (node == NULL) {
        return 0lu;
    } else {
        a = (node->left != NULL) ? findMaxAcc(node->left) : node;
        b = (node->right != NULL) ? findMaxAcc(node->right) : node;
        max = cmpAcc(a, b);
    }

    /* Returning value */
    return max;
}

void rearrange(tree *new_t, const tree *t) {

    /* Initializing variables */
    auto size_t max;

    /* Main part */
    max = findMaxAcc(Tree_begin(t));
}