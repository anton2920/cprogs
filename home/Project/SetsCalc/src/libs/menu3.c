#include "../headers/project.h"

int prt_res(const char *res) {

	/* Initializing variables */
	int func;
	char res_fl[NAME] = "===> Answer: ";
	dialog_vars.help_line = "";
	strcat(res_fl, res);

	/* Final output */
	init_dialog(stdin, stdout);
	func = dialog_msgbox(TITLE, res_fl, 5, 100, 1);
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
