#include "libs/libs.h"

enum buf_const {
    BUFSIZE = 1024
};

main() {

    /* Initializing variables */
    auto FILE *fp = fopen("test.txt", "r");
    auto FILE *out = fopen("out.txt", "w");
    auto char buf[BUFSIZE];

    /* Main part */
    fgets(buf, BUFSIZE, fp);
    fwrite(buf, strlen(buf), sizeof(char), out);
    fputc('\r', out);
    for (;;) {
        if ((fgets(buf, BUFSIZE, fp)) == NULL) {
            break;
        }

        fwrite(buf, strlen(buf), sizeof(char), out);
        fputc('\n', out);
        fseek(out, SEEK_SET, 0);
    }

    fclose(fp);
    fclose(out);
}