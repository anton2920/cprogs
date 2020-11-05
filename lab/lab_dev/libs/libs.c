#include <stdlib.h>

#include "libs.h"

void list_init(list_t *self) {

    self->head = calloc(1, sizeof(list_node_t));
    self->nelem = 0;

    self->head->data = 0;
    self->head->next = NULL;
}

void list_clear(list_t *self) {

    list_node_t *iter, *tmp_next;

    for (iter = self->head; iter != NULL; iter = tmp_next) {
        tmp_next = iter->next;
        free(iter);
    }
}

void list_delete(list_t *self) {

    list_clear(self);
}

void list_insert(list_t *self, list_node_t *before, int data) {

    list_node_t *new_node = calloc(1, sizeof(list_node_t));

    new_node->data = data;

    new_node->next = before->next;
    before->next = new_node;
    ++self->nelem;
}

void list_remove(list_t *self, list_node_t *before) {

    list_node_t *tmp = before->next;

    before->next = before->next->next;
    free(tmp);
    --self->nelem;
}