#include <stdio.h>

main() {
	
	/* Initializing variables */
	struct {
		int a : 1;
		int b : 1;
		int c : 1;
	} flags;

	struct {
		int d;
		int e;
		int f;
	} flags2;

	printf("%lu, %lu\n", sizeof(flags), sizeof(flags2));
}
