#ifndef HEADER_FILE_GETS
#define HEADER_FILE_GETS

#if SYSTEM == LINUX
#include <zconf.h>
#elif SYSTEM == WINDOWS
#include <Windows.h>
#endif
#define SIZE_BUF_GETS 1024

int lgets(char *);

#endif