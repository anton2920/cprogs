#include "../headers/llfile.h"

int lgetchar(void) {

    /* Initializing variables */
    static char buf[BUFSIZE];
    static char *bufp = buf;
    static int n = 0;

    /* I/O flow */
    if (!n) {
        n = (int) read(0, buf, BUFSIZE);
        bufp = buf;
    }

    /* Returning variables */
    return (--n >= 0) ? (unsigned char) *bufp++ : EOF;
}

void lputchar(int n) {

    /* I/O flow */
    write(1, &n, 1);
}

int lisnum(int *n) {

    /* Returning value */
    return (*n >= '0' && *n <= '9') ? 1 : 0;
}

int lisspace(int n) {

    /* Returning value */
    return (n == ' ' || n == '\t') ? 1 : 0;
}

int linput(const char *str, const int n, long int *res) {

    /* This function allows you to assign some integer value to a variable. If you type something but integer,
     * the program asks you to type proper value. It's an endless loop, so you must type an integer */

    /* Initializing variables */
    int a, flag = -1, multiplier = 1, counter = 0;
    *res = 0;

    /* Main part */
    while (1) {
        write_str_scr(str, n);
        while (1) {
            a = lgetchar(); /* Gets one typed char at a time */
            if (a == '-') { /* Detects a negative sign */
                multiplier = -1;
            } else if (a == '+') { /* Detects a positive sign */
                multiplier = 1;
            } else if (lisnum(&a) && flag != 0) { /* Detects digits */
                *res = (*res * 10) + (a - '0'); /* Making of the answer */
                flag = 1; /* «1» if a digit was detected */
                ++counter; /* Counts a number of successfully scanned digits */
            } else if (a != '\n' && a != '+' && a != '-') { /* Detects «garbage» */
                flag = 0; /* «0» if «garbage» was detected */
                *res = 0; /* Answer is equals to zero now */
                counter = 0;
                multiplier = 1;
            } else if (a == '\n') { /* Detects End-Of-Line char */
                break; /* End-Of-Line («Enter» button usually) is the only way to finish a number */
            }
        }
        if (flag == 1) { /* Checks whether only digits were typed */
            break; /* Congrats! Your number were successfully scanned */
        }
        flag = -1; /* «-1» if a previous attempt to scan a number was a fail */
    }
    *res *= multiplier; /* Applies negative sign, if necessary */

    return counter; /* Returns a number of successfully scanned digits */
}

int input(const char *str, const int n, int *res) {

    /* Returning value */
    return linput(str, n, (long *) res);
}

void read_mas_key(int *mas, int *n) {

    /* Initializing variables */
    int i;

    /* I/O flow */
    for (i = 0; i < *n; ++i) {
        input("Type array element: ", sizeof("Type array element: ") - 1, mas + i);
    }
}

int write_str_scr(const char *ptr, const int size) {

    return (int) write(1, ptr, size);
}

int numlength(int num) {

    /* Initializing variables */
    int i;

    /* Main part */
    for (i = 1; (num /= 10); ++i)
        ;

    /* Returning value */
    return i;
}

char *reverse(int num, int len) {

    /* Initializing variables */
    char mas[33];
    int i;
    char sign = (num >= 0) ? 1 : -1;
    char *ptr = mas;

    /* Main part */
    num *= sign;
    for (i = len; i > 0; --i) {
        *(mas + i) = (num % 10) + '0';
        num /= 10;
    }
    *mas = (sign == 1) ? '+' : '-';

    return ptr;
}

int write_int_scr(const int *num) {

    /* Initializing variables */
    int len = numlength(*num);
    char *ptr = reverse(*num, len);

    /* Returning value */
    return (*ptr == '+') ? write_str_scr(++ptr, len) : write_str_scr(ptr, len + 1);

}

void write_mas_scr(const int *mas, const int *n) {

    /* Initializing variables */
    int i;

    /* I/O flow */
    write_str_scr("Your array: ", sizeof("Your array: ") - 1);
    for (i = 0; i < *n; ++i) {
        write_int_scr(mas + i);
        if (i != *n - 1) {
            lputchar(',');
        }
        lputchar(' ');
    }
    lputchar('\n');
}