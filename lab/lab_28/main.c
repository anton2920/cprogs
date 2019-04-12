#include "source.h"

int main(int argc, char *argv[]) {

    /* VarCheck */
    if (check_args(argc, argv) == true) {

        /* Initializing variables */
        struct string s;
        char *sent1, *sent2;
        int task = **(argv + 1) - '0';

        /* I/O flow */
        switch (task) {
            case 1:
                if (create_string(&s.str) == true) {
                    s.num_num = 0;
                    read_text(&s);
                    find_digits(&s);
                    print_text(s.str);
                    print_num_num(s.num_num);
                    delete_string(s.str);
                }
                break;
            case 2:
                if (create_string(&s.str) == true) {
                    read_str(&s.str);
                    rm_sp(s.str);
                    print_str(s.str);
                    delete_string(s.str);
                }
                break;
            case 3:
                if (create_string(&sent1) == true && create_string(&sent2) == true) {
                    read_str(&sent1);
                    rm_sp(sent1);
                    read_str(&sent2);
                    rm_sp(sent2);
                    find_sht(sent1, sent2);
                    delete_string(sent1);
                    delete_string(sent2);
                }
                break;
            default:
                break;
        }
    }

    /* Returning value */
    return 0;
}