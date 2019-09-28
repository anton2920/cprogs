#ifndef LAB_DEV_LIBS_H
#define LAB_DEV_LIBS_H

/* Header inclusions */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Macro definitions */
#define isnotwordend(x) ((x) != ' ' && (x) != '\n' &&   \
    (x) != '.' && (x) != ',' && (x) != '?' && (x) != '!')

/* Type definitions */
struct word {
    char *beg;
    size_t length;
};

/* Functions declarations */
struct word *find_word(const char *, const char *);
struct word *word_alloc(size_t);

#endif
