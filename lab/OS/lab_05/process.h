#ifndef LAB_DEV_PROCESS_H
#define LAB_DEV_PROCESS_H

/* Header inclusion */
#include <time.h>

/* New data types */
enum status {
    waiting,
    active
};

typedef struct _process {
    enum status st;

    unsigned int pid;

    time_t duration;
    time_t awaiting;
    time_t in_system;
    time_t total_time;

    double reactivity;
    double fine_relation;

    double p; /* Priority */
    double u; /* CPU time counter */
} process;

/* Functions' declarations */
process *create_process(unsigned int pid, enum status st, time_t max_duration, double priority);
void kill_process(process *p);

#endif