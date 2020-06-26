#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "libs.h"

void insert(heap_t *h, int priority, char *data) {

    /* Initializing variables */
    auto int i = h->len + 1;
    auto int j = i / 2;

    /* VarCheck */
    assert(h != NULL && priority > 0 && data != NULL);

    /* Main part */
    if (h->len + 1 >= h->size) {
        h->size = h->size ? h->size * 2 : 4;
        h->nodes = (node_t *) realloc(h->nodes, h->size * sizeof(node_t));
    }

    while (i > 1 && h->nodes[j].priority > priority) {
        h->nodes[i] = h->nodes[j];
        i = j;
        j = j / 2;
    }

    h->nodes[i].priority = priority;
    h->nodes[i].data = data;
    h->len++;
}

char *delete_min(heap_t *h) {

    /* Initializing variables */
    auto int i, j, k;

    /* VarCheck */
    assert(h != NULL);

    if (!h->len) {
        return NULL;
    }

    /* Main part */
    auto char *data = h->nodes[1].data;

    h->nodes[1] = h->nodes[h->len];

    h->len--;

    i = 1;
    while (i != h->len + 1) {
        k = h->len + 1;
        j = 2 * i;
        if (j <= h->len && h->nodes[j].priority < h->nodes[k].priority) {
            k = j;
        }
        if (j + 1 <= h->len && h->nodes[j + 1].priority < h->nodes[k].priority) {
            k = j + 1;
        }
        h->nodes[i] = h->nodes[k];
        i = k;
    }

    /* Returning value */
    return data;
}