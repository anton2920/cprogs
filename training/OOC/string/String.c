#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

#include "String.h"
#include "new.h"
#include "new.r"

struct String {
	const void *class;
	char *text;
};

static void *String_ctor(void *_self, va_list *app) {

	/* Initializing variables */
	auto struct String *self = _self;
	auto const char *text = va_arg(*app, const char *);

	/* Main part */
	self->text = malloc(strlen(text) + 1);
	assert(self->text != NULL);
	strcpy(self->text, text);

	/* Returning value */
	return (void *) self;
}

static void *String_dtor(void *_self) {

	/* Initializing variables */
	auto struct String *self = _self;

	/* Main part */
	free(self->text);
	self->text = NULL;

	/* Returning value */
	return self;
}

static void *String_clone(const void *_self) {

	/* Initializing variables */
	auto const struct String *self = _self;

	/* Returning value */
	return new(String, self->text);
}

static int String_differ(const void *_self, const void *_b) {

	/* Initializing variables */
	auto const struct String *self = _self;
	auto const struct String *b = _b;

	/* Main part */
	if (self == b) {
		return 0;
	}
	if (b == NULL || b->class != String) {
		return 1;
	}

	/* Returning value */
	return strcmp(self->text, b->text);
}

static const struct Class _String = {
	sizeof(struct String),
	String_ctor,
	String_dtor,
	String_clone,
	String_differ
};

const void *String = &_String;