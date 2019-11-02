#ifndef LAB_DEV_LIBS_H
#define LAB_DEV_LIBS_H

/* Header inclusions */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

/* Macro definitions */

/* Type definitions */
struct element {
    int key;
    size_t naccess;
};

/* Functions declarations */
void fillInTree(tree *, FILE *);
double doAccess(tree *);
void doAccess2(tree_node *);
void rearrange(tree *new_t, const tree *t);
void print_node(const tree_node *);

#endif
