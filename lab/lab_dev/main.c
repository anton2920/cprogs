#include "libs/libs.h"

enum buf_consts {
    BUFSIZE = 1024,
    WORDSIZE = 30
};

main() {

    /* Initializing variables */
    auto char buf[BUFSIZE] = "", new_buf[BUFSIZE], *lineptr, *curr_insert;
    auto char word1[WORDSIZE], word2[WORDSIZE];
    auto FILE *infile = fopen("test.txt", "r"), *outfile = fopen("out.txt", "w");
    auto struct word *curr_word = NULL;
    auto size_t word2l;

    /* I/O flow */
    printf("Type a first word: ");
    scanf("%s", word1);
    printf("Type a second word: ");
    scanf("%s", word2);

    /* Main part */
    if (infile == NULL || outfile == NULL) {
        perror("Problem with files");
    }

    word2l = strlen(word2);

    for (;;) {
        if ((fgets(buf, BUFSIZE / 2, infile)) == NULL) {
            break;
        }
        memset(new_buf, 0, BUFSIZE);
        memcpy(new_buf, buf, strlen(buf));

        for (lineptr = buf, curr_insert = new_buf; ; lineptr = curr_word->beg + curr_word->length) {
            if ((curr_word = find_word(lineptr, word1)) == NULL) {
                break;
            }
            memset(new_buf, 0, BUFSIZE);

            memcpy(curr_insert, buf, curr_word->beg - buf);
            curr_insert += curr_word->beg - lineptr;
            memcpy(curr_insert, word2, word2l);
            curr_insert += word2l;
            memcpy(curr_insert, curr_word-> beg + curr_word->length, strlen(curr_word->beg + curr_word->length));

            memcpy(buf, new_buf, strlen(new_buf));

            /* Clean up */
            free(curr_word);
        }
        fprintf(outfile, "%s", new_buf);
    }

    fclose(infile);
    fclose(outfile);
}