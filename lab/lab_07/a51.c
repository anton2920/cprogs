#include <stdio.h>

int phib(int n);

/* N-member of fibonacci sequence */
main() {

	/* Initializing variables */
	int n;

	/* I/O flow && VarCheck*/
	do {
		printf("Type N: ");
		scanf("%d", &n);
	} while (n <= 0);

	/* Final output */
	printf("The %d-member of fibonacci sequence: %d\n", n, phib(n));
}


int phib(int n) {
	if (n == 1 || n == 2) {
		return 1;
	} else {
		return phib(n - 1) + phib(n - 2);
	}
}