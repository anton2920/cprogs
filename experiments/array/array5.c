#include <stdio.h>

main() {
	
	/* Initializing variables */
	int i, a[] = { 1, 2, 3, 4, 5 }, max = 0;

	/* Main part */
	for (i = 1; i < 5; ++i) {
		if (*(a + i) > *(a + (i - 1)))
			max = *(a + i);
	}

	printf("Max = %d", max);

	exit(0);
}
