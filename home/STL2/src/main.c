#include "STL.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printList(STL_List *, FILE *);
int num_cmp(const void *, const void *);

main() {

    /* Initializing variables */
    auto STL_Queue a;
    auto int rand_val, i;

    /* Main part */
    STL_Queue_init(&a);
    srand(time(NULL) / 2);
    for (i = 0; i < 10; ++i) {
        rand_val = rand() % 10;
        STL_Queue_push(&a, &i, sizeof(int));
    }

    printList(&a, stdout);

    STL_List_delete(&a);

    /* Returning value */
    return 0;
}

void printList(STL_List *l, FILE *stream) {

    /* Initializing variables */
    int *elem;

    /* Main part */
    for (; STL_Queue_size(l); ) {
        elem = STL_Queue_back(l);
        fprintf(stream, "%d ", *elem);
        STL_Queue_pop(l);
    }


    fprintf(stream, "\n");
}

int num_cmp(const void *_this, const void *_other) {

    /* Initializing variables */
    auto const int *this = _this, *other = _other;

    /* Returning value */
    return (*this > *other) ? 1 : (*this < *other) ? -1 : 0;
}