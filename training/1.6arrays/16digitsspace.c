#include <stdio.h>

/* Counts digits and other stuff */
main() {
	
	/* Initializing variables */
	int c, slashes = 0, stuff = 0, i; 

	/* Array */
	int digits[10];
	for (i = 0; i < 10; ++i) {
		digits[i] = 0;
	}

	/* Main part */
	while ((c = getchar()) != EOF) { 
		if (c >= '0' && c <= '9') { 
			++digits[c - '0'];
		} else if (c == '\n' || c == ' ' || c == '\t') {
			++slashes;
		} else {
			++stuff;
		}
	}

	/* Output */
	printf("Digits:");
	for (i = 0; i < 10; ++i) {
		printf("%3d", digits[i]);	
	}
	printf("\nSlashes: %3d", slashes);
	printf("\nStuff: %3d\n", stuff);
}
