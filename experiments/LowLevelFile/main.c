#include "headers/llfile.h"

#define SIZE 100

main() {

    /* Initializing variables */
    int var, mas[SIZE], n;

    /* I/O flow */
    write_str_scr(">> Test program for low-level I/O <<\n", sizeof(">> Test program for low-level I/O <<\n") - 1);
    linput("Type int: ", sizeof("Type int: ") - 1, &var);
    write_str_scr("Your int: ", sizeof("Your int: ") - 1);
    write_int_scr(&var);
    write_str_scr("\n----------------------------------------------------------------\n", 66);
    linput("Type the number of elements: ", sizeof("Type the number of elements: ") - 1, &n);
    read_mas_key(mas, &n);
    write_mas_scr(mas, &n);
}