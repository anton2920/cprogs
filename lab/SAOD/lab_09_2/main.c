#include <stdio.h>

#include "tree.h"

typedef int type_t;

int menu_continue(void);
void prt_ln(void);
void print_type_t(const Tree_node *);
int type_t_cmp(const void *_self, const void *_other);

main() {

    /* Initializing variables */
    auto Tree t;
    Tree_init(&t);
    type_t elem;

    /* I/O flow */
    prt_ln();
    do {
        printf("| Type tree element: ");
        scanf("%d", &elem);

        Tree_insert(&t, &elem, sizeof(type_t), type_t_cmp);
    } while (menu_continue());

    /* Main part */
    if (!Tree_isEmpty(&t)) {
        Tree_print(&t, print_type_t);
    }

    Tree_delete(&t);
}

int type_t_cmp(const void *_self, const void *_other) {

    /* Initializing variables */
    auto type_t *self = (type_t *) _self, *other = (type_t *) _other;

    /* Returning value */
    return (self > other) ? 1 : (self < other) ? -1 : 0;
}

void print_type_t(const Tree_node *elem) {

    /* Initializing variables */
    auto int *e = (int *) Tree_get_value(elem);

    /* VarCheck */
    if (e == NULL) {
        return;
    }

    /* I/O flow */
    printf("%d", *e);
}

void prt_ln(void) {

    /* Final output */
    printf(" ------------------------------------------------------------\n");
}

int menu_continue(void) {

    /* Initializing variables */
    int func;

    /* I/O flow */
    while (getchar() != '\n')
        ;

    while (1) {
        printf("| Continue? [y/N]: ");
        switch ((func = getchar())) {
            case 'y': case 'Y':
                if ((getchar()) != '\n') {
                    while ((getchar()) != '\n')
                        ;
                    prt_ln();
                    continue;
                }
                prt_ln();
                return 1;
            case 'n': case 'N': case '\n':
                if (func == 'n' || func == 'N') {
                    if ((getchar()) != '\n') {
                        while ((getchar()) != '\n')
                            ;
                        prt_ln();
                        continue;
                    }
                }
                prt_ln();
                return 0;
            default:
                while ((getchar()) != '\n')
                    ;
                prt_ln();
                continue;
        }
    }
}