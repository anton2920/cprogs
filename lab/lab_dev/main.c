#include <stdio.h>
#include <stdlib.h>

#include "libs/libs.h"

main() {

    /* Initializing variables */
    auto int i;

    /* Creating empty heap */
    auto heap_t *h = (heap_t *) calloc(1, sizeof(heap_t));

    /* Inserting elements */
    insert(h, 3, "Clear drains");
    insert(h, 4, "Feed cat");
    insert(h, 5, "Make tea");
    insert(h, 1, "Solve RC tasks");
    insert(h, 2, "Tax return");

    for (i = 0; i < 5; i++) {
        printf("%s\n", delete_min(h));
    }
}