#include <stdio.h>
#include <string.h>

#include "libs.h"

static int elemcmp(const void *_self, const void *_other) {

    /* Initializing variables */
    auto struct element *self = (struct element *) _self, *other = (struct element *) _other;

    if (self->key < other->key) {
        return -1;
    } else if (self->key > other->key) {
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
            Tree_insert(t, &a, sizeof(struct element), elemcmp);
        }
    } else {
        for ( ; !feof(fp); ) {
            fscanf(fp, "%d", &a.key);
            Tree_insert(t, &a, sizeof(struct element), elemcmp);
        }
    }
}

void doAccess2(tree_node *node) {

    /* Initializing variables */
    auto struct element *elem;

    /* VarCheck */
    if (node == NULL) {
        return;
    }

    /* Main part */
    elem = (struct element *) node->value;
    elem->naccess = (rand() % (5000 - 1000 + 1)) + 1000;

    doAccess2(node->left);
    doAccess2(node->right);
}

static int cmpElem(const struct element *self, const struct element *other) {

    /* Main part */
    if (self->naccess == other->naccess) {
        if (self->key == other->key) {
            return 1;
        } else {
            return 0;
        }
    } else if (self->naccess < other->naccess){
        return 0;
    } else {
        return 1;
    }
}

static tree_node *cmpAcc(tree_node *_self, tree_node *_other) {

    /* VarCheck */
    if (_self == NULL) {
        return _other;
    } else if (_other == NULL) {
        return _self;
    }

    /* Initializing variables */
    auto struct element *self = (struct element *) _self->value;
    auto struct element *other = (struct element *) _other->value;

    /* Main part */
    return self->naccess < other->naccess ? _other : _self;
}

static tree_node *findMaxAcc(tree_node *node, tree_node *max, tree_node *prev_max) {

    /* Main part */
    if (node == NULL) {
        return NULL;
    } else {
        max = cmpAcc(findMaxAcc(node->left, max, prev_max),
                findMaxAcc(node->right, max, prev_max));
        if (max != NULL) {
            if (prev_max != NULL) {
                if (!cmpElem(node->value, prev_max->value)) {
                    if (cmpElem(node->value, max->value)) {
                        max = node;
                    }
                }
            } else {
                if (cmpElem(node->value, max->value)) {
                    max = node;
                }
            }
        } else {
            if (prev_max != NULL) {
                if (!cmpElem(node->value, prev_max->value)) {
                    max = node;
                }
            } else {
                max = node;
            }
        }
    }

    /* Returning value */
    return max;
}

void rearrange(tree *new_t, const tree *t) {

    /* Initializing variables */
    auto tree_node *max = NULL, *prev_max;

    /* Main part */
    do {
        prev_max = max;
        max = findMaxAcc(Tree_begin(t), NULL, prev_max);
        if (max == NULL) {
            break;
        }
        Tree_insert(new_t, max->value, max->nbytes, elemcmp);
    } while (1);
}

void print_node(const tree_node *node) {

    /* VarCheck */
    if (node == NULL) {
        return;
    }

    /* Initializing variables */
    auto struct element *elem = (struct element *) node->value;

    /* Main part */
    printf(" { %d; %lu }\n", elem->key, elem->naccess);
}