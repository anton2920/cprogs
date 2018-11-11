#include <stdio.h>
#include "shoulders.h"

main() {

	/* Initializing variables */
	char *num;
	int count, i, len;

	/* I/O flow */
	printf("Type number: ");
	len = getint(num);

	/* Main part */
	for (i = 2, count = 0; i <= len; ++i) {
		if ((*(num + i) - '0') % 2 == 0) {
			++count;
		}
	}

	/* Final output */
	printf("Answer: %d\n", count);
}