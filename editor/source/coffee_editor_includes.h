#ifndef _COFFEE_EDITOR_INCLUDES_H_
#define _COFFEE_EDITOR_INCLUDES_H_

// Here is the list of all preprocessor definitions available:

/// @def COFFEE_EDITOR
/// @brief Compiling in DLL import mode

//-IMPORT-EXPORT----------------------------------------------------------------------------------//
#ifndef COFFEE_EDITOR
    #define COFFEE_EDITOR_API __declspec(dllexport)
    #define COFFEE_EDITOR_STATIC_API
    #define COFFEE_EDITOR_TEMPLATE_API __declspec(dllexport)
#else
    #define COFFEE_EDITOR_API
    #define COFFEE_EDITOR_STATIC_API __declspec(dllimport)
    #define COFFEE_EDITOR_TEMPLATE_API
#endif

#ifdef COFFEE_EDITOR
    #define COFFEE_EDITOR_EXPORT_STATICS false
#else
    #define COFFEE_EDITOR_EXPORT_STATICS true
#endif
//------------------------------------------------------------------------------------------------//

#include "coffee_editor_externals.h"
#include "coffee.h"

using namespace coffee;

#endif
