#ifndef LAB_DEV_LIBS_H
#define LAB_DEV_LIBS_H

/* Header inclusions */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tree/tree.h"

/* Macro definitions */

/* Type definitions */
struct element {
    key_t key;
    size_t naccess;
};

enum way {
    LEFT = 0,
    RIGHT,
    STAND
};

/* Functions declarations */
void fillInTree(tree *, FILE *);
double doAccess(tree *);
void rearrange(tree *new_t, const tree *t);

#endif
