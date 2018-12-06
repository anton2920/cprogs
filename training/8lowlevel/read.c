#include "gets.h"
#include <stdio.h>

main() {

    int n;
    char buf[SIZE_BUF_GETS];

    write(1, "Type string: ", 13);
    n = gets(buf);
    /* write(1, "Your string: ", 13);
    * write(1, buf, n);
    */
    printf("Your string: %s\n", buf);
}