#include "../headers/project.h"

char *strdup(char *s) {

	/* Initializing variables */
	char *p = (char *) malloc(strlen(s) + 1);

	/* Main part */
	if (p)
		strcpy(p, s);
	
	/* Returning value */
	return p;
}

struct tnode *talloc(void) {

	/* Returning value */
	return (struct tnode *) malloc(sizeof(struct tnode));
}

struct tnode *maketree(struct tnode *p, char *expr) {

	/* Initializing variables */
	char *znak, exprl[NAME], exprr[NAME];
	int diff;

	/* Main part */
	if (p == NULL) {
		p = talloc();
		p->op = strdup(expr);
		p->left = p->right = NULL;
	}
	
	de_par(expr);
	znak = find_op(expr);
	strncpy(exprl, expr, expr - znak);
	strcpy(exprr, znak + 1);
	diff = strlen(exprl) - strlen(exprr);
	diff = ABS(diff);
	if (diff <= 1) {
		switch (znak) {
			case "+": case "v": case "V":
				sum(exprl, exprr);
				break;
			case "*": case "^":
				mul(exprl, exprr);
				break;
			case "\\":
				sub(exprl, exprr);
				break;
		}
	} else {
		p->left = maketree(p->left, exprl, res);
		p->right = 
	}

	/* Returning value */
	return p;
}
