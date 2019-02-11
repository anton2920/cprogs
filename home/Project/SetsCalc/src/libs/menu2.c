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

#include "../headers/project.h"

static int func_err = 0;

int set_expr(char *exp) {
	
	/* Initializing variables */
	int func;
	extern int func_err;
	func_err = 0;
	dialog_vars.help_line = "Ctrl + U to clear field";
	dialog_vars.extra_button = 0;
	char change[NAME];

	/* I/O flow */
	dialog_vars.input_result = change;
	init_dialog(stdin, stdout);
	func = dialog_inputbox(TITLE, "===> Type expression: ", 0, 0, exp, 0);

	/* Check expr */
	strcpy(exp, change);
	rep_str(exp);
	if (func == 1) {
		end_dialog();
		return func;
	} else if (!check2(exp) || !strlen(exp)) {
		expr_err(ERROR_MSG);
		func_err = 1;
		end_dialog();
		return 3;
	}
	
	end_dialog();

	/* Returning value */
	return func;
}

int check2(const char *str) {

	/* Initializing variables */
	int i, parl = 0, parr = 0, op = 0, oper = 0, diff;

	/* Main part */
	if (strlen(str) == 1) {
		return 0;
	}
	for (i = 0; i < strlen(str); ++i) {
		if (*(str + i) != 'A' && *(str + i) != 'B' && *(str + i) != 'C' && *(str + i) != '-' && *(str + i) != '(' && *(str + i) != ')' && !isop(*(str + i))) {
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
			if (*(str + (i + 1)) == 'A' || *(str + (i + 1)) == 'B' || *(str + (i + 1)) == 'C') {
				return 0;
			}
			if (*(str + (i + 1)) == '-') {
				return 0;
			}
		} else if (isop(*(str + i))) {
			++oper;
			if (*(str + (i + 1)) == ')') {
				return 0;
			}
		}
		diff = op - oper;
		if (*(str + i) == '(' && (*(str + (i + 1)) == ')' || isop(*(str + (i + 1))))) {
			return 0;
		}
		if (*(str + i) == '-' && *(str + (i + 1)) == '-') {
			return 0;
		}

	}

	if (parl != parr)
		return 0;
	if (diff != 1) {
		return 0;
	}

	/* Returning value */
	return 1;
}

void expr_err(const char *str) {
	
	/* Initializing variables */
	extern int func_err;
	func_err = 1;

	/* Main part */
	dialog_msgbox(TITLE, str, 0, 0, 1);
}
