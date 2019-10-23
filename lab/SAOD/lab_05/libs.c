#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "libs.h"

void fillInTree(tree *t) {

    /* Initializing variables */
    auto FILE *fp = fopen("input.txt", "r");
    auto struct employee e, *c;
    auto size_t i;
    auto int j;
    auto unsigned k;
    auto tree_node *curr, *prev;
    auto int flag;

    /* I/O flow */
    if (fp == NULL) {
        return;
    }

    for ( ; !feof(fp); ) {
        flag = 1;

        fscanf(fp, "%s %s %u %d %u", e.ln, e.fn, &e.building, &e.dep, &e.room);

        /* Building */
        curr = prev = Tree_begin(t);
        for (i = 0lu; i < Tree_get_nchild(prev); ++i) {
            if (*((unsigned *) curr->child[i]->value) == e.building) {
                curr = curr->child[i];
                break;
            }
        }

        if ((i == Tree_get_nchild(prev) && curr == prev) || !Tree_get_nchild(prev)) {
            k = e.building;
            Tree_Node_insert(curr, &k, sizeof(unsigned));
            curr = Tree_get_child(curr, Tree_get_nchild(curr) - 1);
        }

        /* Department */
        prev = curr;
        for (i = 0lu; i < Tree_get_nchild(prev); ++i) {
            if (*((int *) curr->child[i]->value) == e.dep) {
                curr = curr->child[i];
                break;
            }
        }

        if ((i == Tree_get_nchild(prev) && curr == prev) || !Tree_get_nchild(prev)) {
            j = e.dep;
            Tree_Node_insert(curr, &j, sizeof(int));
            curr = Tree_get_child(curr, Tree_get_nchild(curr) - 1);
        }

        /* Room */
        prev = curr;
        for (i = 0lu; i < Tree_get_nchild(prev); ++i) {
            if (*((unsigned *) curr->child[i]->value) == e.room) {
                curr = curr->child[i];
                break;
            }
        }

        if ((i == Tree_get_nchild(prev) && curr == prev) || !Tree_get_nchild(prev)) {
            i = e.room;
            Tree_Node_insert(curr, &i, sizeof(size_t));
            curr = Tree_get_child(curr, Tree_get_nchild(curr) - 1);
        }

        /* Employee */
        prev = curr;
        for (i = 0lu; i < Tree_get_nchild(prev); ++i) {
            c = (struct employee *) Tree_get_value(Tree_get_child(curr, i));
            if (!strcmp(e.ln, c->ln) && !strcmp(e.fn, c->fn) && e.building == c->building
                && e.dep == c->dep && e.room == c->room) {
                flag = 0;
            }
        }

        if (flag) {
            Tree_Node_insert(curr, &e, sizeof(struct employee));
        }
    }

    fclose(fp);
}

void checkTree(const tree *t) {

    /* Initializing variables */
    auto tree_node *curr;
    auto FILE *fp = fopen("input.txt", "r");
    auto size_t i, j, k, counter = 0, z;
    auto struct employee e, *c;

    /* I/O flow */
    if (fp == NULL) {
        return;
    }

    /* Main part */
    for ( ; !feof(fp); ) {                                                                              /* For-each record */
        fscanf(fp, "%s %s %u %d %u", e.ln, e.fn, &e.building, &e.dep, &e.room);
        for (i = 0, curr = Tree_begin(t); i < Tree_get_nchild(curr); ++i) {                             /* For-each building */
            for (j = 0; j < Tree_get_nchild(curr->child[i]); ++j) {                                     /* For-each department */
                for (k = 0; k < Tree_get_nchild(curr->child[i]->child[j]); ++k) {                       /* For-each room */
                    for (z = 0; z < Tree_get_nchild(curr->child[i]->child[j]->child[k]); ++z) {         /* For-each employee */
                        c = (struct employee *) curr->child[i]->child[j]->child[k]->child[z]->value;    /* Employee */
                        if (!strcmp(e.ln, c->ln) && !strcmp(e.fn, c->fn) && e.building == c->building
                            && e.dep == c->dep && e.room == c->room) {
                            ++counter;
                        }
                    }
                }
            }
        }
        if (counter > 1) {
            printf("Employee %s %s occurs more than once\n", e.ln, e.fn);
        } else if (!counter) {
            printf("Employee %s %s didn't occur\n", e.ln, e.fn);
        } else {
            printf("Employee %s %s occurs correctly\n", e.ln, e.fn);
        }

        counter = 0;
    }
}