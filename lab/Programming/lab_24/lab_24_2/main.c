#include "source.h"

main() {

    /* Initializing variables */
    struct group_l array;

    /* I/O flow */
    if (read_stuff(&array) == true) {
        find_ar_mean(&array);
        find_lt3(&array);
        find_gs_mks(&array);

        delete_arr(&array);
    }
}