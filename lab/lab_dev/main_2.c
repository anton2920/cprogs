#include <stdio.h>
#include <assert.h>

typedef struct plank_section {
    int left;
    int right;
} plank_section_t;

unsigned char plank_section_merge(plank_section_t *self, plank_section_t *other) {

    /* Initializing variables */
    plank_section_t *left, *right;

    if (self->left <= other->left) {
        left = self;
        right = other;
    } else {
        right = self;
        left = other;
    }

    if (right->left - left->right < 2) {
        if (left->right < right->right) {
            left->right = right->right;
        }
    } else {
        return 0;
    }

    return 1;
}

void plank_section_try_to_merge_stash(plank_section_t *self, plank_section_t *stash, size_t stash_size) {

    /* Initializing variables */
    int i, j;
    unsigned char status;

    for (i = 0, status = 0; i < stash_size; ++i) {
        for (j = 0; j < stash_size; ++j) {
            status |= plank_section_merge(self, &stash[j]);
        }

        if (status) {
            status = 0;
        } else {
            break;
        }
    }
}

int main() {

    /* Initializing variables */
    FILE *fin, *fout;

    int planks, days;
    int i;

    plank_section_t result, current;

    plank_section_t stash[1000];
    int current_stash_place = 0;

    /* Main part */
    fin = fopen("input.in", "r");
    fout = fopen("output.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d %d", &planks, &days);

    fscanf(fin, "%d %d", &current.left, &current.right);
    result = current;

    for (i = 0; i < days; ++i) {
        fscanf(fin, "%d %d", &current.left, &current.right);
        if (!plank_section_merge(&result, &current)) {
            stash[current_stash_place++] = current;
        }
    }

    plank_section_try_to_merge_stash(&result, stash, current_stash_place);

    if (result.left == 1 && result.right == planks) {
        fprintf(fout,"YES");
    } else {
        fprintf(fout, "NO");
    }

    fclose(fin);
    fclose(fout);
}