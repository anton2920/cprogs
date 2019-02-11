/* 
SetsCalc — powerful sets calculator
Copyright © 2018 Anton

This file is part of SetsCalc.

SetsCalc is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

SetsCalc is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with SetsCalc. If not, see <https://www.gnu.org/licenses/>.
*/

#include "headers/project.h"

main() {

    /* Initializing variables */
    int func; 
    char a[NAME] = "{}", b[NAME] = "{}", c[NAME] = "{}", expr[NAME] = "", expr_cpy[NAME] = "", res[NAME] = "";
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
		
		strcpy(expr_cpy, expr);
		strcpy(res, "");
		b_tree = NULL;

		if ((b_tree = maketree(b_tree, expr_cpy, &base_sets))) {
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
