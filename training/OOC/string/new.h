#ifndef NEW_H
#define NEW_H

/* Header inclusion */
#include <stdio.h>

/* Functions declarations */
void *new(const void *, ...);
void delete(void *);
void *clone(const void *self);
int differ(const void *self, const void *b);

size_t sizeOf(const void *self);

#endif