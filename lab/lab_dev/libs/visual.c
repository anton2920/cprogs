#include "visual.h"
#include "process.h"

int pidcmp(const void *_self, const void *_other) {

    /* Initializing variables */
    auto process *self = (process *) _self, *other = (process *) _other;

    /* Returning value */
    return ((self->pid > other->pid) ? 1 : (self->pid < other->pid) ? -1 : 0);
}

void draw_hlrr(const STL_Vector *process_v) {

}

void draw_rr(const STL_Queue *process_q) {

    /* Main part */
}