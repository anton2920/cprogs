#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAXSIZE 100

/* Functions declarations */
int menu1(void);
void prt_ln(void);
void to_bin(void);
int menu2(int *);
void menu2_5(int *);
void read_key(int *, const int *);
void read_rand(int *, const int *);
void read_file(int *, const int *);
void read_bfile(int *, const int *);
int menu3(void);
float a_mean (const int *, const int *, int *);
void write_all_scr(const int *, const int *);
void write_scr(const int *, const int *, const float *);
void write_file(const int *, const int *, const float *);
void write_bfile(const int *, const int *, const float *);
int menu4(void);


/* Array: arithmetic mean of even odd-positioned numbers */
int main() {

    /* Initializing variables */
    int mas[MAXSIZE], func, n, func1, func2;
    srand(time(NULL));
    float ar_mean;

    if ((func = menu1()) == 2) {
        to_bin();
    } else if (func == -1) {
        system("clear");
        return 0;
    } else {
        while (1) {
            switch (func1 = menu2(&n)) {
                case -1:
                    system("clear");
                    return 0;
                case 1:
                    read_key(mas, &n);
                    break;
                case 2:
                    read_rand(mas, &n);
                    break;
                case 3:
                    read_file(mas, &n);
                    break;
                case 4:
                    read_bfile(mas, &n);
                    break;
                default:
                    break;
            }

            func2 = menu3();

            /* Main part */
            ar_mean = a_mean(mas, &n, &func2);

            /* Final output */
            switch (func2) {
                case -1:
                    return 0;
                case 0:
                    write_all_scr(mas, &n);
                    write_scr(mas, &n, &ar_mean);
                    break;
                case 1:
                    write_all_scr(mas, &n);
                    write_scr(mas, &n, &ar_mean);
                    write_file(mas, &n, &ar_mean);
                    break;
                case 2:
                    write_all_scr(mas, &n);
                    write_scr(mas, &n, &ar_mean);
                    write_bfile(mas, &n, &ar_mean);
                    break;
                case 12: case 21:
                    write_all_scr(mas, &n);
                    write_scr(mas, &n, &ar_mean);
                    write_file(mas, &n, &ar_mean);
                    write_bfile(mas, &n, &ar_mean);
                    break;
                default:
                    break;
            }
            if (menu4()) {
                continue;
            } else {
                system("clear");
                return 0;
            }
        }
    }
}

/* Functions definitions */
int menu1(void) {

    /* Initializing variables */
    int func, junk;

    /* I/O flow */
    while (1) {
        printf(" ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n"
"|                                                            |\n"
"|                      >> MAIN MENU <<                       |\n"
"|                                                            |\n"
"|       1) Lab_13 #16                                        |\n"
"|       2) Convert .txt to .bin                              |\n"
"|                                                            |\n"
"|       >> Type \"quit\" to terminate this program <<          |\n"
"|                                                            |\n");
        printf("| Answer: ");
        func = getchar();
        prt_ln();
        if (isdigit(func) && func >= '1' && func <= '2') {
            func -= '0';
            while ((junk = getchar()) != '\n')
                ;
            return func;
        } else if (func == 'q') {
            return -1;
        } else {
            printf("| menu: no such command!                                     |\n");
            while ((junk = getchar()) != '\n')
                ;
            continue;
        }
    }
}

void prt_ln(void) {

    /* Final output */
    printf(" ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
}

void to_bin(void) {

    /* Initializing variables */
    int n, num, i;
    FILE *inputs, *outputs;
    char name[21], name2[21];

    /* I/O flow */
    menu2_5(&n);
    do {
        printf("| Type the name of a text file: ");
        scanf("%s", name);
        prt_ln();
        if ((inputs = fopen(name, "r")) == NULL) {
            prt_ln();
            printf("| to_bin: error, no file found!\n");
            prt_ln();
        } else {
            break;
        }
    } while (1);
    for (i = 0; (name2[i] = name[i]) != '.'; ++i)
        ;

    name2[++i] = 'b';
    name2[++i] = 'i';
    name2[++i] = 'n';
    name2[++i] = '\0';

    outputs = fopen(name2, "wb");
    if (outputs == NULL) {
        printf("| to_bin: error, couldn't open file!                        |\n");
        prt_ln();
        return;
    }

    /* Main part */
    for (i = 0; i < n; ++i) {
        fscanf(inputs, "%d", &num);
        fwrite(&num, sizeof(int), 1, outputs);
    }
    fclose(inputs);
    fclose(outputs);

    /* Final output */
    printf("| The «%s» file was created successfully!\n", name2);
    prt_ln();
}

int menu2(int *n) {

    /* Initializing variables */
    int func, junk;

    /* I/O flow */
    while (1) {
        printf(" ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n"
"|                                                            |\n"
"|                      >> Lab_13 #16 <<                      |\n"
"|                                                            |\n"
"|  >> Fill in an array with:                                 |\n"
"|                                                            |\n"
"|       1) Keyboard-typed numbers                            |\n"
"|       2) Pseudo-randomly generated numbers                 |\n"
"|       3) Containment of a text file                        |\n"
"|       4) Containment of a binary file                      |\n"
"|                                                            |\n"
"|       >> Type \"quit\" to terminate this program <<          |\n"
"|                                                            |\n");
        printf("| Answer: ");
        func = getchar();
        prt_ln();
        if (isdigit(func) && func >= '1' && func <= '4') {
            func -= '0';
            while ((junk = getchar()) != '\n')
                ;
            menu2_5(n);
            return func;
        } else if (func == 'q') {
            while ((junk = getchar()) != '\n')
                ;
            return -1;
        } else {
            printf("| menu: no such command!                                     |\n");
            while ((junk = getchar()) != '\n')
                ;
            continue;
        }
    }

}

void menu2_5(int *n) {

    /* I/O flow */
    printf("| Type the number of elements: ");
    scanf("%d", n);
    prt_ln();
}

void read_key(int *mas, const int *n) {

    /* Initializing variables */
    int i;

    /* Main part */
    for (i = 0; i < *n; ++i) {
        printf("| Type %d%s element: ", i, (i == 1) ? "st" : (i == 2) ? "nd" : (i == 3) ? "rd" : "th");
        scanf("%d", mas + i);
    }

    /* Final output */
    prt_ln();
}

void read_rand(int *mas, const int *n) {

    /* Initializing variables */
    int i, a, b, temp;

    /* Main part */
    printf("| Type «left» border of generation: ");
    scanf("%d", &a);
    printf("| Type «right» border of generation: ");
    scanf("%d", &b);
    if (a > b) {
        temp = b;
        b = a;
        a = temp;
    }
    for (i = 0; i < *n; ++i) {
        mas[i] = (rand() % (b - a + 1)) + a;
    }

    /* Final output */
    prt_ln();
}

void read_file(int *mas, const int *n) {

    /* Initializing variables */
    int i;
    FILE *inputs;
    char name[21];

    /* Main part */
    do {
        printf("| Type the name of a text file: ");
        scanf("%s", name);
    } while (!(inputs = fopen(name, "r")));
    for (i = 0; i < *n; ++i) {
        fscanf(inputs, "%d", mas + i);
    }
    fclose(inputs);

    /* Final output */
    prt_ln();
}

void read_bfile(int *mas, const int *n) {

    /* Initializing variables */
    int i;
    FILE *inputs;
    char name[21];

    /* Main part */
    do {
        printf("| Type the name of a binary file: ");
        scanf("%s", name);
    } while (!(inputs = fopen(name, "rb")));
    for (i = 0; i < *n; ++i) {
        fread(mas + i, sizeof(int), 1, inputs);
    }
    fclose(inputs);

    /* Final output */
    prt_ln();
}

int menu3(void) {

    /* Initializing variables*/
    int func, junk;

    /* I/O flow */
    while ((junk = getchar()) != '\n')
        ;
    while (1) {
        printf(" ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n"
"|                                                            |\n"
"|                      >> Lab_13 #16 <<                      |\n"
"|                                                            |\n"
"|  >> Occasional output?                                     |\n"
"|                                                            |\n"
"|       0) Screen only                                       |\n"
"|       1) To the text file                                  |\n"
"|       2) To the binary file                                |\n"
"|                                                            |\n"
"|       >> Type \"quit\" to terminate this program <<          |\n"
"|                                                            |\n");
        printf("| Answer: ");
        func = getchar();
        prt_ln();
        if (isdigit(func) && func >= '0' && func <= '2') {
            func -= '0';
            if ((junk = getchar()) != '\n') {
                if ((junk == '1' && func == 2) || (junk == '2' && func == 1)) {
                    func = (func * 10) + (junk - '0');
                    if ((junk = getchar()) != '\n') {
                        while ((junk = getchar()) != '\n');
                        return -1;
                    }
                } else {
                    while ((junk = getchar()) != '\n')
                        ;
                }
            }
            return func;
        } else if (func == 'q') {
            while ((junk = getchar()) != '\n')
                ;
            return -1;
        } else {
            printf("| menu: no such command!                                     |\n");
            while ((junk = getchar()) != '\n')
                ;
            continue;
        }
    }

}

float a_mean(const int *mas, const int *n, int *func) {

    /* Initializing variables */
    int i, sum = 0, count = 0;
    float ar_mean = 0;

    /* Main part */
    for (i = 0; i < *n; i += 2) {
        if (*(mas + i) % 2 == 0) {
            sum += *(mas + i);
            ++count;
        }
    }

    if (count == 0) {
        *func = -2;
    } else {
        ar_mean = sum * 1.0 / count * 1.0;
    }

    /* Returning value */
    return ar_mean;

}

void write_all_scr(const int *mas, const int *n) {

    /* Initializing variables */
    int i;

    /* I/O flow */
    printf("| Full array: ");
    for (i = 0; i < *n; ++i) {
        printf("%d ", *(mas + i));
    }

    /* Final output */
    printf("\n");
    prt_ln();
}

void write_scr(const int *mas, const int *n, const float *ar_mean) {

    /* Initializing variables */
    int i;

    /* Main part */
    printf("| Arithmetic mean: %6.2f                                    |\n", *ar_mean);
    printf("| Array: ");
    for (i = 0; i < *n; ++i) {
        if (*(mas + i) > *ar_mean) {
            printf("%d ", *(mas + i));
        }
    }
    printf("\n ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
}

void write_file(const int *mas, const int *n, const float *ar_mean) {

    /* Initializing variables */
    int i;
    FILE *outputs;

    /* Main part */
    outputs = fopen("a1out.txt", "w");
    if (outputs == NULL) {
        printf("| txt: error, couldn't open file!                            |\n");
        prt_ln();
        return;
    }
    fprintf(outputs, "%.2f\n", *ar_mean);
    for (i = 0; i < *n; ++i) {
        if (*(mas + i) > *ar_mean) {
            fprintf(outputs, "%d ", *(mas + i));
        }
    }
    fclose(outputs);

    /* Final output */
    printf("| txt: the information was stored successfully!              |\n");
    prt_ln();
}

void write_bfile(const int *mas, const int *n, const float *ar_mean) {

    /* Initializing variables */
    int i;
    FILE *outputs;

    /* Main part */
    outputs = fopen("a1out.bin", "wb");
    if (outputs == NULL) {
        printf("| bin: error, couldn't open file!                            |\n");
        prt_ln();
        return;
    }
    fwrite(&ar_mean, sizeof(float), 1, outputs);
    for (i = 0; i < *n; ++i) {
        if (*(mas + i) > *ar_mean) {
            fwrite(mas + i, sizeof(int), 1, outputs);
        }
    }
    fclose(outputs);

    /* Final output */
    printf("| bin: the information was stored successfully!              |\n");
    prt_ln();
}

int menu4(void) {

    /* Initializing variables */
    int func, junk;

    /* I/O flow */
    while (1) {
        printf("| Continue? [y/N]: ");
        switch ((func = getchar())) {
            case 'y': case 'Y':
                while ((junk = getchar()) != '\n')
                    ;
                prt_ln();
                return 1;
            case 'n': case 'N': case '\n':
                prt_ln();
                return 0;
            default:
                while ((junk = getchar()) != '\n')
                    ;
                prt_ln();
                continue;
        }
    }
}