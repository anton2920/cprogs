#ifndef LAB_DEV_TREE_H
#define LAB_DEV_TREE_H

/* New type definitions */
typedef struct __tree_node {
    void *value;
    size_t nchild;

    struct __tree_node *parent;
    struct __tree_node **child;
} tree_node;

typedef struct __tree {
    struct __tree_node *base;
} tree;

enum Tree_errors {
    Tree_OK = 1,                    /* Everything is OK. Not an error */
    Tree_memory_error,              /* If Tree routine can't allocate memory */
    Tree_index_error,               /* If desired position is wrong */
    Tree_null_reference_error       /* If (Tree *) or (const void *elem) is NULL */
};

/* Tree methods */
int Tree_init(tree *);
int Tree_delete(tree *);

int Tree_isEmpty(const tree *);

int Tree_Node_delete(tree_node *);
tree_node *Tree_Node_insert(tree_node *node, const void *item, size_t size);

tree_node *Tree_begin(const tree *);
tree_node *Tree_get_parent(const tree_node *);
size_t     Tree_get_nchild(const tree_node *);
tree_node *Tree_get_child(const tree_node *, size_t);
void      *Tree_get_value(const tree_node *);

void Tree_print(const tree *t, void (*)(const tree_node *));

int Tree_count(const tree *t, const void *, int (*)(const void *, const void *));

#endif