#include <stdio.h>
#include <assert.h>

#include "Set.h"
#include "new.h"

#if !defined MANY || MANY < 1
	#define MANY (10)
#endif

static int heap[MANY] = {};

void *new(const void *type, ...) {

	/* Initializing variables */
	auto int *p;

	/* Main part */
	for (p = heap + 1; p < heap + MANY; ++p) {
		if (! *p) {
			break;
		}
	}
	assert(p < heap + MANY);
	*p = MANY;

	/* Returning value */
	return (void *) p;
}

void delete(void *_item) {

	/* Initializing variables */
	auto int *item = _item;

	/* Main part */
	if (item != NULL) {
		assert(item > heap && item < heap + MANY);
		*item = 0;
	}
}

void *add(void *_set, const void *_element) {

	/* Initializing variables */
	auto int *set = _set;
	auto const int *element = _element;

	/* Main part */
	assert(set > heap && set < heap + MANY);
	assert(*set == MANY);
	assert(element > heap && element < heap + MANY);

	if (*element == MANY) {
		*(int *)element = set - heap;
	} else {
		assert(*element == set - heap);
	}

	/* Retutning value */
	return (void *) element;
}

void *find(const void *_set, const void *_element) {

	/* Initializing variables */
	auto const int *set = _set;
	auto const int *element = _element;

	/* Main part */
	assert(set > heap && set < heap + MANY);
	assert(*set == MANY);
	assert(element > heap && element < heap + MANY);
	assert(*element);

	return *element == set - heap ? (void *) element : 0;
}

int contains(const void *_set, const void *_element) {

	/* Returning value */
	return find(_set, _element) != 0;
}

void *drop(void *_set, const void *_element) {

	/* Initializing variables */
	auto int *element = find(_set, _element);

	/* Main part */
	if (element) {
		*element = MANY;
	}

	/* Returning value */
	return element;
}

int differ(const void *a, const void *b) {

	/* Returning value */
	return a != b;
}


/* Definitions */
const void *Set;
const void *Object;