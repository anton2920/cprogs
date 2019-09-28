#include "libs.h"



struct word *find_word(const char *text, const char *wrd) {

    /* Initializing variables */
    auto size_t i;
    auto char *tmp;
    auto struct word *ret = NULL;

    /* Main part */
    if ((tmp = strstr(text, wrd)) != NULL) {
        ret = word_alloc(1);
        ret->beg = tmp;
        for (; isnotwordend(*tmp) ; ++tmp)
            ;
        ret->length = tmp - ret->beg;
    }

    /* Returning value */
    return ret;
}

struct word *word_alloc(size_t n) {

    /* Returning value */
    return (struct word *) malloc(n * sizeof(struct word));
}