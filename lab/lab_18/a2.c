#include <stdio.h>

#define N (15)

main() {

	/* Initializing variables */
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21};
	int *p = a;

	/* Final output */
	printf("a[0] = %d, a[1 + %d] = %d, a[1 + (2 * %d %% 21)] = %d\n", *p, N, *(p + 1 + N), N, *(p + 1 + (2 * N % 21)));
}