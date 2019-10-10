#include <stdio.h>

#include "libs/libs.h"
#include "/home/anton/C/home/STL2/src/STL.h"

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