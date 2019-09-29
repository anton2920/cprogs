#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#include "new.r"
#include "new.h"

/* Functions declarations */
void *new(const void *_class, ...) {

	/* Initializing variables */
	auto const struct Class *class = _class;
	auto void *p = calloc(1, class->size);

	/* Main part */
	assert(p);
	*(const struct Class **) p = class;

	if (class->ctor) {
		va_list ap;

		va_start(ap, _class);
		p = class->ctor(p, &ap);
		va_end(ap);
	}

	/* Returning value */
	return p;
}

void delete(void *self) {

	/* Initializing variables */
	auto const struct Class **cp = self;

	/* Main part */
	if (self != NULL && *cp != NULL && (*cp)->dtor) {
		self = (*cp)->dtor(self);
	}

	free(self);
}

void *clone(const void *self) {

	/* Initializing variables */
	auto const struct Class * const *cp = self;

	/* Main part */
	assert(self != NULL && *cp != NULL && (*cp)->clone);

	/* Returning value */
	return (*cp)->clone(self);
}

int differ(const void *self, const void *b) {

	/* Initializing variables */
	auto const struct Class * const *cp = self;

	/* Main part */
	assert(self != NULL && *cp != NULL && (*cp)->differ);

	/* Returning value */
	return (*cp)->differ(self, b); 
}

size_t sizeOf(const void *self) {

	/* Initializing variables */
	auto const struct Class * const *cp = self;

	/* Main part */
	assert(self != NULL && *cp != NULL);

	/* Returning value */
	return (*cp)->size;
}