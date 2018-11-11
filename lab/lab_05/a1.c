#include <stdio.h>

/* Number comparison */
main() {

	/* Initializing variables */
	int a, b;

	/* I/O flow */
	printf("Type first number: ");
	scanf("%d", &a);
	printf("Type second number: ");
	scanf("%d", &b);

	/* Main part */
	if (a >= b) {
		printf("Answer: %d\n", a - b);
	} else {
		if (b != 0) {
			printf("Answer: %.1f\n", (a * 1.0) / (b * 1.0));
		}
	}
}
