#include <stdlib.h>
#include <string.h>

#include "tree.h"

static int max(int a, int b) {

    /* Returning value */
    return (a > b) ? a : b;
}

static Tree_node *Tree_single_rotate_right(Tree_node *k2) {

    /* Initializing variables */
    auto Tree_node *k1 = NULL;

    /* Main part */
    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max(Tree_get_height(k2->left), Tree_get_height(k2->right)) + 1;
    k1->height = max(Tree_get_height(k1->left), Tree_get_height(k2)) + 1;

    /* Returning value */
    return k1;
}

static Tree_node *Tree_single_rotate_left(Tree_node *k1) {

    /* Initializing variables */
    auto Tree_node *k2 = NULL;

    /* Main part */
    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = max(Tree_get_height(k1->left), Tree_get_height(k1->right)) + 1;
    k2->height = max(Tree_get_height(k2->right), Tree_get_height(k1)) + 1;

    /* Returning value */
    return k2;
}

static Tree_node *Tree_double_rotate_left_right(Tree_node *k1) {

    /* Main part */
    k1->left = Tree_single_rotate_left(k1->left);

    /* Returning value */
    return Tree_single_rotate_right(k1);
}

static Tree_node *Tree_double_rotate_right_left(Tree_node *k1) {

    /* Main part */
    k1->right = Tree_single_rotate_right(k1->right);

    /* Returning value */
    return Tree_single_rotate_left(k1);
}

static int Tree_get_balance(const Tree_node *node) {

    /* VarCheck */
    if (node == NULL) {
        return 0;
    }

    /* Returning value */
    return Tree_get_height(node->right) - Tree_get_height(node->left);
}

int Tree_init(Tree *t) {

    /* VarCheck */
    if (t == NULL) {
        return Tree_null_reference_error;
    }

    /* Main part */
    if ((t->root = (Tree_node *) calloc(1, sizeof(Tree_node))) == NULL) {
        return Tree_memory_error;
    }

    t->root->left = t->root->right = t->root->value = NULL;
    t->root->nbytes = 0lu;

    /* Returning value */
    return Tree_OK;
}

static int Tree_Node_delete(Tree_node *node) {

    /* VarCheck */
    if (node == NULL) {
        return Tree_null_reference_error;
    }

    /* Main part */
    if (node->left == NULL && node->right == NULL) {
        free(node->value);
        free(node);
        return Tree_OK;
    } else {
        Tree_Node_delete(node->left);
        Tree_Node_delete(node->right);
    }
}

int Tree_delete(Tree *t) {

    /* VarCheck */
    if (t == NULL) {
        return Tree_null_reference_error;
    }

    /* Main part */
    return Tree_Node_delete(Tree_begin(t));
}

int Tree_erase(Tree *t, void *item, int (*cmp)(const void *, const void *)) {

    /* VarCheck */
    if (t == NULL) {
        return Tree_null_reference_error;
    }

    t->root = Tree_Node_erase(t->root, item, cmp);

    /* Returning value */
    return Tree_OK;
}

int Tree_isEmpty(const Tree *t) {

    /* VarCheck */
    if (t == NULL) {
        return Tree_null_reference_error;
    }

    /* Returning value */
    return t->root->value == NULL ? 1 : 0;
}

static Tree_node *Tree_min_value_node(Tree_node *node) {

    /* Main part */
    while (node->left != NULL) {
        node = node->left;
    }

    /* Returning value */
    return node;
}

Tree_node *Tree_Node_erase(Tree_node *node, void *item, int (*cmp)(const void *, const void *)) {

    /* Initializing variables */
    auto Tree_node *tmp;
    auto int res;

    /* Main part */
    if (node == NULL) {
        return NULL;
    }
    if ((res = cmp(item, node->value)) == -1) {
        node->left = Tree_Node_erase(node->left, item, cmp);
    } else if (res == 1) {
        node->right = Tree_Node_erase(node->right, item, cmp);
    } else {
        if (node->left == NULL || node->right == NULL) {
            tmp = node->left != NULL ? node->left : node->right;

            free(node->value);
            if (tmp == NULL) {
                tmp = node;
                node = NULL;
            } else {
                memcpy(node, tmp, sizeof(Tree_node));
            }

            free(tmp);
        } else {
            tmp = Tree_min_value_node(node->right);

            memcpy(node->value, tmp->value, node->nbytes);
            node->right = Tree_Node_erase(node->right, tmp->value, cmp);
        }
    }

    if (node == NULL) {
        return NULL;
    }

    node->height = max(Tree_get_height(node->left), Tree_get_height(node->right)) + 1;

    if (Tree_get_balance(node) < -1) {
        if (Tree_get_balance(node->left) <= 0) {
            node = Tree_single_rotate_right(node);
        } else {
            node = Tree_double_rotate_left_right(node);
        }
    } else if (Tree_get_balance(node) > 1) {
        if (Tree_get_balance(node->right) >= 0) {
            node = Tree_single_rotate_left(node);
        } else {
            node = Tree_double_rotate_right_left(node);
        }
    }

    /* Returning value */
    return node;
}

Tree_node *Tree_Node_insert(Tree_node *node, const void *item, size_t size, int (*cmp)(const void *, const void *)) {

    /* Initializing variables */
    auto int res;

    /* Main part */
    if (node == NULL) {
        if ((node = (Tree_node *) calloc(1, sizeof(Tree_node))) == NULL) {
            return NULL;
        }
        if ((node->value = malloc(size)) == NULL) {
            free(node);
            return NULL;
        }
        memcpy(node->value, item, size);
        node->nbytes = size;
        node->height = 0;
        node->left = node->right = NULL;
    } else if ((res = cmp(item, node->value)) == -1) {
        node->left = Tree_Node_insert(node->left, item, size, cmp);
    } else if (res == 1) {
        node->right = Tree_Node_insert(node->right, item, size, cmp);
    } else {
        return node;
    }

    node->height = max(Tree_get_height(node->left), Tree_get_height(node->right)) + 1;

    if (Tree_get_balance(node) < -1) {
        if (Tree_get_balance(node->left) == -1) {
            node = Tree_single_rotate_right(node);
        } else {
            node = Tree_double_rotate_left_right(node);
        }
    } else if (Tree_get_balance(node) > 1) {
        if (Tree_get_balance(node->right) == 1) {
            node = Tree_single_rotate_left(node);
        } else {
            node = Tree_double_rotate_right_left(node);
        }
    }

    /* Returning value */
    return node;
}

Tree_node *Tree_insert(Tree *t, const void *item, size_t size, int (*cmp)(const void *, const void *)) {

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
        Tree_begin(t)->height = 0;
    } else {
        return t->root = Tree_Node_insert(t->root, item, size, cmp);
    }

    /* Returning value */
    return NULL;
}

Tree_node *Tree_begin(const Tree *t) {

    /* VarCheck */
    if (t == NULL) {
        return NULL;
    }

    /* Returning value */
    return t->root;
}

Tree_node *Tree_get_left_child(const Tree_node *node) {

    /* VarCheck */
    if (node == NULL) {
        return NULL;
    }

    /* Returning value */
    return node->left;
}

Tree_node *Tree_get_right_child(const Tree_node *node) {

    /* VarCheck */
    if (node == NULL) {
        return NULL;
    }

    /* Returning value */
    return node->right;
}

void *Tree_get_value(const Tree_node *node) {

    /* VarCheck */
    if (node == NULL) {
        return NULL;
    }

    /* Returning value */
    return node->value;
}

int Tree_get_height(const Tree_node *node) {

    /* VarCheck */
    if (node == NULL) {
        return -1;
    }

    /* Returning value */
    return node->height;
}

static void Tree_Node_print(const Tree_node *node, size_t Tree_print_counter, void (*print_node_value)(const Tree_node *)) {

    /* VarCheck */
    if (node == NULL) {
        return;
    }

    /* Main part */
    /*printf("\t----\t----\t----\t----\n");
    printf("Node level: %lu\n", Tree_print_counter);
    printf("Node's value: ");*/
    print_node_value(node);
    printf(" on level %lu\n", Tree_print_counter);

    Tree_Node_print(node->left, Tree_print_counter + 1, print_node_value);
    Tree_Node_print(node->right, Tree_print_counter + 1, print_node_value);
}

void Tree_print(const Tree *t, void (*print_node_value)(const Tree_node *)) {

    /* Main part */
    Tree_Node_print(Tree_begin(t), 0lu, print_node_value);
}