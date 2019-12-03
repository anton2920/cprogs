#ifndef GVK_THE_BEST_TREE_EVER_O_1
#define GVK_THE_BEST_TREE_EVER_O_1

/* Header inclusion */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* New data types */
typedef struct _node {
    int key;
    struct _node *s_left;
    struct _node *s_right;
} node;

typedef node sheet;

extern node *headTree;
extern FILE *f;

void addNode(int keyNode, node **node_pointer);
void makeTree(node *head);
void build_AVL_Tree();
int high_p(node *node);
int checkTree(node *node);
node *search_rod(int key_, node *node);
node *search(int key_, node *node);
node *search_left(node *node);
void addKey(int temp, node *head);
int delKey(int key);
int balans(node *node);
int balansTree(node *node);

#endif