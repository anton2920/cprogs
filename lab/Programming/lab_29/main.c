#include "source.h"

main() {

    /* Initializing variables */
    struct string s = { NULL, 0 };
    char letter;

    /* I/O flow */
    if (create_string(&s.str) != false) {
        read_text(&s);
        letter = read_letter();
        find_letter(letter, &s);
        print_let_num(letter, s.let_num);
        delete_string(s.str);
    } else {
        str_err();
    }
}