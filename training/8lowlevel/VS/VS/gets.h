#ifndef HEADER_FILE_GETS
#define HEADER_FILE_GETS

#if SYSTEM == _WIN32 || SYSTEM == OS_Windows
	#define SYSCALLS <Windows.h>
#elif SYSTEM == __unix__
	#define SYSCALLS <zconf.h>
#endif
#include SYSCALLS

#define SIZE_BUF_GETS 1024

#endif