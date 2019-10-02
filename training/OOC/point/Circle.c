#include <stdio.h>
#include <stdarg.h>

#include "Circle.h"
#include "Circle.r"
#include "new.h"
#include "new.r"

static void *Circle_ctor(void *_self, va_list *app) {

	/* Initializing variables */
	auto struct Circle *self = ((const struct Class *) Point)->ctor(_self, app);

	/* Main part */
	self->rad = va_arg(*app, int);

	/* Returning value */
	return self;
}

static void Circle_draw(const void *_self) {

	/* Initializing variables */
	auto const struct Circle *self = _self;

	/* Main part */
	printf("circle ar %d, %d rad %d\n", x(self), y(self), self->rad);
}

static const struct Class _Circle = {
	sizeof(struct Circle),
	Circle_ctor,
	NULL,
	Circle_draw
};

const void *Circle = &_Circle;