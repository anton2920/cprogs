#ifndef HEADER_FILE_GETS
#define HEADER_FILE_GETS

#ifdef _WIN32
#include <io.h>
#endif

#ifdef __unix__
#include <zconf.h>
#endif

#define SIZE_BUF_GETS 1024

int lgets(char *);

#endif