#include "headers/project.h"

main() {

    /* Initializing variables */
    int func; 
    char a[NAME] = "{}", b[NAME] = "{}", c[NAME] = "{}", expr[NAME] = "", res[NAME];

    /* Main part */
	srand(time(NULL));
	while (1) {
		strcpy(res, "===> Answer: ");
		while (1) {
    		if (!(func = set_sets(a, b, c)) && (strcmp(a, "{}") || strcmp(b, "{}") || strcmp(c, "{}"))) {
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
	
		while (1) {
			if ((func = set_expr(expr)) == 1) {
				lclear();
				return 0;
			} else if (!func && !strcmp(expr, "Error!")) {
				continue;
			} else {
				break;
			}
		}
	
		printf("%s\n", expr);
		
		if ((func = prt_res(res)) == 1) {
			lclear();
			return 0;
		}

		if ((func = cont()) == 0) {
			continue;
		} else {
			break;
		}
	}

	/* Final output */
	lclear();
}

void lclear(void) {

	/* Main part */
	system(COMM);
}
