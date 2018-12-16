#include "headers/project.h"

main() {

    /* Initializing variables */
    int func; 
    char a[NAME] = "{}", b[NAME] = "{}", c[NAME] = "{}", expr[NAME] = "", res[NAME] = "";
	struct tnode *b_tree = NULL;
	struct set base_sets;
	base_sets.a = a;
	base_sets.b = b;
	base_sets.c = c;

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
		b_tree = NULL;

		if ((b_tree = maketree(b_tree, expr, &base_sets))) {
			strcpy(res, b_tree->op);
			free(b_tree);
		} else {
			strcpy(res, ERROR_TREE);
		}
		if (*res == '-') {
			to_opp(res, 1);
		}
		
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
