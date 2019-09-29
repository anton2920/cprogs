#ifndef SET_H
#define SET_H

extern const void *Set;

void *add(void *, const void *);
void *find(const void *, const void *);
void *drop(void *, const void *);
int contains(const void *, const void *);

#endif