#include <stdio.h>

/* Additional tasks (letter «e») */
main() {

	/* Initializing variables */
	float a, b, c;


	/* I/O flow */
	printf("Type a: ");
	scanf("%f", &a);

	/* Four operations --> a ^ 3 & a ^ 10 */
	c = a * a; /* ^ 2 */
	b = c * a; /* ^ 3 */
	a = c * b; /* ^ 5 */
	c = a * a; /* ^ 10 */
	printf("a ^ 3 = %6.3f\na ^ 10 = %6.3f\n", b, c); /* Output */
}