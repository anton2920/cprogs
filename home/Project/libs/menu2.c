#include "../headers/project.h"

int set_expr(char *exp) {
	
	/* Initializing variables */
	int func;
	dialog_vars.help_line = "Use: A, B, C and ^, v, -";
	char change[NAME];

	/* I/O flow */
	dialog_vars.input_result = change;
	init_dialog(stdin, stdout);
	func = dialog_inputbox(TITLE, "===> Type expression: ", 0, 0, "", 0);
	end_dialog();
	/* Check expr */
	strcpy(exp, change);

	/* Returning value */
	return func;
}
