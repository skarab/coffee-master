#ifdef COFFEE_OS_WINDOWS
#ifndef _COFFEE_CORE_PLATFORM_INCLUDES_WIN32_H_
#define _COFFEE_CORE_PLATFORM_INCLUDES_WIN32_H_

#ifndef _WIN32_WINDOWS
    #define _WIN32_WINDOWS 0x0502
#endif
#ifndef WINVER
    #define WINVER 0x0502
#endif

#include <windows.h>
#include <winbase.h>
#include <commctrl.h>
#include <direct.h>
#include <ks.h>
#include <ctype.h>
#include <csignal>
#include <tlhelp32.h>

#endif
#endif
