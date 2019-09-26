#include "libs/libs.h"

enum buf_consts {
    BUFSIZE = 1024
};

main() {

    /* Initializing variables */
    auto char buf[BUFSIZE];
    auto size_t nlines, i, len;
    auto FILE *infile = fopen("test.txt", "r"), *outfile = fopen("out.txt", "w");
    auto char **lines;

    /* Main part */
    for (nlines = 0; ; ++nlines) {
        if ((fgets(buf, BUFSIZE, infile)) == NULL) {
            break;
        }
    }

    fseek(infile, 0L, SEEK_SET);

    /* Memory allocation */
    lines = (char **) malloc(nlines * sizeof(char *));
    for (i = 0; i < nlines; ++i) {
        fgets(buf, BUFSIZE, infile);
        len = strlen(buf);
        if (*(buf + len - 1) != '\n') {
            *(buf + len) = '\n';
            *(buf + len + 1) = '\0';
        }
        *(lines + i) = strdup(buf);
    }

    for (i = nlines - 1; i != -1; --i) {
        fwrite(*(lines + i), sizeof(char), strlen(*(lines + i)), outfile);
    }

    /* Cleaning */
    for (i = 0; i < nlines; ++i) {
        free(*(lines + i));
    }
    free(lines);
}