#include "String.h"
#include "new.h"

main() {

	/* Initializing variables */
	auto *a = new(String, "a"), *aa = clone(a);
	auto *b = new(String, "b");

	/* I/O flow */
	printf("sizeOf(a) == %lu\n", sizeOf(a));

	/* Main part */
	if (differ(a, b)) {
		puts("OK!");
	}

	if (differ(a, aa)) {
		puts("Differ?");
	}

	if (a == aa) {
		puts("Clone?");
	}

	delete(a), delete(aa), delete(b);
}