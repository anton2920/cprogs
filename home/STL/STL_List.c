#include "STL.h"

__bool List_init(List *l) {

    /* Main part */
    if ((l->bp = (list_node *) malloc(sizeof(list_node))) == NULL) {
        return __false;
    }

    l->lp = l->bp;
    l->bp->next = l->bp->value = NULL;

    /* Returning value */
    return __true;
}

void List_delete(List *l) {

    /* Main part */

}