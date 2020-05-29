#include <stdio.h>
#include <STL/STL_List.h>
#include <STL/STL_Algorithm.h>
#include <stdlib.h>

#include "visual.h"
#include "../process/process.h"
#include "../libs/libs.h"

static const char *bottom_header = "| PID | Time left | Total time | Lost time | Reactivity |   Fine   |\n";
static const char *horizontal_line =   " ----------------------------------------------------------------- \n";

static const char *active_clr = "\033[30m\033[102m";
static const char *default_clr = "\033[39m\033[49m";

static const unsigned int MAX_DRAW_SIZE = 13;

void draw_bottom(STL_Queue *qs);

int pidcmp(const void *_self, const void *_other) {

    /* Initializing variables */
    auto process *self = (process *) _self, *other = (process *) _other;

    /* Returning value */
    return ((self->pid > other->pid) ? 1 : (self->pid < other->pid) ? -1 : 0);
}

void draw_bottom(STL_Queue *qs) {

    /* This is dangerous and stupid */
    auto STL_List *process_l;
    auto STL_List_node *iter;
    /* This is dangerous and stupid */

    /* Copying list to vector instead of sorting list */
    auto STL_Vector process_v;
    auto process *piter;
    register size_t i;
    STL_Vector_init(&process_v, sizeof(process));
    /* This is more stupid */

    /* Main part */
    for (i = 0; i < NUM_OF_QS; ++i) {
        process_l = qs + i;
        for (iter = STL_List_begin(process_l); iter != STL_List_end(process_l); iter = iter->next) {
            STL_Vector_push_back(&process_v, iter->value);
        }
    }
    if (STL_Vector_empty(&process_v)) {
        printf("%s%s%s", horizontal_line, bottom_header, horizontal_line);
        return;
    }

    STL_quick_sort(STL_Vector_data(&process_v), STL_Vector_size(&process_v), sizeof(process), pidcmp);

    printf("%s%s%s", horizontal_line, bottom_header, horizontal_line);
    for (i = 0lu; i < STL_Vector_size(&process_v) && i < MAX_DRAW_SIZE; ++i) {
        piter = (process *) STL_Vector_at(&process_v, i);
        if (piter == NULL) {
            break;
        }
        if (piter->st == active) {
            printf("%s", active_clr);
        }
        printf("| %3u | %9lu | %10lu | %9lu | %10.4lf | %8.4lf |%s\n",
               piter->pid, piter->duration, piter->total_time, piter->awaiting, piter->reactivity, piter->fine_relation,
               default_clr);
        printf("%s", horizontal_line);
    }
}

void draw_queues(STL_Queue *qs) {

    /* Initializing variables */
    register int i;

    /* For queues traversal */
    auto STL_List *process_l;
    auto STL_List_node *iter;

    /* I/O flow */
    system("clear");
    printf("%s", horizontal_line);

    /* Main part */
    for (i = 0; i < NUM_OF_QS; ++i) {
        process_l = qs + i;
        printf("| Queue #%d: ", i);
        for (iter = STL_List_begin(process_l); iter != STL_List_end(process_l); iter = iter->next) {
            if (((process *) iter->value)->st == active) {
                printf("%s", active_clr);
            }
            printf("[ %2u ]%s", ((process *) iter->value)->pid, default_clr);
        }
        printf("\n");
        fflush(stdout);
    }

    draw_bottom(qs);
}