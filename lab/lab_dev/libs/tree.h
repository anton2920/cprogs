#ifndef LAB_DEV_TREE_H
#define LAB_DEV_TREE_H

/* Header inclusions */
#include <stdio.h>

/* New data types */
typedef struct tree_node {
    void *value;
    size_t nbytes;

    struct tree_node *left;
    struct tree_node *right;
} tree_node_t;

typedef struct tree {
    tree_node_t *root;
} tree_t;

enum Tree_errors {
    Tree_OK = 1,                    /* Everything is OK. Not an error */
    Tree_memory_error,              /* If Tree routine can't allocate memory */
    Tree_null_reference_error       /* If (Tree *) or (const void *elem) is NULL */
};

/* Tree methods */
int Tree_init(tree_t *);
int Tree_delete(tree_t *);

int Tree_isEmpty(const tree_t *);

int Tree_Node_delete(tree_node_t *);
tree_node_t *Tree_Node_insert(tree_node_t *node, const void *item, size_t size, int (*)(const void *, const void *));
tree_node_t *Tree_insert(tree_t *t, const void *, size_t, int (*)(const void *, const void *));

tree_node_t *Tree_begin(const tree_t *);
/* tree_node_t *Tree_get_parent(const tree_node_t *); */
tree_node_t *Tree_get_left_child(const tree_node_t *);
tree_node_t *Tree_get_right_child(const tree_node_t *);
void      *Tree_get_value(const tree_node_t *);

void Tree_print(const tree_t *t, void (*)(const tree_node_t *));

#endif
