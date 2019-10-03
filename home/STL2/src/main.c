#include "STL.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printList(STL_List *, FILE *);

main() {

    /* Initializing variables */
    auto STL_List a;
    auto STL_List_node *iter;
    auto int rand_val, i;

    /* Main part */
    STL_List_init(&a);
    srand(time(NULL) / 2);
    for (i = 0; i < 10; ++i) {
        rand_val = rand() % 10;
        STL_List_insert_pos(&a, &rand_val, sizeof(int), i);
    }

    printList(&a, stdout);

    /* Returning value */
    return 0;
}

void printList(STL_List *l, FILE *stream) {

    /* Initializing variables */
    auto STL_List_node *iter;
    auto int *value;

    /* Main part */
    for (iter = STL_List_begin(l); iter < STL_List_end(l); iter = iter->next) {
        value = (int *) iter->value;
        fprintf(stream, "%d ", *value);
    }

    fprintf(stream, "\n");
}