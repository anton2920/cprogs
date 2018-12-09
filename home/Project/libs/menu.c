#include "../headers/project.h"

int set_sets(char *a, char *b, char *c) {

    /* Initializing variables */
    int func;
    char *list[] = {"A =", a, "B =", b, "C =", c};
	char change[NAME];
    dialog_vars.input_menu = 1;
	dialog_vars.help_line = "Ctrl + U to clear field";
	dialog_vars.extra_button = 1;
	dialog_vars.extra_label = "Change";
	dialog_vars.cancel_label = "Quit";

    /* I/O flow */
	dialog_vars.input_result = change;
    init_dialog(stdin, stdout);
    func = dialog_menu(TITLE, "===> Type sets: ", 0, 0, 10, 3, list);
    end_dialog();
	if (func == 0 || func == 1) {
		return func;
	}
	if (*(change + 8) == 'A') {
		strcpy(a, change + 12);
		rep_str(a);
		if (!check(a))
			strcpy(a, "Error! Use only «{», «}», «,», «.» and decimal digits");
	} else if (*(change + 8) == 'B') {
		strcpy(b, change + 12);
		rep_str(b);
		if (!check(b))
			strcpy(b, "Error! Wrong set format!");
	} else {
		strcpy(c, change + 12);
		rep_str(c);
		if (!check(c))
			strcpy(c, "Error! Wrong set format!");
	}

    /* Returning value */
    return func;
}

void rep_str(char *str) {

	/* Initializing variables */
	int i, j;

	/* Main part */
	for (i = 0; i < strlen(str); ++i) {
		if (isspace(*(str + i))) {
			for (j = i; j < strlen(str); ++j) {
				*(str + j) = *(str + (j + 1));
			}
			--i;
		}
	}
}

int check(char *str) {

	/* Initializing variables */
	int i, len = strlen(str);

	/* Main part */
	if (*str != '{')
		return 0;
	if (*(str + (len - 1)) != '}')
		return 0;
	if (len == 2) 
		return 1;

	for (i = 1; i < len - 1; ++i)
		if (!isdigit(*(str + i)) && *(str + i) != ',' && *(str + i) != '.')
			return 0;
	
	/* Returning value */
	return 1;
}
