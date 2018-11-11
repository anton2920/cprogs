#include <stdio.h>

main() {
	
	/* Initialising variables */
	int c;

	/* While loop. It copies char and put it back unless it's EOF (end-of-file) */
	while ((c = getchar()) != EOF) {
		putchar(c);
	}
	if (c == EOF) {
		printf("%d\n", c);
	}
}
