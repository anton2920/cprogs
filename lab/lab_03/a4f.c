#include <stdio.h>

/* Additional tasks (letter «f») */
main() {

	/* Initializing variables */
	float a, b, c;


	/* I/O flow */
	printf("Type a: ");
	scanf("%f", &a);

	/* Five operations --> a ^ 4 & a ^ 20*/
	c = a * a; /* ^ 2 */
	c = c * c; /* ^ 4 */
	b = c * c; /* ^ 8 */
	c = a * b; /* ^ 3 */
	c = c * a; /* ^ 4 */
	printf("a ^ 4 = %6.3f\n", c, ); /* Output */
}