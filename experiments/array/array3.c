#include <stdio.h>

#define NAME (10)

main() {
	
	/* Initializing variables */
	int a, b[NAME];

	/* I/O flow */
	printf("Addr of a var = %d, addr of array = %d, addr of array + 1 = %d\n", &a, b, b + 1);
}
