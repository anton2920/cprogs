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
#define SIZE_OF_WORD (sizeof(word))
#define SIZE_OF_LONG (sizeof(lword))
#define SIZE_OF_QUAD (sizeof(qword))
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
typedef enum {
    __false = FALSE,
    __true = TRUE
} __bool;

/* LIFO stack data type */
typedef struct _stack {
    void *bp;
    void *sp;
    size_t size;
} Stack;

typedef short word;
typedef int dword;
typedef int lword;
typedef long qword;

/* Function declarations */

/* STL_Stack */
__bool Stack_init(Stack *, size_t); /* Creates a stack of declared size using malloc() [not a POSIX-standard function]. Returns __true, if everything is fine */
void Stack_delete(Stack *); /* Deletes a stack */
__bool Stack_cpy(Stack *, Stack *); /* Copies the right stack to the left one. The left stack size must be greater or equals to size of the right one, otherwise function will return __false */
__bool Stack_ncpy(Stack *, Stack *, size_t); /* Acts like function above, but copies only first bytes of the right stack */
__bool Stack_resize(Stack *, size_t); /* Securely resizes stack according to new declared size. Returns __true, if everything is fine */
__bool Stack_pushw(Stack *, const void *word); /* Pushes a word to stack */
__bool Stack_pushl(Stack *, const void *long_word); /* Pushes a longword to stack */
__bool Stack_pushq(Stack *, const void *quad_word); /* Pushes a quadword to stack */
__bool Stack_push_nbytes(Stack *, const void *, size_t); /* Pushes a variable sized word to stack */
void *Stack_popw(Stack *); /* Pops a word from a stack */
void *Stack_popl(Stack *); /* Pops a longword from a stack */
void *Stack_popq(Stack *); /* Pops a quadword from a stack */
void *Stack_pop_nbytes(Stack *, size_t); /* Pops a variable sized word form a stack */
size_t Stack_get_size(Stack *); /* Returns difference between sp and bp */

#endif