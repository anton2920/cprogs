#include <stdio.h>

main() {

	/* Initializing variables */
	int a = 134, *b = &a;

	/* I/O flow */
	printf("Value of variable «a» equals to %d\n", a);
	printf("Address of variable «a» equals to %d\n", &a);
	printf("Dereferenced value of «b» equals to %d\n", *b);
	printf("Value of pointer «b» equals to %d\n", b);
	printf("Address of «b» equals to %d\n", &b);
}