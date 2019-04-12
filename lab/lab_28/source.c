#include "source.h"

/* task #7 */
bool check_args(int argc, char *argv[]) {

    /* VarCheck */
    if (argc == 2) {
        if (**(argv + 1) == '1' || **(argv + 1) == '2' || **(argv + 1) == '3') {
            return true;
        }
    }
    
    fprintf(stderr, "Error! Arguments problem!\n");

    /* Returning value */
    return false;
}

bool create_string(char **a) {

    /* Main part */
     if ((*a = (char *) malloc(INT_MAX))) {
        return true;
     }

    /* Returning value */
    return false;
}

void read_text(struct string *a) {

    /* Initializing variables */
    register int i;

    /* I/O flow */
    puts("Type text [Ctrl + D (i.e EOF) to finish]: ");
    for (i = 0; (a->str[i] = (char) getchar()) != EOF; ++i)
        ;

    /* Main part */
    a->str[i] = '\0';
    if ((a->str = realloc(a->str, (i + 1) * sizeof(char))) == NULL) {
        exit(1);
    }

}

void find_digits(struct string *a) {

    /* Initializing variables */
    register int i;

    /* Main part */
    for (i = 0; i < strlen(a->str); ++i) {
        if (isdigit(a->str[i])) {
            rm_ch(a->str, i);
            ++a->num_num;
            --i;
        }
    }
}

void rm_ch(char *str, int ch_n) {

    /* Initializing variables */
    register int i;

    /* Main part */
    for (i = ch_n; i < strlen(str) || *(str + i) != '\0'; ++i) {
        *(str + i) = *(str + (i + 1));
    }
}

void print_text(char *a) {

    /* Initializing variables */
    register int i;

    /* I/O flow */
    puts("\nYour text: ");
    for (i = 0; i < strlen(a); ++i) {
        putchar(*(a + i));
    }
}

void print_num_num(int num) {

    /* Final output */
    printf("\nThe number of removed digits: %d\n", num);
}

void delete_string(char *a) {

    /* Main part */
    free(a);
}

/* task #16 */
void read_str(char **a) {

    /* Initializing variables */
    char *n_l;

    /* I/O flow */
    puts("Type string: ");
    fgets(*a, INT_MAX, stdin);

    /* Main part */
    n_l = strstr(*a, "\n");
    *n_l = '\0';
    *a = realloc(*a, strlen(*a));
}

void rm_sp(char *a) {

    /* Initializing variables */
    register int i;

    /* Main part */
    for (i = 1; i < strlen(a); ++i) {
        if (*(a + (i - 1)) == ' ' && *(a + i) == ' ') {
            rm_ch(a, i);
            --i;
        }
    }

    if (*(a + (i - 1)) == ' ') {
        *(a + (i - 1)) = '\0';
    }
}

void print_str(char *a) {

    /* I/O flow */
    puts("Your string: ");
    puts(a);
}

/* task #25 */
int find_occ(char *sent, struct word *word) {

    /* Initializing variables */
    register int i;
    struct word curr_word = { sent, 0 };
    int num_of_occ = 0;

    /* Main part */
    for (i = 0; i < strlen(sent); ++i) {
        if ((curr_word = get_next_word(&curr_word)).str == NULL) {
            break;
        } else {
            if (!strncmp(word->str, curr_word.str, (size_t) word->wd_len) && word->wd_len == curr_word.wd_len) {
                ++num_of_occ;
            }
            curr_word.str += curr_word.wd_len;
        }
    }

    /* Returning value */
    return num_of_occ;
}

struct word get_next_word(struct word *c_word) {

    /* Initializing variables */
    register int i;
    struct word c_w = *c_word;

    /* Main part */
    for ( ; !isalpha(*c_w.str); ++c_w.str) {
        if (*c_w.str == '\0') {
            c_w.str = NULL;
            c_w.wd_len = 0;
            return c_w;
        }
    }

    for (i = 0; c_w.str[i] != ' ' && c_w.str[i] != ',' && c_w.str[i] != '.' && c_w.str[i] != '?' && c_w.str[i] != '!'; ++i) {
        if (c_w.str[i] == '\0') {
            c_w.str = NULL;
            c_w.wd_len = 0;
            return c_w;
        }
    }

    c_w.wd_len = i;

    /* Returning value */
    return c_w;
}

void find_sht(char *sent1, char *sent2) {

    /* Initializing variables */
    struct word wd = { sent1, 0 };
    int n;

    /* Main part */
    putchar(10);
    for ( ; (wd = get_next_word(&wd)).str != NULL; ) {
        n = find_occ(sent2, &wd);
        printf("The number of occurrences of «");
        fwrite(wd.str, sizeof(char), (size_t) wd.wd_len, stdout);
        printf("» = %d\n", n);
        wd.str += wd.wd_len;
    }
}