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
