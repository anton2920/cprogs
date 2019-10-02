#ifndef OBJECT_H
#define OBJECT_H

/* Datatype declaration */
extern const void *Object;

/* Functions declarations */
void *new(const void *class, ...);
void delete(void *self);

int differ(const void *self, const void *b);
int puto(const void *self, FILE *fp);

extern const void *Class;

const void *classOf(const void *_self);
size_t sizeOf(const void *_self);

#endif