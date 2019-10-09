#include <stdio.h>
#include <string.h>

#include "libs.h"

void read_polynomials(STL_List *l, FILE *fp) {

    /* Initializing variables */
    auto struct poly tmp, *curr;
    auto STL_List_node *iter;

    /* Main part */
    for (;;) {
        if (fp == stdin) {
            printf("Type coefficient: ");
            scanf("%d", &tmp.coefficient);
            printf("Type power («0» indicates last member): ");
            scanf("%lu", &tmp.power);
            printf("\n");

            if (!tmp.coefficient) {
                continue;
            }
        } else {
            if (feof(fp)) {
                break;
            }

            fscanf(fp, "%d %lu\n", &tmp.coefficient, &tmp.power);

            if (!tmp.coefficient) {
                continue;
            }
        }
        if (tmp.power && STL_List_begin(l) != NULL) {
            for (iter = STL_List_begin(l); iter != NULL; iter = iter->next) {
                curr = (struct poly *) iter->value;
                if (curr->power < tmp.power) {
                    STL_List_insert(l, &tmp, sizeof(struct poly), iter);
                    break;
                } else if (curr->power == tmp.power) {
                    curr->coefficient += tmp.coefficient;
                    break;
                } else if (iter == STL_List_end(l)) {
                        STL_List_push_back(l, &tmp, sizeof(struct poly));
                        break;
                }
            }
        } else if (STL_List_begin(l) == NULL) {
            STL_List_push_back(l, &tmp, sizeof(struct poly));
        } else {
            STL_List_push_back(l, &tmp, sizeof(struct poly));
            break;
        }
    }
}

void print_polynomials(STL_List *l, FILE *fp) {

    /* Initializing variables */
    auto STL_List_node *iter;
    auto struct poly *tmp;

    /* Main part */
    for (iter = STL_List_begin(l); iter != NULL; iter = iter->next) {
        tmp = (struct poly *) iter->value;
        if (tmp->power) {
            fprintf(fp, "%dx ^ %lu %s", tmp->coefficient, tmp->power, (iter->next == NULL) ? "\n" : "+ ");
        } else {
            fprintf(fp, "%d\n", tmp->coefficient);
        }
    }
}

void add_polynomials(STL_List *result, STL_List *this, STL_List *other) {

    /* Initializing variables */
    auto STL_List_node *i1, *i2, *iend;
    auto struct poly *p1, *p2, *pend, res;

    /* Main part */
    for (i1 = STL_List_begin(this), i2 = STL_List_begin(other); i1 != NULL && i2 != NULL; ) {
        p1 = (struct poly *) i1->value;
        p2 = (struct poly *) i2->value;

        if (p1->power > p2->power) {
            STL_List_push_back(result, p1, sizeof(struct poly));
            i1 = i1->next;
        } else if (p1->power < p2->power) {
            STL_List_push_back(result, p2, sizeof(struct poly));
            i2 = i2->next;
        } else {
            res.power = p1->power;
            res.coefficient = p1->coefficient + p2->coefficient;
            STL_List_push_back(result, &res, sizeof(struct poly));
            i1 = i1->next;
            i2 = i2->next;
        }
    }

    for (iend = (i1 == NULL) ? i2 : i1; iend != NULL; iend = iend->next) {
        pend = (struct poly *) iend->value;
        STL_List_push_back(result, pend, sizeof(struct poly));
    }
}

void multiply_polynomials(STL_List *result, STL_List *this, STL_List *other) {

    /* Initializing variables */
    auto STL_List_node *i1, *i2, *iter;
    auto struct poly *p1, *p2, res, *curr;

    /* Main part */
    for (i1 = STL_List_begin(this); i1 != NULL; i1 = i1->next) {
        for (i2 = STL_List_begin(other); i2 != NULL; i2 = i2->next) {
            p1 = (struct poly *) i1->value;
            p2 = (struct poly *) i2->value;

            res.coefficient = p1->coefficient * p2->coefficient;
            res.power = p1->power + p2->power;

            if (res.power && STL_List_begin(result) != NULL) {
                for (iter = STL_List_begin(result); iter != NULL; iter = iter->next) {
                    curr = (struct poly *) iter->value;
                    if (curr->power < res.power) {
                        STL_List_insert(result, &res, sizeof(struct poly), iter);
                        break;
                    } else if (curr->power == res.power) {
                        curr->coefficient += res.coefficient;
                        break;
                    } else if (iter == STL_List_end(result)) {
                        STL_List_push_back(result, &res, sizeof(struct poly));
                        break;
                    }
                }
            } else if (STL_List_begin(result) == NULL) {
                STL_List_push_back(result, &res, sizeof(struct poly));
            } else {
                STL_List_push_back(result, &res, sizeof(struct poly));
            }
        }
    }
}