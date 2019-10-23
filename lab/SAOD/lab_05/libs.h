#ifndef LAB_DEV_LIBS_H
#define LAB_DEV_LIBS_H

/* Header inclusions */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

/* Macro definitions */

/* Type definitions */
enum consts {
    NAME = 30
};

struct employee {
    char ln[NAME];
    char fn[NAME];
    unsigned building;
    enum department {
        CSaS = 1,
        CTS,
        FM,
        GP,
        Tb,
        EE,
    } dep;
    unsigned room;
};

/* Functions declarations */
void fillInTree(tree *t);
void checkTree(const tree *);

#endif