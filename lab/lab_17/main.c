#include "lab.h"

/* Structure: highest and lowest price */
int main() {

    /* Initializing variables */
    struct arr mas;
    int func, func1, func2;
    srand((unsigned int) time(NULL));

    /* Main part */
    while (1) {
        func = 0;
        switch (func1 = menu(&mas.n, &mas.m)) {
            case -1:
                system("clear");
                return 0;
            case 1:
                read_key(&mas);
                break;
            case 2:
                read_rand(&mas);
                break;
            case 3:
                read_file(&mas);
                func = (!mas.n && !mas.m) ? -2 : 0;
                break;
            case 4:
                read_formula(&mas);
                break;
            default:
                break;
        }

        func2 = (!func) ? menu2() : func;

        /* Main part */


        /* Final output */
        switch (func2) {
            case -1:
                system("clear");
                return 0;
            case 0:
                write_scr(&mas);
                break;
            case 1:
                write_scr(&mas);
                write_file(&mas);
                break;
            default:
                break;
        }
        if (menu3()) {
            continue;
        } else {
            system("clear");
            return 0;
        }
    }
}