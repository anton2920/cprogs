#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "libs/libs.h"

enum buf_consts {
    BUFSIZE = 1024,
    WORDSIZE = 30
};

enum symbols {
    sym = ' ',
    nul = '\0'
};

main() {

    /* Initializing variables */
    auto char buf[BUFSIZE], word[WORDSIZE], **lines, **new_lines;
    auto FILE *infile = fopen("test.txt", "r"), *outfile = fopen("out.txt", "w");
    auto size_t max_length = 0, curr_length, max_word_length = 0;
    auto char *beg_sp, *end_sp;

    auto char *pbuf = buf, *lineptr;
    auto size_t nlines, offset;
    auto size_t i, j;
    auto size_t curr_l;
    auto struct word *curr_w;

    /* Main part */
    assert(infile != NULL && outfile != NULL);

    /* Finding out how many lines */
    for (nlines = 0; ; ++nlines) {
        if ((fgets(buf, BUFSIZE / 2, infile)) == NULL) {
            break;
        }

        pbuf = buf;
        while (*pbuf != '\n') {
            sscanf(pbuf, "%s", word);
            curr_length = strlen(word);
            if (curr_length > max_word_length) {
                max_word_length = curr_length;
            }
            pbuf += curr_length;
        }
    }

    fseek(infile, 0L, SEEK_SET);

    /* Store 'em all */
    lines = (char **) malloc(nlines * sizeof(char *));

    for (i = 0; i < nlines; ++i) {
        fgets(buf, BUFSIZE / 2, infile);
        *(lines + i) = strdup(buf);
    }

    /* Ask user for the offset */
    do {
        printf("Type offset: ");
        scanf("%lu", &offset);
    } while (offset < max_word_length);

    /* Split lines using following rules:
     * 1. We can't split the words
     * 2. smth...
     */

    new_lines = (char **) malloc(nlines * sizeof(char *));

    for (i = 0, j = 0; i < nlines; ++i) {
        lineptr = *(lines + i);
        while ((curr_w = get_next_word()) {

        }
    }

    /* sym insertion */
    for (;;) {
        if ((fgets(buf, BUFSIZE / 2, infile)) == NULL) {
            break;
        }

        for (beg_sp = strchr(buf, sym), curr_length = strlen(buf);
            curr_length < max_length;
            beg_sp = strchr(beg_sp + 1, sym), ++curr_length)
        {
            beg_sp = insertAfter(buf, curr_length + 1, sym, beg_sp - buf);

            if (beg_sp == NULL) {
                beg_sp = buf;
                --curr_length;
            }

            if (++curr_length >= max_length) {
                break;
            }

            end_sp = strrchr(buf, sym);
            end_sp = insertBefore(buf, curr_length + 1, nul, end_sp - buf);

            if (end_sp == NULL || end_sp <= beg_sp) {
                replaceNAll(buf, curr_length, nul, sym);
            }
        }

        replaceNAll(buf, curr_length, nul, sym);
        fprintf(outfile, "%s", buf);
        fflush(outfile);
    }

    fclose(infile);
    fclose(outfile);
}