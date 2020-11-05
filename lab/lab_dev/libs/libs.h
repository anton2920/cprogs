#ifndef LAB_DEV_LIBS_H
#define LAB_DEV_LIBS_H

/* New value types */
typedef struct list_node {
    int data;
    struct list_node *next;
} list_node_t;

typedef struct list {
    list_node_t *head;
    int nelem;
} list_t;

/* Functions' declarations */
void list_init(list_t *self);
void list_clear(list_t *self);
void list_delete(list_t *self);
void list_insert(list_t *self, list_node_t *before, int data);
void list_remove(list_t *self, list_node_t *before);

#endif
