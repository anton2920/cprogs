#ifndef LAB_DEV_LIBS_H
#define LAB_DEV_LIBS_H

/* Header inclusion */

/* New data types */

/* Node of our priority queue */
typedef struct {
    int priority;
    char *data;
} node_t;

/* Priority queue based on binary heap */
typedef struct {
    node_t *nodes;
    int len;
    int size;
} heap_t;

/* Functions' declarations */
void insert(heap_t *h, int priority, char *data);
char *delete_min(heap_t *h);

#endif
