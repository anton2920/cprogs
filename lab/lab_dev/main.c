#include <pthread.h>

#include "libs/libs.h"

pthread_mutex_t the_mutex;
pthread_cond_t condc, condp; /* Used for signaling */

/* Delays..., choruses, and reverberations :) */
struct timespec prod_sleep_time = {0, 0.5e7};
struct timespec cons_sleep_time = {0, 1e7};

/* Buffer */
typedef int item;
static int buffer;

/* Percentages */
int overall_percentage = 0;
int prod_percentage, cons_percentage;

void *producer(void *ptr) {

    /* Main part */
    for (; overall_percentage < RUN_SIZE; ++overall_percentage) {
        pthread_mutex_lock(&the_mutex); /* Get exclusive access to buffer */
        while (buffer == MAX_SIZE) {
            pthread_cond_wait(&condp, &the_mutex);
        }
        for (prod_percentage = 0; prod_percentage < 100; ++prod_percentage)
            nanosleep(&prod_sleep_time, NULL);   /* Simulating very hard work */
        ++buffer; /* Put item in buffer */
        pthread_cond_signal(&condc); /* Wake up consumer */
        pthread_mutex_unlock(&the_mutex); /* Release access to buffer */

        /* To make an interleaving sequence */
        /* nanosleep(&prod_sleep_time, NULL); */
    }

    /* Exitting */
    pthread_exit(0);
}

void *consumer(void *ptr) {

    /* Main part */
    for (; overall_percentage < RUN_SIZE; ++overall_percentage) {
        pthread_mutex_lock(&the_mutex); /* Get exclusive access to buffer */
        while (!buffer) {
            pthread_cond_wait(&condc, &the_mutex);
        }
        for (cons_percentage = 0; cons_percentage < 100; ++cons_percentage)
            nanosleep(&cons_sleep_time, NULL);   /* Simulating very hard work */
        --buffer; /* Remove item from buffer */
        pthread_cond_signal(&condp); /* Wake up produccer */
        pthread_mutex_unlock(&the_mutex); /* Release access to buffer */

        /* To make an interleaving sequence */
        /* nanosleep(&cons_sleep_time, NULL); */
    }

    /* Exitting */
    pthread_exit(0);
}

main() {

    /* Initializing variables */
    auto pthread_t pro, con, draw;

    auto struct thread_status st = {&buffer, &prod_percentage,
                                    &cons_percentage, &overall_percentage};

    pthread_mutex_init(&the_mutex, 0);

    pthread_cond_init(&condc, 0);
    pthread_cond_init(&condp, 0);

    pthread_create(&draw, 0, draw_system, &st);
    pthread_create(&con, 0, consumer, 0);
    pthread_create(&pro, 0, producer, 0);

    /* Main part */
    pthread_join(pro, 0);
    pthread_join(con, 0);
    pthread_join(draw, 0);

    pthread_cond_destroy(&condc);
    pthread_cond_destroy(&condp);

    pthread_mutex_destroy(&the_mutex);
}