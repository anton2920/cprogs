#include "a1.h"

/* Structure: highest and lowest price */
int main() {

    /* Initializing variables */
    struct goods mas[MAXSIZE], min_g, max_g;
    int n;
    char func, func1, func2;
    srand((unsigned int) time(NULL));

    /* Main part */
    while (1) {
        struct_init(mas);
        func = 0;
        switch (func1 = menu2(&n)) {
            case -1:
                system("clear");
                return 0;
            case 1:
                read_key(mas, &n);
                break;
            case 2:
                read_rand(mas, &n);
                break;
            case 3:
                read_file(mas, &n);
                func = (!n) ? -2 : 0;
                break;
            default:
                break;
        }

        func2 = (!func) ? menu3() : func;

        /* Main part */
        min_g = min(mas, &n);
        max_g = max(mas, &n);

        /* Final output */
        switch (func2) {
            case -1:
                system("clear");
                return 0;
            case 0:
                write_all_scr(mas, &n);
                write_scr(&min_g, &max_g);
                break;
            case 1:
                write_all_scr(mas, &n);
                write_scr(&min_g, &max_g);
                write_file(&min_g, &max_g);
                break;
            default:
                break;
        }
        if (menu4()) {
            continue;
        } else {
            system("clear");
            return 0;
        }
    }
}