#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <time.h>
#include <STL/STL_Queue.h>
#include <STL/STL_List.h>
#include <stdlib.h>

#include "libs.h"
#include "../process/process.h"
#include "../visual/visual.h"

static const int FREQ = 5; /* Probability of process occasion = 1 / FREQ */
static struct timespec pause_pamram = {0, 1e8}; /* Program delay {sec, nsec} */

void prt_ln(void) {

    /* Final output */
    printf(" ------------------------------------------------------------\n");
}

void get_values(time_t *max_duration, unsigned int *max_processes, double *p) {

    /* I/O flow */
    prt_ln();

    do {
        printf("| Type max process duration: ");
        scanf("%lu", max_duration);
    } while (*max_duration < 1);

    do {
        printf("| Type max number of processes: ");
        scanf("%u", max_processes);
    } while (*max_processes < 1);

    prt_ln();
}

void print_finals(process *average, unsigned int max_processes, unsigned int quants) {

    /* I/O flow */
    printf("| >>> Total #quants: %u\n", quants);
    prt_ln();
    printf("| >>> Average values: \n");
    printf("| Total time:    %6.3lf\n", (double) average->total_time / max_processes);
    printf("| Lost time:     %6.3lf\n", (double) average->awaiting / max_processes);
    printf("| Reactivity:    %6.3lf\n", average->reactivity / max_processes);
    printf("| Fine relation: %6.3lf\n", average->fine_relation / max_processes);

    prt_ln();
}

int check_if_empty(STL_Queue *qs, unsigned int num) {

    /* Initializing variables */
    register int i;

    /* Main part */
    for (i = 0; i < num; ++i) {
        if (!STL_Queue_empty(qs + i)) {
            return list_not_empty;
        }
    }

    /* Returning value */
    return list_is_empty;
}

void multiple_queues(void) {

    /* Initializing variables */
    auto STL_Queue qs[NUM_OF_QS]; /* Process queues */
    register int i;

    /* Initializing queues */
    for (i = 0; i < NUM_OF_QS; ++i) {
        STL_Queue_init(qs + i);
    }

    /* Current values */
    auto unsigned int current_n = 0; /* Current number of processes, which have already showed up */
    auto time_t current_quant = 0; /* Current time quant. For statistics */

    /* Limitations */
    auto unsigned int pid = 0, max_processes;
    auto time_t max_duration;

    /* Processes */
    auto process *proc, tmp, average = {};

    /* STL_List for queue traversal (junky solution) */
    auto STL_List *process_l;
    auto STL_List_node *iter;

    /* I/O flow */
    get_values(&max_duration, &max_processes, NULL);

    /* Main part */
    proc = create_process(pid++, active, max_duration, QUEUE_QUANT); /* Creating new process */
    ++current_n;
    STL_Queue_push(qs, proc, sizeof(process));
    kill_process(proc);

    /* Main simulation loop */
    while (!check_if_empty(qs, NUM_OF_QS) || current_n < max_processes) {

        /* Updating time */
        ++current_quant;
        nanosleep(&pause_pamram, NULL);

        /* Drawing */
        draw_queues(qs);

        /* Generating new process */
        if (!(rand() % FREQ) && current_n <= max_processes) {
            proc = create_process(pid++, waiting, max_duration, QUEUE_QUANT);
            if (STL_Queue_empty(qs)) {
                proc->st = active;
                for (i = 0; i < NUM_OF_QS; ++i) {
                    process_l = qs + i;
                    for (iter = STL_List_begin(process_l); iter != STL_List_end(process_l); iter = iter->next) {
                        if (((process *) iter->value)->st == active) {
                            ((process *) iter->value)->st = waiting;
                            break;
                        }
                    }
                }
            }
            STL_Queue_push(qs, proc, sizeof(process));
            ++current_n;
            kill_process(proc);
        }

        if (check_if_empty(qs, NUM_OF_QS)) {
            continue;
        }

        /* Scheduling in round-robin fashion */
        for (i = 0; i < NUM_OF_QS; ++i) {
            if (!STL_Queue_empty(qs + i)) {
                round_robin(qs + i, &average);
                break;
            }
        }

        /* Updating queues */
        for (i = 0; i < NUM_OF_QS - 1; ++i) {
            process_l = qs + i;
            for (iter = STL_List_begin(process_l); iter != STL_List_end(process_l); iter = iter->next) {
                proc = iter->value;
                if (proc->this_q_time <= 0) {
                    proc->st = waiting;
                    proc->this_q_time = QUEUE_QUANT * (i + 2);
                    STL_Queue_push(qs + (i + 1), proc, sizeof(process));
                    STL_List_erase(process_l, iter);
                }
            }
        }
    }

    nanosleep(&pause_pamram, NULL);
    draw_queues(qs);

    /* Final output */
    print_finals(&average, max_processes, current_quant);
}

void round_robin(STL_Queue *process_q, process *average) {

    /* Initializing variables */
    auto STL_List *process_l = process_q;
    auto STL_List_node *iter;

    auto process *proc, tmp;

    /* Main part */

    /* Make sure we have one active process */
    ((process *) STL_Queue_front(process_q))->st = active;

    /* Quant time - updating processes */
    for (iter = STL_List_begin(process_l); iter != STL_List_end(process_l); iter = iter->next) {
        proc = iter->value;
        if (proc->st == active) {
            ++proc->in_system;
            --proc->duration;
            --proc->this_q_time;
        }

        ++proc->total_time;
        proc->awaiting = proc->total_time - proc->in_system;
        proc->reactivity = (double) (proc->duration + proc->in_system) / proc->total_time;
        proc->fine_relation = 1 / proc->reactivity;
    }

    /* Set new active process and remove finished ones */
    tmp = *((process *) STL_Queue_front(process_q));
    tmp.st = waiting;

    STL_Queue_pop(process_q);

    if (tmp.duration) {
        STL_Queue_push(process_q, &tmp, sizeof(process));
    } else {
        average->total_time += tmp.total_time;
        average->awaiting += tmp.awaiting;
        average->reactivity += tmp.reactivity;
        average->fine_relation += tmp.fine_relation;
    }

    if (STL_Queue_size(process_q)) {
        ((process *) STL_Queue_front(process_q))->st = active;
    }
}