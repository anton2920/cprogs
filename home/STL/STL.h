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
#include "config.h"

/* Including standard headers */
#if (HAVE_STDIO_H == 1)
    #include <stdio.h>
#endif
#if (HAVE_STDLIB_H == 1)
    #include <stdlib.h>
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

/* Unprotected macros for pop'ing */
#define STACK_POP_SHORT(st) (*((short *) Stack_popw(st)))
#define STACK_POP_LONG(st) (*((int *) Stack_popl(st)))
#define STACK_POP_FLOAT(st) (*((float *) Stack_popl(st)))
#define STACK_POP_QUAD(st) (*((long *) Stack_popq(st)))
#define STACK_POP_DOUBLE(st) (*((double *) Stack_popq(st)))

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

/* STL_List section */
typedef struct _list_node {
    struct _list *next;
    void *value;
} list_node;

/* Single-linked list data type */
typedef struct _list {
    list_node *bp;
    list_node *lp;
    size_t size;
} List;

typedef enum _stpt {
    head,
    tail
} stpt;

__bool List_init(List *);
void List_detele(List *);
__bool List_add_element(List *, const void *, size_t nbytes, stpt pt, size_t offset);


#endif