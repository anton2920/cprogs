#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAXSIZE 1024
#define NAME    21

/* Structure declaration */
struct goods {
    char name[NAME];
    int price;
};

/* Functions declarations */
void struct_init(struct goods *);
void prt_ln(void);
void no_cmd(void);
int quit_m(void);
int menu2(int *);
void menu2_5(int *);
void read_key(struct goods *, const int *);
int menu(int *);
int menu5(int *);
int rand_over(int *);
void read_rand(struct goods *, int *);
struct goods rand_goods(const int *, const int *, const int *);
int super_rand(const int *, const int *);
struct goods form_str(const char *, int);
void lstrcpy(const char *, char *);
int in_arr(const int *, const int *, const int *);
void init_arr(int *);
void read_file(struct goods *, int *);
int menu3(void);
struct goods min(const struct goods *, const int *);
struct goods max(const struct goods *, const int *);
void write_all_scr(const struct goods *, const int *);
void write_scr(const struct goods *, const struct goods *);
void write_file(const struct goods *, const struct goods *);
int menu4(void);

#endif