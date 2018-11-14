#include <stdio.h>

/* Number sequence */
int main() {

    /* Initializing variables */
    int mem, min1 = 0, min2 = 0, dist = 0, max_dist = 0, flag = 0, prev_mem, next_mem = 0, min_flag = 0;

    /* Main part */
    printf("Type a sequence member (zero for exit): ");
    scanf("%d", &prev_mem);
    if (!prev_mem) {
        return 0;
    }
    printf("Type a sequence member (zero for exit): ");
    scanf("%d", &mem);
    if (!mem) {
        return 0;
    } else if (mem > prev_mem) {
        flag = 1;
    } else if (mem < prev_mem) {
        flag = 2;
    }
    do {
        printf("Type a sequence member (zero for exit): ");
        scanf("%d", &next_mem);
        if (!next_mem) {
            break;
        }
        if ((next_mem > mem && flag == 2) || (next_mem < mem && flag == 1) || next_mem == mem) {
            flag = -1;
        } else if (next_mem > mem && flag != -1) {
            flag = 1;
        } else if (next_mem < mem && flag != -1) {
            flag = 2;
        }
        if (min_flag) {
            ++dist;
        }
        if (mem < prev_mem && mem < next_mem && !min_flag) {
            min1 = mem;
            min_flag = 1;
        } else if (mem < prev_mem && mem < next_mem && min_flag) {
            min2 = mem;
            if (dist > max_dist) {
                max_dist = dist;
            }
        }

        prev_mem = mem;
        mem = next_mem;

    } while (1);

    /* Final output */
    if (flag != -1) {
        printf("%s", (flag == 1) ? "The sequence in an ascending order\n" : (flag == 2) ? "The sequence in an descending order" : "All members of the sequence are equal");
    } else {
        printf("The distance between two local lows (%d and %d):  %d\n", min1, min2, max_dist - 1);
    }

    /* Returning value */
    return 0;
}