#ifndef LOWLEVELFILE_LLFILE_H
#define LOWLEVELFILE_LLFILE_H

#include <zconf.h>

#define BUFSIZE 1024
#define EOF (-1)

int lgetchar(void);
void lputchar(int);
int lisnum(int *);
int lisspace(int);
int linput(const char *, int, long int *);
int input(const char *, int, int *);
void read_mas_key(int *, int *);
int write_str_scr(const char *, int);
int numlength(int);
char *reverse(int, int);
int write_int_scr(const int *);
void write_mas_scr(const int *, const int *);

#endif //LOWLEVELFILE_LLFILE_H
