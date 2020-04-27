#ifndef LAB_DEV_TREE_H
#define LAB_DEV_TREE_H

/* Header inclusions */
#include <stdio.h>

/* New data types */
typedef struct __Tree_node {
    void *value;
    size_t nbytes;

    struct __Tree_node *left;
    struct __Tree_node *right;

    int height;
} Tree_node;

typedef struct __Tree {
    Tree_node *root;
} Tree;

enum Tree_errors {
    Tree_OK = 1,                    /* Everything is OK. Not an error */
    Tree_memory_error,              /* If Tree routine can't allocate memory */
    Tree_null_reference_error       /* If (Tree *) or (const void *elem) is NULL */
};

/* Tree methods */
int Tree_init(Tree *);
int Tree_delete(Tree *t);

int Tree_isEmpty(const Tree *);

Tree_node *Tree_Node_erase(Tree_node *node, void *item, int (*cmp)(const void *, const void *));
int Tree_erase(Tree *t, void *item, int (*cmp)(const void *, const void *));

Tree_node *Tree_Node_insert(Tree_node *node, const void *item, size_t size, int (*)(const void *, const void *));
Tree_node *Tree_insert(Tree *t, const void *, size_t, int (*)(const void *, const void *));

Tree_node *Tree_begin(const Tree *);
Tree_node *Tree_get_left_child(const Tree_node *);
Tree_node *Tree_get_right_child(const Tree_node *);
void      *Tree_get_value(const Tree_node *);
int        Tree_get_height(const Tree_node *);

void Tree_print(const Tree *t, void (*)(const Tree_node *));

#endif
