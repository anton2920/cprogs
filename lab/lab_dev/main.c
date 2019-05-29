#include <stdio.h>
#include <STL.h>
#include <string.h>

#define SIZE (50)
#define CSIZE (20)


/* New data types */
struct person {
    char last_name[SIZE];
    char course[CSIZE];
    int group_num;
    int score[5];
};


/* Function declarations */
void prt_ln(void);

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
        printf("Type a student's last name (type «0» to exit): ");
        scanf("%s", p.last_name);
        if (!strcmp("0", p.last_name)) {
            printf("Exiting...\n");
            return 0;
        }
        printf("Type a course: ");
        scanf("%s", p.course);
        do {
            printf("Type a group number: ");
            scanf("%d", &p.group_num);
        } while (p.group_num < 0);


    } while (1);

    /* Returning value */
    return 0;
}

void prt_ln(void) {

    /* Final output */
    printf(" -----------------------------------------------------------\n");
}