#include "../headers/project.h"

int set_expr(char *exp) {
	
	/* Initializing variables */
	int func;
	dialog_vars.help_line = "Use: A, B, C and ^, v, -";
	dialog_vars.extra_button = 0;
	char change[NAME];

	/* I/O flow */
	dialog_vars.input_result = change;
	init_dialog(stdin, stdout);
	func = dialog_inputbox(TITLE, "===> Type expression: ", 0, 0, exp, 0);
	end_dialog();
	/* Check expr */
	strcpy(exp, change);
	rep_str(exp);
	if (!check2(exp) || !strlen(exp)) {
		strcpy(exp, "Error!");
	}

	/* Returning value */
	return func;
}

int check2(char *str) {

	/* Initializing variables */
	int i, parl = 0, parr = 0, op = 0, oper = 0, diff;

	/* Main part */
	for (i = 0; i < strlen(str); ++i) {
		if (*(str + i) != 'A' && *(str + i) != 'B' && *(str + i) != 'C' && *(str + i) != 'v' && *(str + i) != '^' && *(str + i) != '-' && *(str + i) != 'V' && *(str + i) != '+' && *(str + i) != '*' && *(str + i) != '\\' && *(str + i) != '(' && *(str + i) != ')') {
			return 0;
		}
		if (*(str + i) == '(')
			++parl;
		if (*(str + i) == ')')
			++parr;
		if (parr > parl)
			return 0;
		if (*(str + i) == 'A' || *(str + i) == 'B' || *(str + i) == 'C') {
			++op;
		} else if (*(str + i) == 'v' || *(str + i) == '^' || *(str + i) == 'V' || *(str + i) == '+' || *(str + i) == '*' || *(str + i) == '\\') {
			++oper;
		}
		diff = (op >= oper) ? op - oper : oper - op;
		if (diff > 1)
			return 0;

	}

	if (parl != parr)
		return 0;

	/* Returning valuse */
	return 1;
}
