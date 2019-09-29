#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Set.h"
#include "Object.h"

struct Set {
	unsigned int count;
};

struct Object {
	unsigned int count;
	struct Set *in;
};

static const size_t _Set = sizeof(struct Set);
static const size_t _Object = sizeof(struct Object);

const void *Set = &_Set;
const void *Object = &_Object;

void *new(const void *type, ...) {

	/* Initializing variables */
	auto const size_t size = *(const size_t *) type;
	auto void *p = calloc(1, size);

	/* Main part */
	assert(p != NULL);

	/* Returning value */
	return p;
}

void delete(void *_item) {

	/* Main part */
	free(_item);
}

void *add(void *_set, const void *_element) {

	/* Initializing variables */
	auto struct Set *set = _set;
	auto struct Object *element = (void *) _element;

	/* Main part */
	assert(set);
	assert(element);

	if (!element->in) {
		element->in = set;
	} else {
		assert(element->in == set);
	}

	++element->count;
	++set->count;

	/* Returning value */
	return element;
}

void *find(const void *_set, const void *_element) {

	/* Initializing variables */
	auto const struct Object *element = _element;

	/* Main part */
	assert(_set);
	assert(element);

	/* Returning value */
	return element->in == _set ? (void *) element : 0;
}

int contains(const void *_set, const void *_element) {

	/* Returning value */
	return find(_set, _element) != 0;
}

void *drop(void *_set, const void *_element) {

	/* Initializing variables */
	auto struct Set *set = _set;
	auto struct Object *element = find(set, _element);

	if (element) {
		if (!(--element->count)) {
			element->in = 0;
		}
		--set->count;
	}

	/* Returning value */
	return element;
}

unsigned int count(const void *_set) {

	/* Initializing variables */
	auto const struct Set *set = _set;

	assert(set);

	/* Returning value */
	return set->count;
}

int differ(const void *a, const void *b) {

	/* Returning value */
	return a != b;
}