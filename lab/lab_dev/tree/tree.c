#include <stdlib.h>
#include <string.h>

#include "tree.h"

int Tree_init(tree *t) {

    /* VarCheck */
    if (t == NULL) {
        return Tree_null_reference_error;
    }

    /* Main part */
    if ((t->root = (tree_node *) calloc(1, sizeof(tree_node))) == NULL) {
        return Tree_memory_error;
    }

    t->root->left = t->root->right = t->root->value = NULL;
    t->nelem = t->level = 0lu;
    t->root->nbytes = 0lu;
}
int Tree_delete(tree *t) {

    /* VarCheck */
    if (t == NULL) {
        return Tree_null_reference_error;
    }

    /* Returning value */
    return Tree_Node_delete(t->root);
}

int Tree_isEmpty(const tree *t) {

    /* VarCheck */
    if (t == NULL) {
        return Tree_null_reference_error;
    }

    /* Returning value */
    return t->root->value == NULL ? 1 : 0;
}

int Tree_Node_delete(tree_node *t) {

    /* Main part */
    if (t == NULL) {
        return Tree_null_reference_error;
    }
    if (t->left == NULL && t->right == NULL) {
        free(t->value);
        free(t);
        return Tree_OK;
    } else {
        Tree_Node_delete(t->left);
        Tree_Node_delete(t->right);
    }

    /* Returning value */
    return Tree_OK;
}

tree_node *Tree_Node_insert(tree_node *node, const void *item, size_t size, int (*cmp)(const void *, const void *)) {

    /* VarCheck */
    if (node == NULL) {
        return NULL;
    }

    /* Initializing variables */
    auto int res = cmp(item, node->value);
    auto tree_node *tmp;

    /* Main part */
    if (!res) {
        return node;
    } else if (res == -1 && node->left != NULL) {
        return Tree_Node_insert(node->left, item, size, cmp);
    } else if (res == 1 && node->right != NULL) {
        return Tree_Node_insert(node->right, item, size, cmp);
    } else {
        if ((tmp = (tree_node *) calloc(1, sizeof(tree_node))) == NULL) {
            return NULL;
        }
        if ((tmp->value = malloc(size)) == NULL) {
            free(tmp);
            return NULL;
        }
        memcpy(tmp->value, item, size);
        tmp->nbytes = size;
        tmp->left = tmp->right = NULL;

        if (res == -1) {
            node->left = tmp;
        } else if (res == 1) {
            node->right = tmp;
        }
    }

    return tmp;
}

tree_node *Tree_insert(tree *t, const void *item, size_t size, int (*cmp)(const void *, const void *)) {

    /* VarCheck */
    if (t == NULL) {
        return NULL;
    }

    if (Tree_isEmpty(t)) {
        if ((Tree_begin(t)->value = malloc(size)) == NULL) {
            return NULL;
        }
        memcpy(Tree_begin(t)->value, item, size);
        Tree_begin(t)->nbytes = size;
        Tree_begin(t)->left = Tree_begin(t)->right = NULL;
    } else {
        return Tree_Node_insert(t->root, item, size, cmp);
    }

    /* Returning value */
    return NULL;
}

tree_node *Tree_begin(const tree *t) {

    /* VarCheck */
    if (t == NULL) {
        return NULL;
    }

    /* Returning value */
    return t->root;
}

tree_node *Tree_get_left_child(const tree_node *node) {

    /* VarCheck */
    if (node == NULL) {
        return NULL;
    }

    /* Returning value */
    return node->left;
}

tree_node *Tree_get_right_child(const tree_node *node) {

    /* VarCheck */
    if (node == NULL) {
        return NULL;
    }

    /* Returning value */
    return node->right;
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

    /* VarCheck */
    if (node == NULL) {
        return;
    }

    /* Main part */
    printf("\t----\t----\t----\t----\n");
    printf("Node level: %lu\n", Tree_print_counter);
    printf("Node's value: ");
    print_node_value(node);

    Tree_Node_print(node->left, Tree_print_counter + 1, print_node_value);
    Tree_Node_print(node->right, Tree_print_counter + 1, print_node_value);
}

void Tree_print(const tree *t, void (*print_node_value)(const tree_node *)) {

    /* Main part */
    Tree_Node_print(Tree_begin(t), 0lu, print_node_value);
}

size_t Tree_get_nelem(const tree *t) {

    /* Returning value */
    return t->nelem;
}

size_t Tree_get_max_level(const tree *t) {

    /* Returning value */
    return t->level;
}