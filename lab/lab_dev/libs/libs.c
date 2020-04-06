#include <stdio.h>
#include <time.h>

const time_t quant_time = 1000;
time_t dt = quant_time / 4;

#include "libs.h"

void get_values(time_t *max_duration, unsigned int *max_processes) {

    /* I/O flow */
    printf("| Type max process duration: ");
    scanf("%lu", max_duration);

    printf("| Type max number of processes: ");
    scanf("%u", max_processes);
}

void hlrr() {

}

void round_robin() {

    /* Initializing variables */
    auto unsigned int pid = 0, max_processes;
    auto time_t max_duration;
}