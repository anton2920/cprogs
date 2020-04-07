#include <stdio.h>
#include <STL/STL_List.h>
#include <STL/STL_Algorithm.h>
#include <stdlib.h>

#include "visual.h"
#include "process.h"

const char *hlrr_header = "| PID | Time left |  P[i]  |  U[i]  | Total time | Lost time | Reactivity |   Fine   |\n";
const char *hlrr_line =   " ------------------------------------------------------------------------------------ \n";

const char *rr_header = "| PID | Time left | Total time | Lost time | Reactivity |   Fine   |\n";
const char *rr_line =   " ------------------------------------------------------------------ \n";

const char *active_clr = "\033[30m\033[102m";
const char *default_clr = "\033[39m\033[49m";

int pidcmp(const void *_self, const void *_other) {

    /* Initializing variables */
    auto process *self = (process *) _self, *other = (process *) _other;

    /* Returning value */
    return ((self->pid > other->pid) ? 1 : (self->pid < other->pid) ? -1 : 0);
}

void draw_hlrr(STL_Vector *process_v) {

    /* Initializing variables */
    auto process *piter;
    register size_t i;

    /* Main part */
    system("clear");
    if (STL_Vector_empty(process_v)) {
        printf("%s%s%s", hlrr_line, hlrr_header, hlrr_line);
        return;
    }

    printf("%s%s%s", hlrr_line, hlrr_header, hlrr_line);
    for (i = 0lu; i < STL_Vector_size(process_v); ++i) {
        piter = (process *) STL_Vector_at(process_v, i);
        if (piter == NULL) {
            break;
        }
        if (piter->st == active) {
            printf("%s", active_clr);
        }
        printf("| %3u | %9lu | %6.3lf | %6.3lf | %10lu | %9lu | %10.4lf | %8.4lf |%s\n",
               piter->pid, piter->duration, piter->p, piter->u,
               piter->total_time, piter->awaiting, piter->reactivity, piter->fine_relation, default_clr);
        printf("%s", hlrr_line);
    }
}

void draw_rr(STL_Queue *process_q) {

    /* This is dangerous and stupid */
    auto STL_List *process_l = process_q;
    auto STL_List_node *iter;
    /* This is dangerous and stupid */

    /* Copying list to vector instead of sorting list */
    auto STL_Vector process_v;
    auto process *piter;
    register size_t i;
    STL_Vector_init(&process_v, sizeof(process));
    /* This is more stupid */

    /* Main part */
    system("clear");
    if (STL_List_empty(process_l)) {
        printf("%s%s%s", rr_line, rr_header, rr_line);
        return;
    }
    for (iter = STL_List_begin(process_l); iter != STL_List_end(process_l); iter = iter->next) {
        STL_Vector_push_back(&process_v, iter->value);
    }

    STL_quick_sort(process_v.data, STL_Vector_size(&process_v), sizeof(process), pidcmp);

    printf("%s%s%s", rr_line, rr_header, rr_line);
    for (i = 0lu; i < STL_Vector_size(&process_v); ++i) {
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
        printf("%s", rr_line);
    }
}