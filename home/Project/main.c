#include "headers/project.h"

main() {

    /* Initializing variables */
    int func;
    char a[NAME] = "{}", b[NAME] = "{}", c[NAME] = "{}", expr[NAME] = "";

    /* I/O flow */
	while (!strcmp(a, "{}") || !strcmp(b, "{}") || !strcmp(c, "{}")) {
    	if ((func = set_sets(a, b, c)) == 0) {
			break;
		} else if (func == 1) {
			lclear();
			return 0;
		} else {
			continue;
		}
	}
	printf("%d\n", func);
	printf("A = %s\n", a);
	printf("B = %s\n", b);
	printf("C = %s\n", c);

	if ((func = set_expr(expr)) == 1) {
		lclear();
		return 0;
	}

	lclear();
}

void lclear(void) {

	system(COMM);
}
