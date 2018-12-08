#include <dialog.h>
#include <curses.h>
#include "../headers/project.h"

int set_sets(char *a, char *b, char *c) {

    /* Initializing variables */
    int func;
    char *list[3] = {"{}", "{}", "{}"};
    dialog_vars.input_menu = 1;

    /* I/O flow */
    init_dialog(stdin, stdout);
    func = dialog_menu(TITLE, "===> Type sets", 0, 0, 10, 3, list);
    end_dialog();

    /* Returning value */
    return func;
}