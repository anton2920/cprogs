#ifndef OBJECT_R
#define OBJECT_R

/* Header inclusion */
#include <stdio.h>
#include <stdarg.h>

/* Object representation */
struct Object {
	const struct Class *class;
};

/* Class representation */
struct Class {
	const struct Object _;
	const char *name;
	const struct Class *super;
	size_t size;
	void * (*ctor)(void *self, va_list *app);
	void * (*dtor)(void *self);
	int (*differ)(const void *self, const void *b);
	int (*puto)(const void *self, FILE *fp);
};

#endif