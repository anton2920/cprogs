#include <stdio.h>

/* Function declarations */
int y(int x);
int t(int x);

/* y(x) for different x'es */
main() {

	/* Initializing variables */
	int x;

	/* Main part */
	for (x = 3; x <= 30; x += 3) {
		printf("y(%d) = %d\n", x, y(x));
	}
}

int y(int x) {
	return (t(x) * t(x) * t(x)) + (3 * t(x) * t(x)) + 1;
}

int t(int x) {
	return 2 - x;
}