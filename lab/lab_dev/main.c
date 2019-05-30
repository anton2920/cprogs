#include <stdio.h>
#include <STL.h>
#include <string.h>

#define SIZE (50)
#define ENDING(__expr) (((__expr) == 1) ? "st" : ((__expr) == 2) ? "nd" : ((__expr) == 3) ? "rd" : "th")
#ifndef MAX
    #define MAX(A, B) (((A) > (B)) ? (A) : (B))
#endif
#ifndef MIN
    #define MIN(A, B) (((A) < (B)) ? (A) : (B))
#endif

/* New data types */
struct person {
    char last_name[SIZE];
    int age;
    int year;
    int group_num;
    int score[5];
};


/* Function declarations */
void prt_ln(void);
void find_mean(List *);
void find_age(List *);
void find_biggest_group(List *);

main() {

    /* Initializing variables */
    auto List a;
    auto struct person p;
    auto int i;

    /* I/O flow && VarCheck */
    do {
        prt_ln();
        printf("Student info: \n");
        prt_ln();
        printf("Type a student's last name (type «0» to finish): ");
        scanf("%s", p.last_name);
        if (!strcmp("0", p.last_name)) {
            prt_ln();
            printf("Finishing...\n");
            break;
        }
        do {
            printf("Type age (must be less than 100): ");
            scanf("%d", &p.age);
        } while (p.age > 100 || p.age < 0);
        do {
            printf("Type a year: ");
            scanf("%s", &p.year);
        } while (p.year < 0 || p.year > 15);
        do {
            printf("Type a group number: ");
            scanf("%d", &p.group_num);
        } while (p.group_num < 0);
        for (i = 0; i < 5; ++i) {
            do {
                printf("Type score on the %d%s subject: ", i, ENDING(i));
                scanf("%d", (p.score + i));
            } while (*(p.score + i) < 0);
        }

        List_Stack_push_nbytes(&a, &p, sizeof(struct person));
    } while (1);

    /* Main part */
    find_mean(&a);
    find_age(&a);
    find_biggest_group(&a);


    /* Returning value */
    return 0;
}

void prt_ln(void) {

    /* Final output */
    printf(" -----------------------------------------------------------\n");
}

void find_mean(List *l) {

    /* Initializing variables */
    auto List a;
    auto int i;
    auto list_node *iter;
    auto struct person *curr_p;

    /* Main part */
    /*for (i = 0; ) {

    }

    for (iter = l->bp; iter != NULL; iter = iter->next) {
        if () {

        }
    }*/
}

void find_age(List *l) {

    /* Initializing variables */
    auto int min_age = 101, max_age = -1;
    auto list_node *iter;
    auto struct person *curr_p;

    /* Main part */
    for (iter = l->bp; iter != NULL; iter = iter->next) {
        curr_p = iter->value;
        min_age = MIN(min_age, curr_p->age);
        max_age = MAX(max_age, curr_p->age);
    }

    printf("The oldest student: %d\n", max_age);
    printf("The youngest student: %d\n", min_age);

    /* Final output */
    prt_ln();
}

void find_biggest_group(List *l) {

    /* Initializing variables */

}