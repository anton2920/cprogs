#include <stdio.h>
#include <assert.h>

#include "Object.h"
#include "Object.r"
 
static void *Object_ctor(void *self, va_list *app) {

	/* Returning value */
	return self;
}

static void *Object_dtor(void *self) {

	/* Returning value */
	return self;
}

static int Object_differ(const void *self, const void *b) {

	/* Returning value */
	return self != b;
}

static int Object_puto(const void *_self, FILE *fp) {

	/* Initializing variables */
	auto const struct Class *class = classOf(_self);

	return fprintf(fp, "%s at %p\n", class->name, _self);
}

const void *classOf(const void *_self) {

	/* Initializing variables */
	auto const struct Object *self = _self;

	/* Main part */
	assert(self != NULL && self->class != NULL);

	/* Returning value */
	return self->class;
}

size_t sizeOf(const void *_self) {

	/* Initializing variables */
	auto const struct Class *class = classOf(_self);

	/* Returning value */
	return class->size;
}