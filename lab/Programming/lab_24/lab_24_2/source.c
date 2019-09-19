#include "source.h"

bool create_st_l(struct group_l *arr) {

    /* Initializing variables */
    register int i;

    /* I/O flow */
    if ((arr->mas = (struct student **) malloc(arr->number * sizeof(struct student *))) != NULL) {
        for (i = 0; i < arr->number; ++i) {
            if ((arr->mas[i] = (struct student *) malloc(sizeof(struct student))) != NULL) {
                if ((arr->mas[i]->mks_pt = (int *) malloc(INT_MAX)) == NULL) {
                    return false;
                }
            } else {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }

}

bool read_stuff(struct group_l *arr) {

    /* Initializing variables */

    /* I/O flow */
    do {
        printf("Type the number of students: ");
        scanf("%d", &arr->number);
    } while (arr->number <= 0);

    if (create_st_l(arr) == true) {
        read_arr(arr);
    } else {
        arr_err();
        return false;
    }

    /* Returning value */
    return true;
}

void arr_err(void) {

    /* Final output */
    fprintf(stderr, "Error! Allocating problems!");
}

void read_arr(struct group_l *arr) {

    /* Initializing variables */
    register int i, j;

    /* I/O flow */
    for (i = 0; i < arr->number; ++i) {
        printf("Type marks of a %d%s student: ", i, (i == 1) ? "st" : (i == 2) ? "nd" : (i == 3) ? "rd" : "th");
        arr->mas[i]->gs_mks = true;
        arr->mas[i]->ar_mean = 0;
        for (j = 0; ; ++j) {
            do {
                scanf("%d", &arr->mas[i]->mks_pt[j]);
                if (!arr->mas[i]->mks_pt[j]) {
                    break;
                }
                if (arr->mas[i]->mks_pt[j] < 2 || arr->mas[i]->mks_pt[j] > 5) {
                    printf("Error! Wrong mark!\n");
                }
            } while (arr->mas[i]->mks_pt[j] < 2 || arr->mas[i]->mks_pt[j] > 5);
            if (!arr->mas[i]->mks_pt[j]) {
                break;
            } else {
                arr->mas[i]->ar_mean += arr->mas[i]->mks_pt[j];
                if (arr->mas[i]->mks_pt[j] < 4) {
                    arr->mas[i]->gs_mks = false;
                }
            }
        }
        arr->mas[i]->num_of_mks = j;
        arr->mas[i]->mks_pt = realloc(arr->mas[i]->mks_pt, j * sizeof(int));
        arr->mas[i]->lt3 = (arr->mas[i]->num_of_mks < 3) ? true : false;
        arr->mas[i]->ar_mean /= arr->mas[i]->num_of_mks;

    }

    /* Final output */
    printf("\n");
}

void find_ar_mean(struct group_l *arr) {

    /* Initializing variables */
    register int i;
    double ar_m = 0;

    /* Main part */
    for (i = 0; i < arr->number; ++i) {
        ar_m += arr->mas[i]->ar_mean;
    }

    ar_m /= arr->number;

    /* Final output */
    printf("Arithmetic mean: %.2lf\n", ar_m);
}

void find_lt3(struct group_l *arr) {

    /* Initializing variables */
    register int i;
    int lt3_num = 0;

    for (i = 0; i < arr->number; ++i) {
        lt3_num += (arr->mas[i]->lt3 == true) ? 1 : 0;
    }

    /* Final output */
    printf("The number of students with less than three marks: %d\n", lt3_num);
}

void find_gs_mks(struct group_l *arr) {

    /* Initializing variables */
    register int i;
    int gs_mks_num = 0;

    /* Main part */
    for (i = 0; i < arr->number; ++i) {
        gs_mks_num += (arr->mas[i]->gs_mks == true) ? 1 : 0;
    }

    /* Final output */
    printf("The number of students with «positive» marks: %d\n", gs_mks_num);
}

void delete_arr(struct group_l *arr) {

    /* Initializing variables */
    register int i;

    /* Main part */
    for (i = 0; i < arr->number; ++i) {
        free(arr->mas[i]->mks_pt);
        free(arr->mas[i]);
    }
    free(arr->mas);
}