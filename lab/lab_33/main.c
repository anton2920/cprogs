#include <stdio.h>
#include <STL.h>
#include <string.h>
#include <grp.h>

#define SIZE (50)
#define ENDING(__expr) (((__expr) == 1) ? "st" : ((__expr) == 2) ? "nd" : ((__expr) == 3) ? "rd" : "th")
#ifndef MAX
    #define MAX(A, B) (((A) > (B)) ? (A) : (B))
#endif
#ifndef MIN
    #define MIN(A, B) (((A) < (B)) ? (A) : (B))
#endif

/* New data types */
struct lgroup {
    int year;
    int group_num;
};

struct person {
    char last_name[SIZE];
    int age;
    struct lgroup grp;
    int score[5];
};


/* Function declarations */
void prt_ln(void);
void find_mean(List *, List *);
void find_age(List *);
void find_biggest_group(List *, List *);

main() {

    /* Initializing variables */
    auto List a, gr;
    auto struct person p;
    auto int i;
    auto list_node *iter;
    auto __bool is_found = __false;
    auto struct lgroup *curr_gp, curr_g;
    List_init(&a);
    List_init(&gr);

    /* I/O flow && VarCheck */
    do {
        is_found = __false;
        prt_ln();
        printf("Student info: \n");
        prt_ln();
        printf("Type a student's last name (type «0» to finish): ");
        scanf("%s", p.last_name);
        if (!strcmp("0", p.last_name)) {
            prt_ln();
            printf("Finishing...\n");
            prt_ln();
            break;
        }
        do {
            printf("Type age (must be less than 100): ");
            scanf("%d", &p.age);
        } while (p.age > 100 || p.age < 0);

        do {
            printf("Type a year: ");
            scanf("%d", &p.grp.year);
        } while (p.grp.year < 0 || p.grp.year > 15);
        do {
            printf("Type a group number: ");
            scanf("%d", &p.grp.group_num);
        } while (p.grp.group_num < 0);
        curr_g.year = p.grp.year;
        curr_g.group_num = p.grp.group_num;
        for (iter = gr.bp->next; iter != NULL; iter = iter->next) {
            curr_gp = iter->value;
            if (curr_gp->group_num == p.grp.group_num && curr_gp->year == p.grp.year) {
                is_found = __true;
                break;
            }
        }
        if (!is_found) {
            List_Stack_push_nbytes(&gr, &curr_g, sizeof(struct lgroup));
        }

        for (i = 0; i < 5; ++i) {
            do {
                printf("Type score on the %d%s subject: ", i + 1, ENDING(i + 1));
                scanf("%d", (p.score + i));
            } while (*(p.score + i) < 0);
        }

        List_Stack_push_nbytes(&a, &p, sizeof(struct person));
    } while (1);

    /* Main part */
    find_mean(&a, &gr);
    find_age(&a);
    find_biggest_group(&a, &gr);

    List_delete(&a);
    List_delete(&gr);


    /* Returning value */
    return 0;
}

void prt_ln(void) {

    /* Final output */
    printf(" -----------------------------------------------------------\n");
}

void find_mean(List *l, List *gr) {

    /* Initializing variables */
    auto int i;
    auto list_node *iter, *iter2;
    auto struct person *curr_p;
    auto struct lgroup *curr_gp;
    auto int p_count;
    auto double mean;

    /* Main part */
    for (iter2 = gr->bp->next; iter2 != NULL; iter2 = iter2->next) {
        curr_gp = iter2->value;
        printf("Group %d%s-year #%d\n", curr_gp->year, ENDING(curr_gp->year), curr_gp->group_num);
        for (i = 0; i < 5; ++i) {
            p_count = 0;
            mean = 0.0;
            for (iter = l->bp->next; iter != NULL; iter = iter->next) {
                curr_p = iter->value;
                if (curr_p->grp.group_num == curr_gp->group_num &&
                        curr_p->grp.year == curr_gp->year) {
                    ++p_count;
                    mean += curr_p->score[i];
                }
            }
            mean /= p_count;
            printf("Average score on %d%s subject: %lf\n", i + 1, ENDING(i + 1), mean);
        }
        prt_ln();
    }
}

void find_age(List *l) {

    /* Initializing variables */
    auto int min_age = 101, max_age = -1;
    auto list_node *iter;
    auto struct person *curr_p;

    /* Main part */
    for (iter = l->bp->next; iter != NULL; iter = iter->next) {
        curr_p = iter->value;
        min_age = MIN(min_age, curr_p->age);
        max_age = MAX(max_age, curr_p->age);
    }

    printf("The oldest student: %d\n", max_age);
    printf("The youngest student: %d\n", min_age);

    /* Final output */
    prt_ln();
}

void find_biggest_group(List *l, List *gr) {

    /* Initializing variables */
    auto int i;
    auto list_node *iter, *iter2;
    auto struct person *curr_p;
    auto struct lgroup *curr_gp;
    auto int group_max = -1, curr_st_count;
    auto struct lgroup *biggest_gr = NULL;

    /* Main part */
    for (iter2 = gr->bp->next; iter2 != NULL; iter2 = iter2->next) {
        curr_st_count = 0;
        curr_gp = iter2->value;
        for (iter = l->bp->next; iter != NULL; iter = iter->next) {
            curr_p = iter->value;
            if (curr_p->grp.group_num == curr_gp->group_num &&
                curr_p->grp.year == curr_gp->year) {
            }
            ++curr_st_count;
        }
        if (curr_st_count > group_max) {
            group_max = MAX(group_max, curr_st_count);
            biggest_gr = curr_gp;
        }
    }

    if (biggest_gr != NULL) {
        printf("The biggest group is a group of a %d%s-year students #%d\n", biggest_gr->year,
               ENDING(biggest_gr->year), biggest_gr->group_num);
    }

    /* Final output */
    prt_ln();
}