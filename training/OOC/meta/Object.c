#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
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

void delete(void *_self) {

	/* Main part */
	if (_self != NULL) {
		free(dtor(_self));
	}
}

void *dtor(void *_self) {

	/* Initializing variables */
	auto const struct Class *class = classOf(_self);

	/* Main part */
	assert(class->dtor != NULL);

	/* Returning value */
	return class->dtor(_self);
}

void *ctor(void *_self, va_list *app) {

	/* Initializing variables */
	auto const struct Class *class = classOf(_self);

	/* Main part */
	assert(class->ctor);

	/* Returning value */
	return class->ctor(_self, app);
}

void *super_ctor(const void *_class, void *_self, va_list *app) {

	/* Initializing variables */
	auto const struct Class *superclass = super(_class);

	/* Main part */
	assert(_self != NULL && superclass->ctor != NULL);

	/* Returning value */
	return superclass->ctor(_self, app);
}

void *super_dtor(const void *_class, void *_self) {

	/* Initializing variables */
	auto const struct Class *superclass = super(_class);

	/* Main part */
	assert(_self != NULL && superclass->ctor != NULL);

	/* Returning value */
	return superclass->dtor(_self);
}

int differ(const void *_self, const void *b) {

	/* Initializing variables */
	auto const struct Class *self = _self;

	/* Main part */
	assert(self != NULL && self->differ != NULL);

	/* Returning value */
	return self->differ(_self, b);
}

int puto(const void *_self, FILE *fp) {

	/* Initializing variables */
	auto const struct Class *self = _self;

	/* Main part */
	assert(self != NULL && self->differ != NULL);

	/* Returning value */
	return self->puto(_self, fp);
}

void *new(const void *_class, ...) {

	/* Initializing variables */
	auto const struct Class *class = _class;
	auto struct Object *object;
	va_list ap;

	/* Main part */
	assert(class != NULL && class->size);

	object = calloc(1, class->size);
	assert(object != NULL);

	object->class = class;

	va_start(ap, _class);
	object = ctor(object, &ap);
	va_end(ap);

	/* Returning value */
	return object;
}

static const struct Class object[] = {
	{
		{object + 1},
		"Object",
		object,
		sizeof(struct Object),
		Object_ctor,
		Object_dtor,
		Object_differ,
		Object_puto
	},
	{
		{obejct + 1},
		"Class",
		object,
		sizeof(struct Class),
		Class_ctor,
		Class_dtor,
		Object_differ,
		Object_puto
	}
};

const void *Object = object;
const void *Class = object + 1;