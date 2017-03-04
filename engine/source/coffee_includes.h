#ifndef _COFFEE_INCLUDES_H_
#define _COFFEE_INCLUDES_H_

// Here is the list of all preprocessor definitions available:

/// @def COFFEE_ENGINE
/// @brief Compiling in DLL import mode

/// @def COFFEE_DEBUG
/// @brief Compiling in debug mode

/// @def COFFEE_RELEASE
/// @brief Compiling in release mode

/// @def COFFEE_OS_WINDOWS
/// @brief Compiling for Windows

/// @def COFFEE_OS_UNIX
/// @brief Compiling for Unix (future use)

// Disable annoying warnings
#pragma warning(disable:4251)   // dll templates interfaces ("needs to have dll-interface to be used by clients of class")
#pragma warning(disable:4275)   // missing dll import (required to fix vtable hell)

//-IMPORT-EXPORT----------------------------------------------------------------------------------//
#ifndef COFFEE_ENGINE
    #define COFFEE_API __declspec(dllexport)
    #define COFFEE_STATIC_API
    #define COFFEE_TEMPLATE_API __declspec(dllexport)
#else
    #define COFFEE_API 
    #define COFFEE_STATIC_API __declspec(dllimport)
    #define COFFEE_TEMPLATE_API
#endif

#ifdef COFFEE_ENGINE
    #define COFFEE_EXPORT_STATICS false
#else
    #define COFFEE_EXPORT_STATICS true
#endif
//------------------------------------------------------------------------------------------------//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <malloc.h>
#include <vector>
#include "coffee_mode.h"
#include "kernel/kernel_macros.h"
#include "system/system_macros.h"
#include "wide/wide_macros.h"

#endif
