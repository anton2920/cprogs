#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "libs.h"

enum buf_consts {
    BUFSIZE = 1024
};

size_t get_curr_mem(void) {

    /* Initializing variables */
    FILE *fp = fopen("/proc/meminfo", "r");
    char buf[BUFSIZE];
    size_t i;

    /* Main part */
    fgets(buf, BUFSIZE, fp);
    fgets(buf, BUFSIZE, fp);

    for (i = 0; !isdigit(buf[i]); ++i)
        ;

    return atoi(buf + i);
}