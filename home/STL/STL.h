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

#ifndef STL_LIBRARY_H
#define STL_LIBRARY_H

/* Include config.h */
#include "STL_Config.h"

/* Including standard headers */
#if (HAVE_STDIO_H == 1)
    #include <stdio.h>
#endif
#if (HAVE_STDLIB_H == 1)
    #include <stdlib.h>
#endif
#if (HAVE_MALLOC_H == 1)
    #include <malloc.h>
#endif

/* Macros */
#ifndef SIZE_OF_WORD
    #define SIZE_OF_WORD (sizeof(word))
#endif
#ifndef SIZE_OF_LONG
    #define SIZE_OF_LONG (sizeof(lword))
#endif
#ifndef SIZE_OF_QUAD
    #define SIZE_OF_QUAD (sizeof(qword))
#endif
#ifndef TRUE
    #define TRUE (1)
#endif
#ifndef FALSE
    #define FALSE (0)
#endif
#ifndef LIST_INDEX_ERROR
    #define LIST_INDEX_ERROR (-1)
#endif
#ifndef SWAP
    #define SWAP(a, b, size)                \
        do {                                \
            int __size = (size);            \
            char *__a = (a), *__b = (b);    \
            do {                            \
                char __tmp = *__a;          \
                *__a++ = *__b;              \
                *__b++ = __tmp;             \
            } while (--__size > 0);         \
        } while (0)
#endif
#ifndef COPY
    #define COPY(a, b, size)                \
        do {                                \
          int __size = (size);              \
          char *__a = (a);                  \
          const char *__b = (b);            \
          do {                              \
              *__a++ = *__b++;              \
          } while (--__size > 0);           \
        } while (0)
#endif

/* AT&T assembly styled macros */
#define movb(__src, __dest) (COPY((void *) __dest, (const void *) __src, 1))
#define movw(__src, __dest) (COPY((void *) __dest, (const void *) __src, SIZE_OF_WORD))
#define movl(__src, __dest) (COPY((void *) __dest, (const void *) __src, SIZE_OF_LONG))
#define movq(__src, __dest) (COPY((void *) __dest, (const void *) __src, SIZE_OF_QUAD))

/* New data types */
#ifndef __BOOL_TYPE
    #define __BOOL_TYPE
    typedef enum {
        __false = FALSE,
        __true = TRUE
    } __bool;
#endif

typedef short word;
typedef int dword;
typedef int lword;
typedef long qword;

/* Function declarations */

/* STL_Stack section */

/* LIFO stack data type */
typedef struct _stack {
    void *bp;
    void *sp;
    size_t size;
} Stack;

__bool Stack_init(Stack *, size_t); /* Creates a stack of declared size using malloc() [not a POSIX-standard function]. Returns __true, if everything is fine */
void Stack_delete(Stack *); /* Deletes a stack */
__bool Stack_cpy(Stack *, Stack *); /* Copies the right stack to the left one. The left stack size must be greater or equals to size of the right one, otherwise function will return __false */
__bool Stack_ncpy(Stack *, Stack *, size_t); /* Acts like function above, but copies only first bytes of the right stack */
__bool Stack_resize(Stack *, size_t); /* Safely resizes stack according to new declared size. Returns __true, if everything is fine */
__bool Stack_pushw(Stack *, const void *word); /* Pushes a word to stack */
__bool Stack_pushl(Stack *, const void *long_word); /* Pushes a longword to stack */
__bool Stack_pushq(Stack *, const void *quad_word); /* Pushes a quadword to stack */
__bool Stack_push_nbytes(Stack *, const void *, size_t); /* Pushes a variable sized word to stack */
void *Stack_popw(Stack *); /* Pops a word from a stack */
void *Stack_popl(Stack *); /* Pops a longword from a stack */
void *Stack_popq(Stack *); /* Pops a quadword from a stack */
void *Stack_pop_nbytes(Stack *, size_t); /* Pops a variable sized word form a stack */
size_t Stack_get_size(Stack *); /* Returns difference between sp and bp */

/* Unprotected macros for pop'ing */
#define STACK_POPW(st) (*((word *) Stack_popw(st)))
#define STACK_POPL(st) (*((lword *) Stack_popl(st)))
#define STACK_POPQ(st) (*((qword *) Stack_popq(st)))
#define STACK_POP_FLOAT(st) (*((float *) Stack_popl(st)))
#define STACK_POP_DOUBLE(st) (*((double *) Stack_popq(st)))

/* STL_List section */
typedef struct _list_node {
    struct _list_node *next;
    void *value;
} list_node;

/* Single-linked list data type. First element's value is not used. *bp should be changed! */
typedef struct _list {
    list_node *bp;
    list_node *lp;
    size_t size;
} List;

/* Offset's base for adding and removing elements */
typedef enum _stpt {
    head,
    tail
} stpt;

__bool List_init(List *); /* Creates a single-linked list. Returns __true, if everything is OK */
void List_delete(List *); /* Deletes a single-linked list */
__bool List_add_element(List *, const void *elem, size_t nbytes, stpt pt, size_t offset); /* Adds an element of specific size to a specific place, defined by starting point and the offset from it*/
__bool List_delete_element(List *, stpt pt, size_t offset); /* Deletes a specific element, defined by starting point and the offset from it */
list_node *List_get_element(List *, stpt pt, size_t offset); /* Returns a full list node, defined by starting point and the offset from it */
void *List_get_element_value(List *, stpt pt, size_t offset); /* Returns the value of a specific node, defined by starting point and the offset from it */
int List_get_element_offset(List *, list_node *, stpt pt); /* Returns the offset of specific element from declared starting point */
__bool List_swap_elements(list_node *, list_node *); /* Swaps two values of specific elements */
__bool List_cpy(List *__dest, List *__src); /* Creates an exact copy of a list */
__bool List_ncpy(List *__dest, List *__src, size_t n); /* Creates an exact copy of first n elements of a list */


/* LIFO Stack based on STL_List */
__bool List_Stack_push_nbytes(List *, const void *, size_t); /* Pushes nbytes value in the list, acting like a stack */
__bool List_Stack_pushw(List *, const void *); /* Pushes word in a list, acting like the stack */
__bool List_Stack_pushl(List *, const void *); /* Pushes long word in the list, acting like a stack */
__bool List_Stack_pushq(List *, const void *); /* Pushes quad word in the list, acting like a stack */
void *List_Stack_pop(List *); /* Pops element from the list, acting like a stack */

/* Secure macros for popping values from the list, acting like a stack*/
#define LIST_STACK_POPW(st, __word)                             \
    do {                                                        \
        void *temp = List_Stack_pop((st));                      \
        if (temp != NULL) {                                     \
            (__word) = *((word *) temp);                        \
            free(temp);                                         \
        }                                                       \
    } while(0)

#define LIST_STACK_POPL(st, __lword)                            \
    do {                                                        \
        void *temp = List_Stack_pop((st));                      \
        if (temp != NULL) {                                     \
            (__lword) = *((lword *) temp);                      \
            free(temp);                                         \
        }                                                       \
    } while(0)

#define LIST_STACK_POPQ(st, __qword)                            \
    do {                                                        \
        void *temp = List_Stack_pop((st));                      \
        if (temp != NULL) {                                     \
            (__qword) = *((qword *) temp);                      \
            free(temp);                                         \
        }                                                       \
    } while(0)

#define LIST_STACK_POP_FLOAT(st, __float)                       \
    do {                                                        \
        void *temp = List_Stack_pop((st));                      \
        if (temp != NULL) {                                     \
            (__float) = *((float *) temp);                      \
            free(temp);                                         \
        }                                                       \
    } while(0)

#define LIST_STACK_POP_DOUBLE(st, __double)                     \
    do {                                                        \
        void *temp = List_Stack_pop((st));                      \
        if (temp != NULL) {                                     \
            (__double) = *((double *) temp);                    \
            free(temp);                                         \
        }                                                       \
    } while(0)


/* FIFO Queue based on STL_List */
__bool List_Queue_push_nbytes(List *, const void *, size_t); /* Pushes nbytes in the list, acting like a queue */
__bool List_Queue_pushw(List *, const void *); /* Pushes word in the list, acting like a queue */
__bool List_Queue_pushl(List *, const void *); /* Pushes word in the list, acting like a queue */
__bool List_Queue_pushq(List *, const void *); /* Pushes word in the list, acting like a queue */
void *List_Queue_pop(List *); /* Pops value from the list, acting like a queue */

/* Secure macros for popping values from the list, acting like a queue */
#define LIST_QUEUE_POPW(st, __word)                             \
    do {                                                        \
        void *temp = List_Queue_pop((st));                      \
        if (temp != NULL) {                                     \
            (__word) = *((word *) temp);                        \
            free(temp);                                         \
        }                                                       \
    } while(0)

#define LIST_QUEUE_POPL(st, __lword)                            \
    do {                                                        \
        void *temp = List_Queue_pop((st));                      \
        if (temp != NULL) {                                     \
            (__lword) = *((lword *) temp);                      \
            free(temp);                                         \
        }                                                       \
    } while(0)

#define LIST_QUEUE_POPQ(st, __qword)                            \
    do {                                                        \
        void *temp = List_Queue_pop((st));                      \
        if (temp != NULL) {                                     \
            (__qword) = *((qword *) temp);                      \
            free(temp);                                         \
        }                                                       \
    } while(0)

#define LIST_STACK_POP_FLOAT(st, __float)                       \
    do {                                                        \
        void *temp = List_Stack_pop((st));                      \
        if (temp != NULL) {                                     \
            (__float) = *((float *) temp);                      \
            free(temp);                                         \
        }                                                       \
    } while(0)

#define LIST_QUEUE_POP_DOUBLE(st, __double)                     \
    do {                                                        \
        void *temp = List_Queue_pop((st));                      \
        if (temp != NULL) {                                     \
            (__double) = *((double *) temp);                    \
            free(temp);                                         \
        }                                                       \
    } while(0)


/* Circular buffer based on STL_List */
__bool List_Ring_init(List *); /* Creates a ring based on single-linked list. Returns __true, if everything is OK */
__bool List_Ring_delete(List *); /* Deletes a ring */
__bool List_Ring_add_element(List *, const void *elem, size_t nbytes, stpt pt, size_t offset); /* Adds an element of specific size to a specific place, defined by starting point and the offset from it*/
__bool List_Ring_delete_element(List *, stpt pt, size_t offset); /* Deletes a specific element, defined by starting point and the offset from it */
list_node *List_Ring_get_element(List *, stpt pt, size_t offset); /* Returns a full list node, defined by starting point and the offset from it */
void *List_Ring_get_element_value(List *, stpt pt, size_t offset); /* Returns the value of a specific node, defined by starting point and the offset from it */
int List_Ring_get_element_offset(List *, list_node *, stpt pt); /* Returns the offset of specific element from declared starting point */
__bool List_Ring_swap_elements(list_node *, list_node *); /* Swaps two values of specific elements */
__bool List_Ring_cpy(List *__dest, List *__src); /* Creates an exact copy of a ring */
__bool List_Ring_ncpy(List *__dest, List *__src, size_t n); /* Creates an exact copy of first n elements of a ring */

#endif