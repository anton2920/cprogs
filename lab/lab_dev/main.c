#include <stdio.h>
#include <assert.h>

#define ENDING(x) (((x) == 1) ? "st" : ((x) == 2) ? "nd" : ((x) == 3) ? "rd" : "th")

enum sizes {
    LAST_NAME_SIZE = 20,
    NSCORES = 5,
    NTABLEROWS = 5
};

typedef int id_t;

typedef struct table_elem {
    id_t id;
    char last_name[LAST_NAME_SIZE];
    int score[NSCORES];
} table_elem_t;

typedef table_elem_t table[NTABLEROWS];

void read_table_elem(table_elem_t *e);

main()
{
    /* Initializing variables */
    FILE *fp;
    register size_t i;
    table t, t1 = {};

    /* Main part */
    /*fp = fopen("database.dat", "wb");
    assert(fp != NULL);
    for (i = 0; i < NTABLEROWS; ++i) {
        read_table_elem(t + i);
    }

    fwrite(&t, sizeof(table_elem_t), NTABLEROWS, fp);
    fclose(fp);*/

    /* Reading */
    fp = fopen("database.dat", "rb");
    fseek(fp, 3 * sizeof(table_elem_t), SEEK_SET);
    size_t nread = fread(&t1, sizeof(table_elem_t), NTABLEROWS, fp);

    for (i = 0; i < NTABLEROWS; ++i) {
        printf("ID: %d; Last name: %s; Score#1: %d; Score #2: %d; Score#3: %d; Score #4: %d; Score#5: %d;\n",
               (t1 + i)->id, (t1 + i)->last_name, (t1 + i)->score[0], (t1 + i)->score[1], (t1 + i)->score[2],
               (t1 + i)->score[3], (t1 + i)->score[4]);
    }
    printf("\nRead %lu bytes\n", nread * sizeof(table_elem_t));
    fclose(fp);
}

void read_table_elem(table_elem_t *e)
{
    /* Initializing variables */
    static id_t last_id = 0;
    register size_t i;

    /* I/O flow */
    printf("Type last name: ");
    scanf("%s", e->last_name);

    for (i = 0; i < NSCORES; ++i) {
        printf("Type %lu%s score: ", i + 1, ENDING(i + 1));
        scanf("%d", e->score + i);
    }
    e->id = last_id++;

    /* Final output */
    printf("\n");
}
