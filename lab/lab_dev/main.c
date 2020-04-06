#include <stdio.h>
#include <ctype.h>

void menu(void);
int menu_continue(void);
int quit_m(void);
void prt_ln(void);
void no_cmd(void);

main() {

    /* I/O flow */
    menu();
}

void prt_ln(void) {

    /* Final output */
    printf(" ------------------------------------------------------------\n");
}

void no_cmd(void) {

    /* Final output */
    printf("| menu: no such command!                                     |\n");
}

void menu() {
    /* Initializing variables */
    int func, n = 0;

    /* I/O flow */
    while (1) {
        printf(" ------------------------------------------------------------\n"
               "|                                                            |\n"
               "|                   >> Process monitor <<                    |\n"
               "|                                                            |\n"
               "|  >> Choose a scheduling algorithm:                         |\n"
               "|                                                            |\n"
               "|       1) HLRR                                              |\n"
               "|       2) Round robin                                       |\n"
               "|                                                            |\n"
               "|       >> Type \"quit\" to terminate this program <<          |\n"
               "|                                                            |\n");
        printf("| Answer: ");
        func = getchar();
        prt_ln();
        if (isdigit(func) && func >= '1' && func <= '6') {
            func -= '0';
            if ((getchar()) != '\n') {
                while ((getchar()) != '\n')
                    ;
                no_cmd();
                continue;
            }

            switch (func) {
                case 1:

                    break;
                case 2:

                    break;
                default:
                    break;
            }

            if (!menu_continue()) {
                return;
            }

        } else if (func == 'q') {
            if (quit_m()) {
                return;
            } else {
                continue;
            }
        } else {
            no_cmd();
            if (func != '\n') {
                while ((getchar()) != '\n')
                    ;
            }
            continue;
        }
    }
}

int menu_continue(void) {

    /* Initializing variables */
    int func, junk;

    /* I/O flow */
    while (1) {
        printf("| Continue? [y/N]: ");
        switch ((func = getchar())) {
            case 'y': case 'Y':
                if ((junk = getchar()) != '\n') {
                    while ((junk = getchar()) != '\n')
                        ;
                    prt_ln();
                    continue;
                }
                prt_ln();
                return 1;
            case 'n': case 'N': case '\n':
                if (func == 'n' || func == 'N') {
                    if ((junk = getchar()) != '\n') {
                        while ((junk = getchar()) != '\n')
                            ;
                        prt_ln();
                        continue;
                    }
                }
                prt_ln();
                return 0;
            default:
                while ((junk = getchar()) != '\n')
                    ;
                prt_ln();
                continue;
        }
    }
}

int quit_m(void) {

    /* Initializing variables */
    int junk;

    /* Main part */
    if ((junk = getchar()) == 'u') {
        if ((junk = getchar()) == 'i') {
            if ((junk = getchar()) == 't') {
                if ((junk = getchar()) == '\n') {
                    return -1;
                } else {
                    no_cmd();
                    while ((junk = getchar()) != '\n')
                        ;
                    return 0;
                }
            } else {
                no_cmd();
                if (junk == '\n') {
                    return 0;
                } else {
                    while ((junk = getchar()) != '\n');
                    return 0;
                }
            }
        } else {
            no_cmd();
            if (junk == '\n') {
                return 0;
            } else {
                while ((junk = getchar()) != '\n');
                return 0;
            }
        }
    } else {
        no_cmd();
        if (junk == '\n') {
            return 0;
        } else {
            while ((junk = getchar()) != '\n');
            return 0;
        }
    }
}