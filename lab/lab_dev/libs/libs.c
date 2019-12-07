#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libs.h"

static tree_node *search_for_insert(tree_node *node, size_t level, size_t curr_level) {

    /* Initializing variables */
    auto tree_node *tmp;

    /* Main part */
    if (curr_level == level - 1) {
        if (node->left == NULL || node->right == NULL) {
            return node;
        } else {
            return NULL;
        }
    } else if (curr_level > level - 1) {
        return NULL;
    }

    tmp = search_for_insert(node->left, level, curr_level + 1);
    if (tmp != NULL) {
        return tmp;
    } else {
        node = search_for_insert(node->right, level, curr_level + 1);
    }

    /* Returning value */
    return node;
}

static void insert(tree_node *node, const void *elem, size_t size) {

    /* Main part */
    if (node->left == NULL) {
        node->left = (tree_node *) calloc(1, sizeof(tree_node));
        node->left->value = malloc(size);
        memcpy(node->left->value, elem, size);
        node->left->nbytes = size;
        node->left->left = node->left->right = NULL;
    } else if (node->right == NULL) {
        node->right = (tree_node *) calloc(1, sizeof(tree_node));
        node->right->value = malloc(size);
        memcpy(node->right->value, elem, size);
        node->right->nbytes = size;
        node->right->left = node->right->right = NULL;
    } else {
        return;
    }
}

void add_element(tree *t, const void *elem, size_t size) {

    /* Main part */
    if (!Tree_get_nelem(t)) {
        t->root->value = malloc(size);
        memcpy(t->root->value, elem, size);
        t->root->nbytes = size;
        t->root->left = t->root->right = NULL;
    } else {
        insert(search_for_insert(Tree_begin(t), Tree_get_max_level(t), 0), elem, size);
    }

    ++t->nelem;

    switch (Tree_get_nelem(t)) {
        case 1: case 3: case 7: case 15:
            ++t->level;
            break;
        default:
            break;
    }
}