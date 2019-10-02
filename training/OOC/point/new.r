#ifndef NEW_R
#define NEW_R

/* Header inclusion */
#include <stdio.h>
#include <stdarg.h>

/* Private class' declaration */
struct Class {
	size_t size;
	void * (*ctor)(void *self, va_list *app);
	void * (*dtor)(void *self);
	void (*draw)(const void *self);
};

#endif