#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <time.h>
#include <STL/STL_Queue.h>
#include <STL/STL_List.h>
#include <stdlib.h>
#include <float.h>

#include "process.h"
#include "visual.h"

static const time_t dt = 4;  /* Number of sub-quants in quant */
static const int FREQ = 5; /* Probability of process occasion = 1 / FREQ */
static struct timespec pause_pamram = {0, 1e8}; /* Program delay {sec, nsec} */

enum aldorithm {
    halflife,
    roundrobin
};

void prt_ln(void) {

    /* Final output */
    printf(" ------------------------------------------------------------\n");
}

void get_values(enum aldorithm alg, time_t *max_duration, unsigned int *max_processes, double *p) {

    /* I/O flow */
    do {
        printf("| Type max process duration: ");
        scanf("%lu", max_duration);
    } while (*max_duration < 1);

    do {
        printf("| Type max number of processes: ");
        scanf("%u", max_processes);
    } while (*max_processes < 1);

    if (alg == halflife) {
        do {
            printf("| Type initial priority: ");
            scanf("%lf", p);
        } while (*p < 0.0);
    }

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

void hlrr() {

    /* Initializing variables */
    auto unsigned int pid = 0, max_processes;
    auto time_t max_duration;
    auto double initial_priority;

    auto process *proc, average = {};

    auto unsigned int current_n = 0;
    auto time_t current_quant = 0;

    auto STL_Vector process_v;
    STL_Vector_init(&process_v, sizeof(process));

    register size_t i;

    auto double min_p;
    auto size_t min_pos;

    /* Main part */
    get_values(halflife, &max_duration, &max_processes, &initial_priority);

    proc = create_process(pid++, active, max_duration, initial_priority);
    STL_Vector_push_back(&process_v, proc);
    ++current_n;
    kill_process(proc);

    draw_hlrr(&process_v);

    while (!STL_Vector_empty(&process_v) || current_n < max_processes) {
        ++current_quant;
        nanosleep(&pause_pamram, NULL);

        /* Generating new processes */
        if (!(rand() % FREQ) && current_n <= max_processes) {
            proc = create_process(pid++, waiting, max_duration, initial_priority);
            STL_Vector_push_back(&process_v, proc);
            ++current_n;
            kill_process(proc);
        }

        if (STL_Vector_empty(&process_v)) {
            draw_hlrr(&process_v);
            continue;
        }

        /* Quant time - updating processes */
        for (i = 0lu; i < STL_Vector_size(&process_v); ++i) {
            proc = STL_Vector_at(&process_v, i);
            if (proc->st == active) {
                ++proc->in_system;
                --proc->duration;

                proc->u += dt;
            }

            ++proc->total_time;
            proc->awaiting = proc->total_time - proc->in_system;
            proc->reactivity = (double) (proc->duration + proc->in_system) / proc->total_time;
            proc->fine_relation = 1 / proc->reactivity;

            proc->u /= 2;
            proc->p += proc->u / 2;
        }

        /* Remove finished processes */
        for (i = 0lu; i < STL_Vector_size(&process_v); ++i) {
            proc = STL_Vector_at(&process_v, i);
            if (!proc->duration) {
                average.total_time += proc->total_time;
                average.awaiting += proc->awaiting;
                average.reactivity += proc->reactivity;
                average.fine_relation += proc->fine_relation;

                STL_Vector_erase(&process_v, proc);
                --i;
            }
        }

        if (STL_Vector_empty(&process_v)) {
            draw_hlrr(&process_v);
            continue;
        }

        min_p = DBL_MAX;
        min_pos = 0;
        for (i = 0lu; i < STL_Vector_size(&process_v); ++i) {
            proc = STL_Vector_at(&process_v, i);
            proc->st = waiting;
            if (proc->p < min_p) {
                min_p = proc->p;
                min_pos = i;
            }
        }

        /* Set new active process */
        proc = STL_Vector_at(&process_v, min_pos);
        proc->st = active;

        draw_hlrr(&process_v);
    }

    /* Final output */
    print_finals(&average, max_processes, current_quant);
}

void round_robin() {

    /* Initializing variables */
    auto unsigned int pid = 0, max_processes;
    auto time_t max_duration;

    auto process *proc, tmp, average = {};

    auto unsigned int current_n = 0;
    auto time_t current_quant = 0;

    auto STL_Queue process_q;
    auto STL_List *process_l = &process_q;
    auto STL_List_node *iter;
    STL_Queue_init(&process_q);

    /* Main part */
    get_values(roundrobin, &max_duration, &max_processes, NULL);

    proc = create_process(pid++, active, max_duration, 0.0); /* No need in priority */
    ++current_n;
    STL_Queue_push(&process_q, proc, sizeof(process));
    kill_process(proc);

    while (!STL_Queue_empty(&process_q) || current_n < max_processes) {
        ++current_quant;
        nanosleep(&pause_pamram, NULL);

        /* Generating new processes */
        if (!(rand() % FREQ) && current_n <= max_processes) {
            proc = create_process(pid++, waiting, max_duration, 0.0);
            if (STL_Queue_empty(&process_q)) {
                proc->st = active;
            }
            STL_Queue_push(&process_q, proc, sizeof(process));
            ++current_n;
            kill_process(proc);
        }

        /* Drawing */
        draw_rr(&process_q);

        if (STL_Queue_empty(&process_q)) {
            continue;
        }

        /* Quant time - updating processes */
        for (iter = STL_List_begin(process_l); iter != STL_List_end(process_l); iter = iter->next) {
            proc = iter->value;
            if (proc->st == active) {
                ++proc->in_system;
                --proc->duration;
            }

            ++proc->total_time;
            proc->awaiting = proc->total_time - proc->in_system;
            proc->reactivity = (double) (proc->duration + proc->in_system) / proc->total_time;
            proc->fine_relation = 1 / proc->reactivity;
        }

        /* Set new active process and remove finished ones */
        tmp = *((process *) STL_Queue_front(&process_q));
        tmp.st = waiting;

        STL_Queue_pop(&process_q);

        if (tmp.duration) {
            STL_Queue_push(&process_q, &tmp, sizeof(process));
        } else {
            average.total_time = tmp.total_time;
            average.awaiting = tmp.awaiting;
            average.reactivity = tmp.reactivity;
            average.fine_relation = tmp.fine_relation;
        }

        if (STL_Queue_size(&process_q)) {
            ((process *) STL_Queue_front(&process_q))->st = active;
        }
    }

    nanosleep(&pause_pamram, NULL);
    draw_rr(&process_q);

    /* Final output */
    print_finals(&average, max_processes, current_quant);
}
