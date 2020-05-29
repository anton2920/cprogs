#include <stdlib.h>

#include "process.h"

process *create_process(unsigned int pid, enum status st, time_t max_duration, time_t tqt) {

    /* Initializing variables */
    auto process *ret;

    /* Main part */
    if ((ret = calloc(1, sizeof(process))) == NULL) {
        return NULL;
    }

    ret->pid = pid;
    ret->st = st;
    ret->duration = (rand() % max_duration) + 1;
    ret->total_time = ret->awaiting = ret->in_system = 0;
    ret->this_q_time = tqt;

    /* Returning value */
    return ret;
}

void kill_process(process *p) {

    /* Main part */
    free(p);
}