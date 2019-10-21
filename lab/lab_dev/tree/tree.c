#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

int Tree_init(tree *t) {

    /* Initializing variables */

    /* VarCheck */
    if (t == NULL) {
        return Tree_null_reference_error;
    }

    /* Returning value */
    return Tree_OK;
}

int Tree_delete(tree *t) {

    /* VarCheck */
    if (t == NULL) {
        return Tree_null_reference_error;
    }

    /* Main part */
    return Tree_Node_delete(t->base);
}

int Tree_isEmpty(const tree *t) {

    /* VarCheck */
    if (t == NULL) {
        return Tree_null_reference_error;
    }

    /* Main part */
    if (Tree_begin(t)->nchild) {
        return 1;
    } else {
        return 0;
    }
}

int Tree_Node_delete(tree_node *node) {

    /* Initializing variables */
    register size_t i;

    /* VarCheck */
    if (node == NULL) {
        return Tree_null_reference_error;
    }

    /* Main part */
    for (i = 0; i < node->nchild; ++i) {
        if (node->child[i] != NULL) {
            Tree_Node_delete(node->child[i]);
        }
    }

    free(node->value);
    free(node);

    return Tree_OK;
}

tree_node *Tree_Node_insert(tree_node *node, const void *item, size_t size) {

    /* Initializing variables */
    auto tree_node **tmp;

    /* VarCheck */
    if (node == NULL) {
        return NULL;
    }

    /* Main part */
    if (node->child != NULL) {
        if ((tmp = (tree_node **) calloc(node->nchild + 1, sizeof(tree_node *))) == NULL) {
            return NULL;
        }

        memcpy(tmp, node->child, node->nchild * sizeof(tree_node *));

        if ((tmp[node->nchild] = (tree_node *) calloc(1, sizeof(tree_node))) == NULL) {
            return NULL;
        }

        free(node->child);
        node->child = tmp;

    } else {
        if ((node->child = (tree_node **) calloc(1, sizeof(tree_node *))) == NULL) {
            return NULL;
        }
        if ((node->child[0] = (tree_node *) calloc(1, sizeof(tree_node))) == NULL) {
            return NULL;
        }
        ++node->nchild;
    }

    if ((node->child[node->nchild - 1]->value = malloc(size)) == NULL) {
        free(node->child[node->nchild - 1]);
        --node->nchild;
        return NULL;
    }

    memcpy(node->child[node->nchild - 1]->value, item, size);

    /* Returning value */
    return node->child[node->nchild - 1];
}

tree_node *Tree_begin(const tree *t) {

    /* VarCheck */
    if (t == NULL) {
        return NULL;
    }

    /* Returning value */
    return t->base;
}

tree_node *Tree_get_parent(const tree_node *node) {

    /* VarCheck */
    if (node == NULL) {
        return NULL;
    }

    /* Returning value */
    return node->parent;
}

size_t Tree_get_nchild(const tree_node *node) {

    /* VarCheck */
    if (node == NULL) {
        return 0;
    }

    /* Returning value */
    return node->nchild;
}

tree_node *Tree_get_child(const tree_node *node, size_t pos) {

    /* VarCheck */
    if (node == NULL) {
        return NULL;
    }

    if (pos >= node->nchild) {
        return NULL;
    }

    /* Returning value */
    return node->child[pos];
}

void *Tree_get_value(const tree_node *node) {

    /* VarCheck */
    if (node == NULL) {
        return NULL;
    }

    /* Returning value */
    return node->value;
}

static void Tree_Node_print(const tree_node *node, size_t Tree_print_counter, void (*print_node_value)(const tree_node *)) {

    /* Initializing variables */
    auto size_t i;

    /* VarCheck */
    if (node == NULL) {
        return;
    }

    /* Main part */
    printf("\t----\t----\t----\t----\n");
    printf("Node level: %lu\n", Tree_print_counter);
    printf("This node has %lu %s\n", Tree_get_nchild(node), Tree_get_nchild(node) == 1 ? "child" : "children");
    printf("Nodes value: ");
    print_node_value(node->value);
    printf("\t----\t----\t----\t----\n");

    for (i = 0; i < Tree_get_nchild(node); ++i) {
        Tree_Node_print(Tree_get_child(node, i), Tree_print_counter + 1, print_node_value);
    }
}

void Tree_Print(const tree *t, void (*print_node_value)(const tree_node *)) {

    /* Main part */
    Tree_Node_print(Tree_begin(t), 0lu, print_node_value);
}

int Tree_Node_count(const tree_node *node, const void *elem, int (*cmp)(const void *, const void *)) {

    /* Initializing variables */
    auto size_t count = 0;
    register size_t i;

    /* Main part */
    for (i = 0; i < Tree_get_nchild(node); ++i) {
        if (!cmp(elem, Tree_get_value(node))) {
            ++count;
        }
        if (Tree_get_child(node, i) != NULL) {
            count += Tree_Node_count(Tree_get_child(node, i), elem, cmp);
        }
    }

    /* Returning value */
    return count;
}

int Tree_count(const tree *t, const void *elem, int (*cmp)(const void *, const void *)) {

    /* Returning value */
    return Tree_Node_count(Tree_begin(t), elem, cmp);
}