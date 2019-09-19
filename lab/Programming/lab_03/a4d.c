#include <stdio.h>

/* Additional tasks (letter «d») */
main() {

	/* Initializing variables */
	float a, b, c, d, e;


	/* I/O flow */
	printf("Type a: ");
	scanf("%f", &a);

	/* Five operations --> a ^ 15 */
	b = a * a; /* ^ 2 */
    c = b * a; /* ^ 3 */
    d = c * c; /* ^ 6 */
    e = d * d; /* ^ 12 */
    a = c * e; /* ^ 15 */


	/* Final printing */
	printf("a ^ 15 = %6.3f\n", a);
}