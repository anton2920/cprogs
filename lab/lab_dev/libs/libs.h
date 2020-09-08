#ifndef LAB_DEV_LIBS_H
#define LAB_DEV_LIBS_H

/* Header inclusion */
#include <stdio.h>
#include <stdlib.h>

/* Macros */
#define handle_error(msg)   \
    do {                    \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0);

/* New data types */

/* Functions' declarations */


#endif
