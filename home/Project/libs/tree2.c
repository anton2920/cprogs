#include "../headers/project.h"

struct tnode *talloc(void) {

	/* Returning value */
	return (struct tnode *) malloc(sizeof(struct tnode));
}

struct tnode *maketree(struct tnode *p, char *expr, const struct set *sets) {

	/* Initializing variables */
	char exprl[NAME], exprr[NAME], *sklad; /* *slojh */
	int len = strlen(expr), diff, minus = 1;
	struct tnode *l = NULL, *r = NULL;

	/* Main part */
	printf("IN, len = %d", len);
	getchar();
	if (!p) {
		p = talloc();
		if (!p) {
			return NULL;
		}
		printf("ALLOC");
		getchar();
		do {
			if (*expr == '-' && len != 2) {
				minus *= -1;
				to_neg(expr);
			}
		} while (de_par(expr)); 
		printf("Minus = %d", minus);
		getchar();
		printf("de_par");
		getchar();
		if (len == 1 || (len == 2 && *expr == '-')) {
			p->op = strdup(expr);
			printf("OP = %s", p->op);
			getchar();
		} else {
			p->op = strdup(find_op(expr));
			printf("%s, znak = %c", p->op, *p->op);
			getchar();
		}
		p->left = p->right = NULL;
	}
	
	if (len > 2) {
		printf("strstr = %s, %ld", strstr(expr, p->op), (strstr(expr, p->op)) - expr);
		getchar();
		diff = (int) (strstr(expr, p->op) - expr);
		strcpy(exprl, expr);
		*(exprl + diff) = '\0';
		printf("exprl = %s", exprl);
		getchar();
		strcpy(exprr, strstr(expr, p->op + 1)); 
		printf("exprr = %s", exprr);
		getchar();
		l = LEFT_TREE; /* #define */
		printf("p->left = %s", l->op);
		getchar();
		sklad = strdup(l->op);
		r = RIGHT_TREE; /* #define */
		printf("l = %s, r = %s", sklad, r->op);
		getchar();
		if (*sklad != '-' && *r->op != '-') {
			switch (*p->op) {
				case '+': case 'v': case 'V': 
					p->op = sum(sklad, r->op, 0); 
					break;
				case '*': case '^':
					p->op = mul(sklad, r->op, 0);
					break;
				case '\\':
					p->op = sub(sklad, r->op, 0);
					break;
				default:
					break;
			}
		} else if (*sklad != '-' && *r->op == '-') {
			to_neg(r->op);
			switch (*p->op) {
				case '+': case 'v': case 'V': 
					p->op = sub(r->op, sklad, 1);
					break;
				case '*': case '^':
					p->op = sub(sklad, r->op, 0);
					break;
				case '\\':
					p->op = mul(sklad, r->op, 0);
					break;
				default:
					break;
			}
		} else if (*sklad == '-' && *r->op != '-') {
			to_neg(sklad);
			switch (*p->op) {
				case '+': case 'v': case 'V': 
					p->op = sub(sklad, r->op, 1);
					break;
				case '*': case '^':
					p->op = sub(r->op, sklad, 0);
					break;
				case '\\':
					p->op = sum(sklad, r->op, 1);
					break;
				default:
					break;
			}
		} else {
			to_neg(sklad);
			to_neg(r->op);
			switch (*p->op) {
				case '+': case 'v': case 'V': 
					p->op = mul(sklad, r->op, 1);
					break;
				case '*': case '^':
					p->op = sum(sklad, r->op, 1);
					break;
				case '\\':
					p->op = sub(r->op, sklad, 0);
					break;
			}
		}
		if (minus == -1) {
			to_neg(p->op);
		}
	} else {
		p->op = strdup(derefer(p->op, sets));
		printf("p->op = %s", p->op);
		getchar();
		if (!p->op) {
			return NULL;
		}
	}

	/* Returning value */
	printf("Return!");
	getchar();
	return p;
}

int de_par(char *str) {
	
	/* Initializing variables */
	int i, level = 0, len = strlen(str), min_level = NAME;
	char str2[NAME];

	/* Main part */
	printf("%s", str);
	getchar();
	for (i = 0; i < len - 1; ++i) {
		printf("i = %d, level = %d", i, level);
		getchar();
		if (*(str + i) == '(') {
			++level;
		} else if (*(str + i) == ')') {
			--level;
		}
		if (level < min_level && i) {
			min_level = level;
		}
	}
	if (min_level != NAME && min_level != 0) {
		*(str + (len - 1)) = '\0';
		strcpy(str2, str + 1);
		strcpy(str, str2);
		return 1;
	} else if (min_level == NAME) {
		return 0;
	}

	/* Returning value */
	return 0;
}

char *find_op(const char *str) {

	/* Initializing variables */
	int level = 0, i, len = strlen(str);
	char znak;
	
	/* Main part */
	for (i = 0; i < len; ++i) {
		printf("i = %d, level = %d", i, level);
		getchar();
		if (*(str + i) == '(') {
			++level;
		} else if (*(str + i) == ')') {
			--level;
		} else if (isop(*(str + i)) && !level) {
			znak = *(str + i);
		}
	}

	/* Returning value */
	return strchr(str, znak);
}

int isop(const char znak) {
	
	/* Returning value */
	return (znak == '+' || znak == '*' || znak == 'v' || znak == 'V' || znak == '^' || znak == '\\') ? 1 : 0;
}

char *derefer(const char *str, const struct set *sets) {
		
	/* Initializing variables */
	char str2[NAME] = "", *pstr = str2;

	/* Main part */
	if (!strcmp(str, "A")) {
		strcpy(str2, sets->a);
		return pstr;
	} else if (!strcmp(str, "-A")) {
		strcpy(str2, sets->a);
		to_neg(str2);
		return pstr;
	} if (!strcmp(str, "B")) {
		strcpy(str2, sets->b);
		return pstr;
	} else if (!strcmp(str, "-B")) {
		strcpy(str2, sets->b);
		to_neg(str2);
		return pstr;
	} else if (!strcmp(str, "C")) {
		strcpy(str2, sets->c);
		return pstr;
	} else if (!strcmp(str, "-C")) {
		strcpy(str2, sets->c);
		to_neg(str2);
		return pstr;
	}

	/* Returning value */
	return NULL;
}