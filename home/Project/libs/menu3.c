#include "../headers/project.h"

int prt_res(char *res) {

	/* Initializing variables */
	int func;
	dialog_vars.help_line = "";

	/* Final output */
	init_dialog(stdin, stdout);
	func = dialog_msgbox(TITLE, res, 0, 0, 1);
	end_dialog();
	
	/* Returning value */
	return func;
}

int cont(void) {

	/* Initializing variables */
	int func;
	dialog_vars.defaultno = 1;

	/* Final output */
	init_dialog(stdin, stdout);
	func = dialog_yesno(TITLE, "===> Continue?", 0, 0);
	end_dialog();

	/* Returning value */
	return func;
}
