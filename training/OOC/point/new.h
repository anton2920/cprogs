#ifndef NEW_H
#define NEW_H

/* Header inclusion */
#include <stdio.h>

/* Functions declarations */
void *new(const void *, ...);
void delete(void *);
void draw(const void *);

#endif