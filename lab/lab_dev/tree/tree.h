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
} tree_node;

typedef struct __tree {
    tree_node *root;
    size_t nelem;
    size_t level;
} tree;

enum Tree_errors {
    Tree_OK = 1,                    /* Everything is OK. Not an error */
    Tree_memory_error,              /* If Tree routine can't allocate memory */
    Tree_null_reference_error       /* If (Tree *) or (const void *elem) is NULL */
};

/* Tree methods */
int Tree_init(tree *);
int Tree_delete(tree *);

int Tree_isEmpty(const tree *);

int Tree_Node_delete(tree_node *);
tree_node *Tree_Node_insert(tree_node *node, const void *item, size_t size, int (*)(const void *, const void *));
tree_node *Tree_insert(tree *t, const void *, size_t, int (*)(const void *, const void *));

tree_node *Tree_begin(const tree *);
/* tree_node *Tree_get_parent(const tree_node *); */
tree_node *Tree_get_left_child(const tree_node *);
tree_node *Tree_get_right_child(const tree_node *);
void      *Tree_get_value(const tree_node *);
size_t     Tree_get_nelem(const tree *);
size_t     Tree_get_max_level(const tree *);

void Tree_print(const tree *t, void (*)(const tree_node *));

#endif
