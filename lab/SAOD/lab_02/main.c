#include "libs.h"

enum buf_const{
    BUFSIZE = 1024
};

enum error_codes {
    FILE_ERR = 1,
};

main() {

    /* Initializing variables */
    auto FILE *inputs;
    auto char buf[BUFSIZE] = "", *curr_p = buf;
    auto struct token *op = NULL, *num1 = NULL, *num2 = NULL;
    auto long max_res = LONG_MIN, res;
    auto size_t string_index = 1, curr_str;

    /* Main part */
    if ((inputs = getFd()) == NULL) { /* Open file for reading */
        fprintf(stderr, "Error with opening file!\n");
        return FILE_ERR;
    }

    for (curr_str = 1; ; ++curr_str) {
        if (fgets(buf, BUFSIZE, inputs) == NULL) {
            break;
        }
        for (curr_p = buf; *curr_p != '\n'; curr_p = op->beg + 1) {

            /* Memory management */
            if (op != NULL) {
                free(op);
                op = NULL;
            }
            if (num1 != NULL) {
                free(num1);
                num1 = NULL;
            }
            if (num2 != NULL) {
                free(num2);
                num2 = NULL;
            }

            /* Parsing */
            if ((op = tryParseForOp(curr_p, strlen(curr_p))) == NULL) {
                break;
            }
            if ((num1 = getFirstNum(op, curr_p, (char *) op->beg - curr_p)) == NULL) {
                continue;
            }
            if ((num2 = getSecondNum(op, curr_p, (char *) op->beg - curr_p)) == NULL) {
                continue;
            }

            /* Final evaluation part */
            if ((res = eval(num1, op, num2)) > max_res) {
                max_res = res;
                string_index = curr_str;
            }
        }
    }

    fseek(inputs, SEEK_SET, 0);

    for (curr_str = 0; curr_str < string_index; ++curr_str) {
        fgets(buf, BUFSIZE, inputs);
    }

    /* Final output */
    printf("\nString with the maximum value of expression is string %lu\n%s\n", string_index, buf);

    fclose(inputs);
}