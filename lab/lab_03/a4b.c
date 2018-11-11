#include <stdio.h>

/* Additional tasks (letter «b») */
main() {

	/* Initializing variables */
	float a, b, c, d;


	/* I/O flow */
	printf("Type a: ");
	scanf("%f", &a);

	/* Five operations --> a ^ 13 */
	b = a * a; /* ^ 2 */
    c = b * b; /* ^ 4 */
    d = c * c; /* ^ 8 */
    c = d * c; /* ^ 12 */
    a = a * c; /* ^ 13 */

	/* Final printing */
	printf("a ^ 13 = %6.3f\n", a);
}