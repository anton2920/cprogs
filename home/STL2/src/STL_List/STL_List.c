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

#include <stdlib.h>
#include <string.h>

#include "STL_List.h"

static void STL_List_check_pointers(STL_List *l) {
    if (l->bp != NULL && l->lp == NULL) {
        l->lp = l->bp;
    } else if (l->lp != NULL && l->bp == NULL) {
        l->bp = l->lp;
    }
}

int STL_List_init(STL_List *l) {

    /* Main part */
    if (l == NULL) {
        return STL_List_null_reference_error;
    }

    if ((l->bp = (STL_List_node *) malloc(sizeof(STL_List_node))) == NULL) {
        return STL_List_memory_error;
    }

    l->lp = l->bp;
    l->bp->next = l->bp->prev = l->bp->value = NULL;
    l->size = 0;

    /* Returning value */
    return STL_List_OK;
    
}

void STL_List_delete(STL_List *l) {

    /* Main part */
    if (l == NULL) {
        return;
    }

    STL_List_clear(l);

    free(l->bp);
}

void STL_List_clear(STL_List *l) {

    /* Main part */
    if (l == NULL) {
        return;
    }

    while (l->size) {
        STL_List_pop_back(l);
    }
}

int STL_List_insert_pos(STL_List *l, const void *elem, size_t size, size_t pos) {

    /* Initializing variables */
    register size_t i;
    auto STL_List_node *iter;

    /* Main part */
    if (l == NULL || elem == NULL) {
        return STL_List_null_reference_error;
    }

    if (pos > l->size || pos < 0) {
        return STL_List_index_error;
    }

    if (pos > l->size / 2) {
        for (iter = STL_List_end(l), i = l->size; iter->prev != NULL && i > pos; iter = iter->prev, --i)
            ;
    } else {
        for (iter = STL_List_begin(l), i = 0; iter->next != NULL && i < pos; iter = iter->next, ++i)
            ;
    }

    /* Returning value */
    return STL_List_insert(l, elem, size, iter);
}

int STL_List_insert(STL_List *l, const void *elem, size_t size, STL_List_node *pos) {

    /* Initializing variables */
    auto STL_List_node *new_element;

    /* Main part */
    if (l == NULL || elem == NULL) {
        return STL_List_null_reference_error;
    }

    /* Inserting element */
    if ((new_element = (STL_List_node *) calloc(1, sizeof(STL_List_node))) == NULL) {
        return STL_List_memory_error;
    }
    if ((new_element->value = malloc(size)) == NULL) {
        return STL_List_memory_error;
    }

    memcpy(new_element->value, elem, size);
    new_element->size = size;

    new_element->next = pos;
    new_element->prev = pos->prev;

    if (pos->prev != NULL) {
        pos->prev->next = new_element;
    }
    pos->prev = new_element;

    /* Managing list */
    if (new_element->prev == NULL) {
        l->bp = new_element;
    } else if (new_element->next == NULL) {
        l->lp = new_element;
    }
    if (l->bp > l->lp) {
        l->lp = l->bp;
    }
    ++l->size;

    STL_List_check_pointers(l);

    /* Returning value */
    return STL_List_OK;
}

int STL_List_push_back(STL_List *l, const void *elem, size_t size) {

    /* Initializing variables */
    auto STL_List_node *new_element;

    /* Main part */
    if (l == NULL || elem == NULL) {
        return STL_List_null_reference_error;
    }

    if ((new_element = (STL_List_node *) calloc(1, sizeof(STL_List_node))) == NULL) {
        return STL_List_memory_error;
    }
    if ((new_element->value = malloc(size)) == NULL) {
        return STL_List_memory_error;
    }

    memcpy(new_element->value, elem, size);
    new_element->size = size;

    new_element->next = NULL;
    new_element->prev = l->lp;

    l->lp = new_element;

    ++l->size;

    STL_List_check_pointers(l);

    /* Returning value */
    return STL_List_OK;
}

int STL_List_push_front(STL_List *l, const void *elem, size_t size) {

    /* Returning value */
    return STL_List_insert(l, elem, size, l->bp);
}

STL_List_node *STL_List_erase_pos(STL_List *l, size_t pos) {

    /* Initializing variables */
    register size_t i;
    auto STL_List_node *iter, *ret;

    /* Main part */
    if (l == NULL) {
        return NULL;
    }

    if (pos > l->size / 2) {
        for (iter = STL_List_end(l), i = l->size; iter->prev != NULL && i >= pos; iter = iter->prev, --i)
            ;
    } else {
        for (iter = STL_List_begin(l), i = 0; iter->next != NULL && i <= pos; iter = iter->next, ++i)
            ;
    }

    /* Returning value */
    return STL_List_erase(l, iter);
}

STL_List_node *STL_List_erase(STL_List *l, STL_List_node *pos) {

    /* Initializing variables */
    auto STL_List_node *ret;

    /* Main part */
    if (l == NULL || pos == NULL) {
        return NULL;
    }

    if (pos->prev != NULL) {
        pos->prev = pos->next;
    } else {
        l->bp = pos->next;
    }
    if (pos->next != NULL) {
        pos->next->prev = pos->prev;
    } else {
        l->lp = pos->prev;
    }

    free(pos->value);
    if (pos->next == NULL) {
        ret = STL_List_end(l);
    } else {
        ret = pos->next;
    }
    free(pos);

    --l->size;

    STL_List_check_pointers(l);

    /* Returning value */
    return ret;
}

STL_List_node *STL_List_pop_back(STL_List *l) {

    /* Returning value */
    return STL_List_erase(l, l->lp);
}

STL_List_node *STL_List_pop_front(STL_List *l) {

    /* Returning value */
    return STL_List_erase(l, l->bp);
}

int STL_List_empty(STL_List *l) {

    /* Returning value */
    return (l->size) ? not_empty : empty;
}

size_t STL_List_size(STL_List *l) {

    /* Main part */
    if (l == NULL) {
        return 0;
    }

    /* Returning value */
    return l->size;
}

STL_List_node *STL_List_begin(STL_List *l) {

    /* Returning value */
    return l->bp;
}

STL_List_node *STL_List_end(STL_List *l) {

    /* Returning value */
    return l->lp;
}

static void STL_List_sort_merge(STL_List_node **start1, STL_List_node **end1,
        STL_List_node **start2, STL_List_node **end2, int (*cmp)(const void *, const void *))
{

    /* Initializing variables */
    auto STL_List_node *temp = NULL;

    /* Main part */
    if ((cmp((*start1)->value, (*start2)->value)) == 1) {
        STL_List_swap_nodes(*start1, *start2);
        STL_List_swap_nodes(*end1, *end2);
    }

    auto STL_List_node *astart = *start1, *aend = *end1;
    auto STL_List_node *bstart = *start2, *bend = *end2;
    auto STL_List_node *bendnext = bend->next;

    while (astart != aend && bstart != bend) {
        if (cmp(astart->next->value, bstart->value) == 1) {
            temp = bstart->next;
            bstart->next = astart->next;
            astart->next = bstart;
            bstart = temp;
        }
        astart = astart->next;
    }

    if (astart == aend) {
        astart->next = bstart;
    } else {
        *end2 = *end1;
    }
}

void STL_List_sort(STL_List *l, int (*cmp)(const void *, const void *)) {

    /* Initializing variables */
    auto STL_List_node *start1 = NULL, *end1 = NULL;
    auto STL_List_node *start2 = NULL, *end2 = NULL;
    auto STL_List_node *prevend = NULL;
    auto size_t len = STL_List_size(l), gap, counter;
    auto int isFirstIter;
    auto STL_List_node *temp;

    /* Main part */
    if (l == NULL || cmp == NULL || STL_List_begin(l) == NULL) {
        return;
    }

    for (gap = 1; gap < len; gap >>= 1) {
        start1 = STL_List_begin(l);

        while (start1) {
            isFirstIter = 0;
            if (start1 == STL_List_begin(l)) {
                isFirstIter = 1;
            }

            counter = gap;
            end1 = start1;
            while (--counter && end1->next) {
                end1 = end1->next;
            }

            start2 = end1->next;
            if (start2 == NULL) {
                break;
            }

            counter = gap;
            end2 = start2;
            while (--counter && end2->next) {
                end2 = end2->next;
            }

            temp = end2->next;
            STL_List_sort_merge(&start1, &end1, &start2, &end2, cmp);

            if (isFirstIter) {
                l->bp = start1;
            } else {
                prevend->next = start1;
            }

            prevend = end2;
            start1 = temp;
        }
        prevend->next = start1;
    }
}

void STL_List_swap_nodes(STL_List_node *a, STL_List_node *b) {

    /* Initializing variables */
    auto STL_List_node tmp;

    /* Main part */
    tmp.value = b->value;
    tmp.size = b->size;

    b->value = a->value;
    b->size = a->size;

    a->value = tmp.value;
    a->size = tmp.size;
}

void STL_List_swap(STL_List *this, STL_List *other) {

    /* Initializing variables */
    auto STL_List tmp;

    /* Main part */
    tmp.bp = other->bp;
    tmp.lp = other->lp;
    tmp.size = other->size;

    other->bp = this->bp;
    other->lp = this->lp;
    other->size = this->size;

    this->bp = tmp.bp;
    this->lp = tmp.lp;
    this->size = tmp.size;
}

size_t STL_List_size_node(STL_List_node *l) {

    /* Returning value */
    return l->size;
}