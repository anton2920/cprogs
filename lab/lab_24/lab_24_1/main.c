#include "source.h"

int main(int argc, char *argv[]) {

    /* Main part */
    if (check_args(argc, argv) == true) {

        /* Initializing variables */
        struct array mas;
        int way = **(argv + 1) - '0';

        /* I/O flow && VarCheck */
        printf("Lab_24, way %d\n\n", way);

        input_param(&mas, way);

        if (create_array(&mas) == true) {

            input_array(&mas);

            print_array(&mas);

            sum_of_row(&mas);

            delete_array(&mas);
        } else {
            arr_err();
        }
    }

    return 0;
}