#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "libs.h"

#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

static char off_ch  = ' ';
static char on_ch   = '=';
static char son_ch  = '>';
static char *box    = "[] ";
static char job[]   = "| Job: [                                                  ] |\n";
static char line[]  = " - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n";
static char prod[]  = "| Producing... [                         ]   Complete: %3d%% |\n";
static char cons[]  = "| Consuming... [                         ]   Complete: %3d%% |\n";
static char buf[]   = "| Buffer: ";

void *draw_system(void *_st) {

    /* Initializing variables */
    auto int i, count;
    auto struct thread_status *st = (struct thread_status *) _st;
    auto char *actual_buf = (char *) malloc(3 * MAX_SIZE);

    /* Main part */
    system("clear");
    for ( ; *st->overall_percentage < RUN_SIZE ;) {
        gotoxy(0, 0);
        printf("%s", line);

        /* Job line */
        count = *st->overall_percentage * 50 / RUN_SIZE;
        for (i = 0; i < 50; ++i) {
            if (i < count) {
                *(job + 8 + i) = son_ch;
                if (i) {
                    *(job + 8 + i - 1) = on_ch;
                }
            } else {
                *(job + 8 + i) = off_ch;
            }
        }
        printf("%s%s", job, line);

        /* Producer */
        count = *st->prod_percentage * 25 / 100;
        for (i = 0; i < 25; ++i) {
            if (i < count) {
                *(prod + 16 + i) = son_ch;
                if (i) {
                    *(prod + 16 + i - 1) = on_ch;
                }
            } else {
                *(prod + 16 + i) = off_ch;
            }
        }
        printf(prod, *st->prod_percentage);

        /* Consumer */
        count = *st->cons_percentage * 25 / 100;
        for (i = 0; i < 25; ++i) {
            if (i < count) {
                *(cons + 16 + i) = son_ch;
                if (i) {
                    *(cons + 16 + i - 1) = on_ch;
                }
            } else {
                *(cons + 16 + i) = off_ch;
            }
        }
        printf(cons, *st->cons_percentage);
        printf("%s", line);

        /* Buffer */
        strcpy(actual_buf, "");
        for (i = 0; i < *st->buffer; ++i) {
            strcat(actual_buf, box);
        }
        for (i = 0; i < 10 + 3 * MAX_SIZE; ++i) {
            printf(" ");
        }
        printf("\r%s%s\n%s", buf, actual_buf, line);
    }

    free(actual_buf);

    pthread_exit(0);
}