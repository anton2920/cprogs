#include <stdio.h>
#include <stdarg.h>

#include "Point.h"
#include "Point.r"
#include "new.r"
#include "new.h"

/* Functions declarations */
static void *Point_ctor(void *_self, va_list *app) {

	/* Initializing variables */
	auto struct Point *self = _self;

	/* Main part */
	self->x = va_arg(*app, int);
	self->y = va_arg(*app, int);

	/* Returning value */
	return self;
}

static void Point_draw(const void *_self) {

	/* Initializing variables */
	auto const struct Point *self = _self;

	/* Main part */
	printf("\".\" at %d, %d\n", self->x, self->y);
}

static const struct Class _Point = {
	sizeof(struct Point),
	Point_ctor,
	NULL,
	Point_draw
};

const void *Point = &_Point;

void move(void *_self, int dx, int dy) {

	/* Initialiizng variables */
	auto struct Point *self = _self;

	/* Main part */
	self->x += dx;
	self->y += dy;
}