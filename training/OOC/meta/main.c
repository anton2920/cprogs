#include <stdio.h>

main() {

	/* Initializing variables */
	auto void *o = new(Object);
	auto const void *Any = new(Class, "Any", Object, sizeOf(o), differ, Any_differ, 0);
	auto void *a = new(Any);

	/* I/O flow */
	puto(Any, stdout);
	puto(o, stdout);
	puto(a, stdout);

	/* Main part */
	if (differ(o, o) == differ(a, a)) {
		puts("OK!");
	}

	if (differ(o, a) != differ(a, o)) {
		puts("Not commutative!");
	}

	delete(o);
	delete(a);
	delete(Any); /* Error */
}