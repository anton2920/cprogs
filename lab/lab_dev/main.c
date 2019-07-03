#include <stdio.h>
#include <string.h>

#define STR_SIZE (256)

void rep_str(char *, const char *);

main() {

    /* Initializing variables */
    char string[STR_SIZE], *end, *beg;

    /* I/O flow */
    puts("Type a string: ");
    fgets(string, STR_SIZE, stdin);
    string[strlen(string) - 1] = 0;

    /* Main part */
    for ( ; ; ) {
        if (!(beg = strstr(string, "/*"))) {
            break;
        }
        if (!(end = strstr(string, "*/"))) {
            break;
        }
        rep_str(beg, end);
    }

    /* Final output */
    printf("Your string: %s\n", string);

    /* Returning value */
    return 0;
}

void rep_str(char *beg, const char *end) {

    /* Initializing variables */
    auto int i;
    end += 2;

    /* Main part */
    for (i = 0 ; beg < end; ++beg, ++i) {
        *beg = end[i];
    }

    for ( ; *beg; ++beg) {
        *beg = *(beg + 1);
    }
}