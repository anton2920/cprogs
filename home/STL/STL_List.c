/*
Standard Template Library for C — free shared library, that contains an attempt of recreation of libc++ STL
Copyright © Pavlovsky Anton, 2019

This file is part of STL.

STL is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

STL is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with STL. If not, see <https://www.gnu.org/licenses/>.
*/

#include "STL.h"

__bool List_init(List *l) {

    /* Main part */
    if ((l->bp = (list_node *) malloc(sizeof(list_node))) == NULL) {
        return __false;
    }

    l->lp = l->bp;
    l->bp->next = l->bp->value = NULL;
    l->size = 0;

    /* Returning value */
    return __true;
}

void List_delete(List *l) {

    /* Main part */
    while (l->bp->next != l->lp && l->bp != l->lp) {
        List_delete_element(l, tail, 0);
    }

    free(l->bp);
}

__bool List_add_element(List *l, const void *elem, size_t nbytes, stpt pt, size_t offset) {

    /* Initializing variables */
    register size_t i;
    auto list_node *iter = NULL, *new_elem = NULL;

    /* Main part */
    if (offset > l->size) {
        return __false;
    }

    if (pt == head) {
        for (i = 0, iter = l->bp; i < offset && iter->next != NULL; ++i, iter = (list_node *) iter->next)
            ;

    } else if (pt == tail && !offset) {
        iter = l->lp;
    } else {
        offset = l->size - offset;
        for (i = 0, iter = l->bp; i < offset && iter->next != NULL; ++i, iter = (list_node *) iter->next)
            ;
    }

    if ((new_elem = (list_node *) malloc(sizeof(list_node))) == NULL) {
        return __false;
    }
    new_elem->next = iter->next;
    iter->next = new_elem;
    if ((new_elem->value = malloc(nbytes)) == NULL) {
        return __false;
    }
    COPY(new_elem->value, elem, nbytes);

    if (new_elem->next == NULL) {
        l->lp = new_elem;
    }

    ++l->size;

    /* Returning value */
    return __true;
}

__bool List_delete_element(List *l, stpt pt, size_t offset) {

    /* Initializing variables */
    register size_t i;
    auto list_node *iter, *temp;

    /* Main part */
    if (pt == head && offset < l->size) {
        for (i = 0, iter = l->bp; i < offset && iter->next != NULL; ++i, iter = (list_node *) iter->next)
            ;
    } else if (pt == tail && (offset = l->size - offset - 1) < l->size) {
        for (i = 0, iter = l->bp; i < offset && iter->next != NULL; ++i, iter = (list_node *) iter->next)
            ;
    } else {
        return __false;
    }

    if (i != offset) {
        return __false;
    }

    temp = iter->next;
    free(temp->value);
    iter->next = temp->next;
    free(temp);
    if (iter->next == NULL) {
        l->lp = iter;
    }
    --l->size;

    /* Returning value */
    return __true;
}

list_node *List_get_element(List *l, stpt pt, size_t offset) {

    /* Initializing variables */
    register size_t i;
    auto list_node *iter;

    /* Main part */
    if (pt == head) {
        ++offset;
        for (i = 0, iter = l->bp; i < offset && iter->next != NULL; ++i, iter = iter->next)
            ;
    } else if (pt == tail && !offset) {
        iter = l->lp;
    } else {
        ++offset;
        offset = l->size - offset;
        for (i = 0, iter = l->bp; i < offset && iter->next != NULL; ++i, iter = iter->next)
            ;
    }

    /* Returning value */
    return iter;
}

void *List_get_element_value(List *l, stpt pt, size_t offset) {

    /* Initializing variables */
    auto list_node *temp = List_get_element(l, pt, offset);

    /* Returning value */
    return temp->value;
}

int List_get_element_offset(List *l, list_node *lnode, stpt pt) {

    /* Initializing variables */
    register size_t i;
    auto list_node *iter;

    /* Main part */
    for (i = 0, iter = l->bp->next; iter != lnode && iter != NULL; ++i, iter = iter->next)
        ;

    if (iter == NULL) {
        return LIST_INDEX_ERROR;
    }

    /* Returning value */
    return (pt == head) ? (i) : (l->size - i);
}

__bool List_swap_elements(list_node *lnode1, list_node *lnode2) {

    /* Initializing variables */
    auto void *t_v;

    /* Main part */
    if (lnode1 == lnode2) {
        return __true;
    } else {
        t_v = lnode1->value;
        lnode1->value = lnode2->value;
        lnode2->value = t_v;
    }

    /* Returning value */
    return __true;
}

__bool List_cpy(List *l1, List *l2) {

    /* Initializing variables */
    List_init(l1);
    auto list_node *iter;

    /* Main part */
    for (iter = l2->bp; iter != NULL; iter = iter->next) {
        if (List_add_element(l1, iter->value, malloc_usable_size(iter->value), tail, 0) == __false) {
            return __false;
        }
    }

    /* Returning value */
    return __true;
}

__bool List_ncpy(List *l1, List *l2, size_t n) {

    /* Initializing variables */
    register size_t i;
    auto list_node *iter;

    /* Main part */
    for (i = 0, iter = l2->bp; iter != NULL && i < n; ++i, iter = iter->next) {
        if (List_add_element(l1, iter->value, malloc_usable_size(iter->value), tail, 0) == __false) {
            return __false;
        }
    }

    /* Returning value */
    return __true;
}


/* LIFO Stack based on STL_List */
__bool List_Stack_push_nbytes(List *l, const void *elem, size_t nbytes) {

    /* Returning value */
    return List_add_element(l, elem, nbytes, tail, 0);
}

__bool List_Stack_pushw(List *l, const void *elem) {

    /* Returning value */
    return List_Stack_push_nbytes(l, elem, SIZE_OF_WORD);
}

__bool List_Stack_pushl(List *l, const void *elem) {

    /* Returning value */
    return List_Stack_push_nbytes(l, elem, SIZE_OF_LONG);
}

__bool List_Stack_pushq(List *l, const void *elem) {

    /* Returning value */
    return List_Stack_push_nbytes(l, elem, SIZE_OF_QUAD);
}

void *List_Stack_pop(List *l) {

    /* Initializing variables */
    auto void *temp, *temp2;
    auto size_t nbytes;

    /* Main part */
    if ((temp = List_get_element_value(l, tail, 0)) == NULL) {
        return NULL;
    }
    if ((temp2 = malloc((nbytes = malloc_usable_size(temp)))) == NULL) {
        return NULL;
    }
    COPY(temp2, temp, nbytes);
    List_delete_element(l, tail, 0);

    /* Returning value */
    return temp2;
}

/* FIFO Queue based on STL_List */
__bool List_Queue_push_nbytes(List *l, const void *elem, size_t nbytes) {

    /* Returning value */
    return List_add_element(l, elem, nbytes, head, 0);
}

__bool List_Queue_pushw(List *l, const void *elem) {

    /* Returning value */
    return List_Queue_push_nbytes(l, elem, SIZE_OF_WORD);
}

__bool List_Queue_pushl(List *l, const void *elem) {

    /* Returning value */
    return List_Queue_push_nbytes(l, elem, SIZE_OF_LONG);
}

__bool List_Queue_pushq(List *l, const void *elem) {

    /* Returning value */
    return List_Queue_push_nbytes(l, elem, SIZE_OF_QUAD);
}

void *List_Queue_pop(List *l) {

    /* Initializing variables */
    auto void *temp, *temp2;
    auto size_t nbytes;

    /* Main part */
    if ((temp = List_get_element_value(l, tail, 0)) == NULL) {
        return NULL;
    }
    if ((temp2 = malloc((nbytes = malloc_usable_size(temp)))) == NULL) {
        return NULL;
    }
    COPY(temp2, temp, nbytes);
    List_delete_element(l, tail, 0);

    /* Returning value */
    return temp2;
}

/* Circular buffer based on STL_List */
__bool List_Ring_link(List *r) {

    /* Main part */
    if (r->size) {
        r->lp->next = r->bp->next;
    } else {
        return __false;
    }

    /* Returning value */
    return __true;
}

__bool List_Ring_unlink(List *r) {

    /* Main part */
    if (r->size) {
        r->lp->next = NULL;
    } else {
        return __false;
    }

    /* Returning value */
    return __true;
}

__bool List_Ring_init(List *r) {

    /* Main part */
    return List_init(r);
}

__bool List_Ring_delete(List *r) {

    /* Initializing variables */
    auto __bool status;

    /* Main part */
    if ((status = List_Ring_unlink(r)) == __false) {
        return status;
    }
    List_delete(r);
    if ((status = List_Ring_link(r)) == __false) {
        return status;
    }

    /* Returning value */
    return __true;
}

__bool List_Ring_add_element(List *r, const void *elem, size_t nbytes, stpt pt, size_t offset) {

    /* Initializing variables */
    auto __bool status;

    /* Main part */
    List_Ring_unlink(r);
    if (offset >= r->size) {
        offset -= r->size;
    }
    if ((status = List_add_element(r, elem, nbytes, pt, offset)) == __false) {
        return status;
    }
    List_Ring_link(r);

    /* Returning value */
    return __true;
}

__bool List_Ring_delete_element(List *r, stpt pt, size_t offset) {

    /* Initializing variables */
    auto __bool status;

    /* Main part */
    List_Ring_unlink(r);
    if (offset >= r->size) {
        offset -= r->size;
    }
    if ((status = List_delete_element(r, pt, offset)) == __false) {
        return status;
    }
    List_Ring_link(r);

    /* Returning value */
    return __true;
}

list_node *List_Ring_get_element(List *r, stpt pt, size_t offset) {

    /* Initializing variables */
    auto __bool status;
    auto list_node *elem;

    /* Main part */
    if ((status = List_Ring_unlink(r)) == __false) {
        return NULL;
    }
    if (offset >= r->size) {
        offset -= r->size;
    }
    elem = List_get_element(r, pt, offset);
    if ((status = List_Ring_link(r)) == __false) {
        return NULL;
    }

    /* Returning value */
    return elem;
}

void *List_Ring_get_element_value(List *r, stpt pt, size_t offset) {

    /* Initializing variables */
    auto __bool status;
    auto void *val;

    /* Main part */
    if ((status = List_Ring_unlink(r)) == __false) {
        return NULL;
    }
    if (offset >= r->size) {
        offset -= r->size;
    }
    val = List_get_element_value(r, pt, offset);
    if ((status = List_Ring_link(r)) == __false) {
        return NULL;
    }

    /* Returning value */
    return val;
}

int List_Ring_get_element_offset(List *r, list_node *elem, stpt pt) {

    /* Initializing variables */
    auto int offs;

    /* Main part */
    if (List_Ring_unlink(r) == __false) {
        return LIST_INDEX_ERROR;
    }
    offs = List_get_element_offset(r, elem, pt);
    if (List_Ring_link(r) == __false) {
        return LIST_INDEX_ERROR;
    }

    /* Returning value */
    return offs;
}

__bool List_Ring_swap_elements(list_node *l1, list_node *l2) {

    /* Returning value */
    return List_swap_elements(l1, l2);
}

__bool List_Ring_cpy(List *l1, List *l2) {

    /* Initializing variables */
    auto __bool status;

    /* Main part */
    if ((status = List_Ring_unlink(l1)) == __false) {
        return status;
    }
    if ((status = List_Ring_unlink(l2)) == __false) {
        return status;
    }

    if ((status = List_cpy(l1, l2)) == __false) {
        return status;
    }

    if ((status = List_Ring_link(l1)) == __false) {
        return status;
    }
    if ((status = List_Ring_link(l2)) == __false) {
        return status;
    }

    /* Returning value */
    return __true;
}

__bool List_Ring_ncpy(List *l1, List *l2, size_t n) {

    /* Initializing variables */
    __bool status;

    /* Main part */
    if ((status = List_Ring_unlink(l1)) == __false) {
        return status;
    }
    if ((status = List_Ring_unlink(l2)) == __false) {
        return status;
    }

    if ((status = List_ncpy(l1, l2, n)) == __false) {
        return status;
    }

    if ((status = List_Ring_link(l1)) == __false) {
        return status;
    }
    if ((status = List_Ring_link(l2)) == __false) {
        return status;
    }

    /* Returning value */
    return __true;
}
