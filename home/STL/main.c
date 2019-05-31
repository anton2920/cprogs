#include "STL.h"

int to_bin(int);

main() {

    /* Initializing variables */
    auto List a;
    auto int i, offset;
    auto list_node *iter;

    /* Main part */
    List_Ring_init(&a);

    for (i = 1; i <= 41; ++i) {
        List_Ring_add_element(&a, &i, sizeof(int), tail, 0);
    }

    for (iter = a.bp->next; a.size > 2; ) {
        iter = iter->next;
        iter = iter->next;
        offset = List_Ring_get_element_offset(&a, iter, head);
        if (offset != LIST_INDEX_ERROR) {
            List_Ring_delete_element(&a, head, offset);
        } else {
            return -1;
        }
        iter = List_Ring_get_element(&a, head, offset);
    }

    printf("Safe places: ");
    for (iter = a.bp->next, i = 0; i < a.size; ++i, iter = iter->next) {
        printf("%d ", *((int *) iter->value));
    }

    List_Ring_delete(&a);

    /* Final output */
    printf("\n");

    /* Returning value */
    return 0;
}