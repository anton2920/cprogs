#include "headers/project.h"

main() {

    /* Initializing variables */
    int func; 
    char a[NAME] = "{}", b[NAME] = "{}", c[NAME] = "{}", expr[NAME] = "", res[NAME] = "";
	struct tnode *b_tree;

    /* Main part */
	srand(time(NULL));
	while (1) {
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

		while (1) {
			if (!(func = set_expr(expr))) {
				break;
			} else if (func == 1) {
				lclear();
				return 0;
			} else {
				continue;
			}
		}

		strcpy(res, "");
		
		/* b_tree = maketree(b_tree, expr);
		 * strcpy(res, b_tree->res);
		 */

		/* strcat(res, sum(a, b, 1));
		if (*res == '-') {
			to_opp(res, 0);
		}
		to_opp(res, 1); */

		strcat(res, mul(a, b, 0));		
		
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
