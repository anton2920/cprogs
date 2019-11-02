#ifndef LAB_DEV_TREE_H
#define LAB_DEV_TREE_H

/* Header inclusions */
#include <stdio.h>

/* New data types */
typedef struct __tree_node {
    void *value;
    size_t nbytes;

    struct __tree_node *left;
    struct __tree_node *right;

    int height;
} tree_node;

typedef struct __tree {
    tree_node *root;
} tree;

enum Tree_errors {
    Tree_OK = 1,                    /* Everything is OK. Not an error */
    Tree_memory_error,              /* If Tree routine can't allocate memory */
    Tree_null_reference_error       /* If (Tree *) or (const void *elem) is NULL */
};

/* Tree methods */
int Tree_init(tree *);
int Tree_delete(tree *t);

int Tree_isEmpty(const tree *);

tree_node *Tree_Node_erase(tree_node *node, void *item, int (*cmp)(const void *, const void *));
int Tree_erase(tree *t, void *item, int (*cmp)(const void *, const void *));

tree_node *Tree_Node_insert(tree_node *node, const void *item, size_t size, int (*)(const void *, const void *));
tree_node *Tree_insert(tree *t, const void *, size_t, int (*)(const void *, const void *));

tree_node *Tree_begin(const tree *);
tree_node *Tree_get_left_child(const tree_node *);
tree_node *Tree_get_right_child(const tree_node *);
void      *Tree_get_value(const tree_node *);
int        Tree_get_height(const tree_node *);

void Tree_print(const tree *t, void (*)(const tree_node *));

#endif
