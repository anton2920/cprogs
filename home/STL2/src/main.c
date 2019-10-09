#include "STL.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printList(STL_List *, FILE *);
int num_cmp(const void *, const void *);

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
        STL_List_push_back(&a, &rand_val, sizeof(int));
    }

    printList(&a, stdout);
    mergeNatural(&a, num_cmp);
    printList(&a, stdout);

    STL_List_delete(&a);

    /* Returning value */
    return 0;
}

void printList(STL_List *l, FILE *stream) {

    /* Initializing variables */
    auto STL_List_node *iter;
    auto int *value;

    /* Main part */
    for (iter = STL_List_begin(l); iter != NULL; iter = iter->next) {
        value = (int *) iter->value;
        fprintf(stream, "%d ", *value);
    }

    fprintf(stream, "\n");
}

int num_cmp(const void *_this, const void *_other) {

    /* Initializing variables */
    auto const int *this = _this, *other = _other;

    /* Returning value */
    return (*this > *other) ? 1 : (*this < *other) ? -1 : 0;
}