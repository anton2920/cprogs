#include <stdio.h>
#include "input.h"

int getint(int *pn) {

    int c, sign;

    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return  0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

int isdigit(int a) {
    return  (a >= '0' && a <= '9') ? 1 : 0;
}

int isspace(int a) {
    return (a == ' ') ? 1 : 0;
}