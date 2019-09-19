#include <stdio.h>

main() {

	/* Initializing variables */
	int x = 10, *p, i;

	/* Main part */
	p = &i;
	for (i = 1; i <= x; ++i) {
		printf("%d\n", *p);
	}
}