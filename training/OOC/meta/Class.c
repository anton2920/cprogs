#include <stdio.h>
#include <assert.h>
#include <stdarg.h>

#include "Class.h"
#include "Object.h"
#include "Object.r"

static void *Class_ctor(void * _self, va_list *app) {

	/* Initializing variables */
	auto struct Class *self = _self;

	/* Main part */
	self->name = va_arg(*app, char *);
	self->super = va_arg(*app, struct Class *);
	self->size = va_arg(*app, size_t);

	assert(self->super);
}

static void *Class_dtor(void *_self) {

	/* Initializing variables */
	auto struct Class *self = _self;

	/* I/O flow */
	fprintf(stderr, "%s: cannot destroy class\n", self->name);

	/* Returning value */
	return NULL;
}

const void *super(const void *_self) {

	/* Initializing variables */
	auto const struct Class *self = _self;

	/* Main part */
	assert(self != NULL && self->super != NULL);

	/* Returning value */
	return self->super;
}