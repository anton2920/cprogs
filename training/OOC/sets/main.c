#include <stdio.h>

#include "new.h"
#include "Set.h"
#include "Object.h"

main() {

	/* Initializing variables */
	auto *s = new(Set);
	auto *a = add(s, new(Object));
	auto *b = add(s, new(Object));
	auto *c = new(Object);

	/* Main part */
	if (contains(s, a) && contains(s, b)) {
		puts("OK!");
	}
	if (contains(s, c)) {
		puts("Contains?");
	}
	if (differ(a, add(s, a))) {
		puts("Differ?");
	}
	if (contains(s, drop(s, a))) {
		puts("Drop?");
	}

	delete(drop(s, b));
	delete(drop(s, c));
}