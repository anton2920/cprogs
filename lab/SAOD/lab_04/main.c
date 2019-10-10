#include <stdio.h>

#include "/home/anton/C/home/STL2/src/STL.h"

enum buf_consts {
    BUFSIZE = 1024
};

size_t get_curr_mem(void);

main() {

    /* Initializing variables */
    size_t sz;

    /* Main part */
    sz = get_curr_mem();
    printf("%lu\n", sz);

    sz -= sizeof(STL_Queue);
    sz /= sizeof(STL_Queue_node);
    sz /= sizeof(double);

    printf("%lu\n", sz);

}

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