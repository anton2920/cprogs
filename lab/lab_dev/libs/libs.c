#include <stdio.h>
#include <string.h>

#include "libs.h"

char *insertAfter(char *text, size_t maxsize, char ch, size_t pos) {

    /* Initializing variables */
    auto char new_buf[maxsize];

    /* Main part */
    if (strlen(text) >= maxsize || pos >= maxsize || text == NULL || pos < 0) {
        return NULL;
    }

    memcpy(new_buf, text, maxsize); /* Back up original data */

    *(text + pos + 1) = ch;
    memcpy(text + pos + 2, new_buf + pos + 1, maxsize - pos);

    /* Returning value */
    return (text + pos + 1);
}

char *insertBefore(char *text, size_t maxsize, char ch, size_t pos) {

    /* Returning value */
    return insertAfter(text, maxsize, ch, pos - 1);
}

void replaceNAll(char *text, size_t n, char from, char to) {

    /* Initializing variables */
    register size_t i;

    /* Main part */
    for (i = 0; i < n; ++i) {
        if (*(text + i) == from) {
            *(text + i) = to;
        }
    }
}

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