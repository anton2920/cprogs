#include <stdlib.h>

#include "process.h"

process *create_process(unsigned int pid, enum status st, time_t max_duration, double priority) {

    /* Initializing variables */
    auto process *ret;

    /* Main part */
    if ((ret = calloc(1, sizeof(process))) == NULL) {
        return NULL;
    }

    ret->pid = pid;
    ret->st = st;
    ret->duration = rand() % max_duration + 1;
    ret->p = priority;
    ret->total_time = ret->awaiting = 0;
    ret->u = ret->reactivity = ret->fine_relation = 0.0;

    /* Returning value */
    return ret;
}

void kill_process(process *p) {

    /* Main part */
    free(p);
}