#ifndef LC_PROT_LCFU___SENDTO__C
#define LC_PROT_LCFU___SENDTO__C

#include <lcfu___sendto.h>

#ifdef __linux__
#include "impl/sendto_linux.c"
#elif _WIN32
#include "impl/sendto_windows.c"
#else
#error platform currently not supported
#endif

#endif
