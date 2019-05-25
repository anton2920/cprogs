#include "STL.h"

__bool Stack_init(Stack *st, size_t nbytes) {

    /* Main part */
    if ((st->bp = malloc(nbytes)) != NULL) {
        st->size = nbytes;
        st->bp += st->size;
        st->sp = st->bp;
        return __true;
    } else {
        return __false;
    }
}

void Stack_delete(Stack *st) {

    /* Main part */
    st->bp += st->size;
    free(st->bp);
}

__bool Stack_cpy(Stack *a, Stack *b) {

    /* Initializing variables */
    auto void *abp = a->bp - b->size, *bbp = b->bp - b->size;

    /* VarCheck */
    if (a->size < b->size) {
        return __false;
    }

    /* Main part */
    COPY(abp, bbp, b->size);

    /* Returning value */
    return __true;

}

__bool Stack_ncpy(Stack *a, Stack *b, size_t nbytes) {

    /* Initializing variables */
    auto void *abp = a->bp - nbytes, *bbp = b->bp - nbytes;

    /* VarCheck */
    if (a->size < b->size) {
        return __false;
    }

    /* Main part */
    COPY(abp, bbp, nbytes);

    /* Returning value */
    return __true;

}

__bool Stack_resize(Stack *st, size_t new_size) {

    /* Initializing variables */
    auto Stack new_st;

    /* Main part */
    if (Stack_init(&new_st, new_size) == __false) {
        return __false;
    }

    Stack_cpy(&new_st, st);
    Stack_delete(st);

    /* Returning value */
    return __true;
}

__bool Stack_pushw(Stack *st, const void *word) {

    /* VarCheck */
    if (st->sp - SIZE_OF_WORD < st->bp - st->size) {
        return __false;
    }

    /* Main part */
    COPY((void *) st->sp, word, SIZE_OF_WORD);
    st->sp -= SIZE_OF_WORD;

    /* Returning value */
    return __true;
}

__bool Stack_pushl(Stack *st, const void *long_word) {

    /* VarCheck */
    if (st->sp - SIZE_OF_LONG < st->bp - st->size) {
        return __false;
    }

    /* Main part */
    COPY((void *) st->sp, long_word, SIZE_OF_LONG);
    st->sp -= SIZE_OF_LONG;

    /* Returning value */
    return __true;
}

__bool Stack_pushq(Stack *st, const void *quad_word) {

    /* VarCheck */
    if (st->sp - SIZE_OF_QUAD < st->bp - st->size) {
        return __false;
    }

    /* Main part */
    COPY((void *) st->sp, quad_word, SIZE_OF_QUAD);
    st->sp -= SIZE_OF_QUAD;

    /* Returning value */
    return __true;
}

__bool Stack_push_nbytes(Stack *st, const void *elem, size_t nbytes) {

    /* VarCheck */
    if (st->sp - nbytes < st->bp - st->size) {
        return __false;
    }

    /* Main part */
    COPY((void *) st->sp, elem, nbytes);
    st->sp -= SIZE_OF_QUAD;

    /* Returning value */
    return __true;
}

void *Stack_popw(Stack *st) {
    
    /* VarCheck */
    if (st->sp + SIZE_OF_WORD > st->bp) {
        return NULL;
    }

    /* Main part */
    st->sp += SIZE_OF_WORD;

    /* Returning value */
    return st->sp;
}

void *Stack_popl(Stack *st) {

    /* VarCheck */
    if (st->sp + SIZE_OF_LONG > st->bp) {
        return NULL;
    }

    /* Main part */
    st->sp += SIZE_OF_LONG;

    /* Returning value */
    return st->sp;
}

void *Stack_popq(Stack *st) {

    /* VarCheck */
    if (st->sp + SIZE_OF_QUAD > st->bp) {
        return NULL;
    }

    /* Main part */
    st->sp += SIZE_OF_QUAD;

    /* Returning value */
    return st->sp;
}

void *Stack_pop_nbytes(Stack *st, size_t nbytes) {

    /* VarCheck */
    if (st->sp + nbytes > st->bp) {
        return NULL;
    }

    /* Main part */
    st->sp += nbytes;

    /* Returning value */
    return st->sp;
}