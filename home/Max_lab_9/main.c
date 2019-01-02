/* Includes */
#include <stdio.h>
#include <string.h>

/* Macros */
#define NAME (20)
#define DIRECT_EXT (".dat")
#define SEQ_EXT (".txt")
#define RECS_MIN (2)

/* Structure declaration */
struct autopark {
    char name[NAME]; /* Car name */
    int moshnost; /* HP (kW) */
    int probeg; /* Odometer's data */
    int remont; /* 0 || 1 */
};

/* Function declarations */
void prt_ln(void);
int num_of_elem(void);
void write_file(int, int);
void read_file(int, int);

/* Main function */
main() {

    /* Initializing variables */
    int func, func2, n;

    /* I/O flow && VarCheck */
    do {
        printf("Choose sh**t:\n"
               "1) Write to file\n"
               "2) Read from file\n"
               "3) Read from file considering rule\n"
               "Answer: ");
        scanf("%d", &func);
    } while (func < 1 || func > 3);
    prt_ln();
    do {
        printf("Choose sh**t #2:\n"
               "1) Sequential access\n"
               "2) Direct access\n"
               "Answer: ");
        scanf("%d", &func2);
    } while (func2 < 1 || func2 > 2);
    prt_ln();

    /* Main part */
    --func2;
    switch (func) {
        case 1:
            n = num_of_elem();
            if (!func2) {
                write_file(n, 0);
            } else {
                write_file(n, 1);
            }
            break;
        case 2:
            if (!func2) {
                read_file(0, 0);
            } else {
                read_file(1, 0);
            }
            break;
        case 3:
            if (!func2) {
                read_file(0, 1);
            } else {
                read_file(1, 1);
            }
            break;
        default:
            break;
    }

    /* Final output */
    prt_ln();
}

/* Function definitions */
void prt_ln(void) {

    /* Final output */
    printf("––––––––––––––––––––––––––––––––––––\n");
}

int num_of_elem(void) {

    /* Initializing variables */
    int num;

    /* I/O flow */
    do {
        printf("Type the number of records: ");
        scanf("%d", &num);
        if (num < RECS_MIN) {
            fprintf(stderr, "Error! The number of records can't be less than 10\n");
        }
    } while (num < RECS_MIN);

    /* Final output */
    prt_ln();

    /* Returning value */
    return num;
}

void write_file(int n, int bfile) {

    /* Initializing variables */
    struct autopark mas;
    char name[NAME];
    int i;
    FILE *fp = NULL;

    /* I/O flow && VarCheck */
    do {
        printf("Type a filename: ");
        scanf("%s", name);
        if (!bfile && strstr(name, SEQ_EXT)) {
            fp = fopen(name, "w");
        } else if (strstr(name, DIRECT_EXT)) {
            fp = fopen(name, "wb");
        } else {
            fprintf(stderr, "Error! Bad filename!");
        }

    } while (!fp);

    for (i = 0; i < n; ++i) {
        prt_ln();
        printf("Type car's name: ");
        scanf("%s", mas.name);
        printf("Type car's engine power: ");
        scanf("%d", &mas.moshnost);
        printf("Type car's odometer data: ");
        scanf("%d", &mas.probeg);
        printf("Type whether car's engine were in capital repair [0 | 1]: ");
        scanf("%d", &mas.remont);
        if (!bfile) {
            fprintf(fp, "%s\t%d\t%d\t%d%s", mas.name, mas.moshnost, mas.probeg, mas.remont, (i == n - 1) ? "" : "\n");
        } else {
            fwrite(&mas, sizeof(mas), 1, fp);
        }
    }

    fclose(fp);
}

void read_file(int bfile, int rule) {

    /* Initializing variables */
    struct autopark mas;
    char name[NAME];
    int i, ext = 1;
    FILE *fp;

    /* I/O flow && VarCheck */
    do {
        printf("Type a filename: ");
        scanf("%s", name);
        if (!bfile && strstr(name, SEQ_EXT)) {
            fp = fopen(name, "r");
        } else if (strstr(name, DIRECT_EXT)) {
            fp = fopen(name, "rb");
        } else {
            fprintf(stderr, "Error! Bad filename!");
            return;
        }

    } while (!fp);

    prt_ln();
    for (i = 0; !feof(fp); ) {
        if (!bfile) {
            fscanf(fp, "%s\t%d\t%d\t%d", mas.name, &mas.moshnost, &mas.probeg, &mas.remont);
        } else {
            ext = (int) fread(&mas, sizeof(mas), 1, fp);
            if (!ext) {
                break;
            }
        }
        if (!rule || (rule && mas.probeg > 100000 && mas.remont == 0)) {
            printf("%s\t%d\t%d\t%d\n", mas.name, mas.moshnost, mas.probeg, mas.remont);
            ++i;
        }
    }

    if (!i) {
        printf("Error! No records were found!\n");
    }

    fclose(fp);
}