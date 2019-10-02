#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>

#include "Class.h"
#include "Object.h"
#include "Object.r"

static void *Class_ctor(void * _self, va_list *app) {

	/* Initializing variables */
	auto struct Class *self = _self;
	auto const size_t offset = offsetof(struct Class, ctor);

	/* Main part */
	self->name = va_arg(*app, char *);
	self->super = va_arg(*app, struct Class *);
	self->size = va_arg(*app, size_t);

	assert(self->super);

	memcpy((char *) self + offset, (char *) self->super + offset, sizeOf(self->super) - offset);

	{
		typedef void (*voidf)();
		voidf selector;
		va_list ap = *app;

		for (; (selector = va_arg(ap, voidf)); ) {
			voidf method = va_arg(ap, voidf);

			if (selector == (voidf) ctor) {
				*(voidf *) &self->ctor = method;
			} else if (selector == (voidf) dtor) {
				*(voidf *) &self->dtor = method
			} else if (selector == (voidf) differ) {
				*(voidf *) &self->differ = method;
			} else if (selector == (voidf) puto) {
				*(voidf *) &self->puto = method;
			}
		}

		return self;
	}
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