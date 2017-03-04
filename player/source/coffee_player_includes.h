#ifndef _COFFEE_PLAYER_INCLUDES_H_
#define _COFFEE_PLAYER_INCLUDES_H_

// Here is the list of all preprocessor definitions available:

/// @def COFFEE_PLAYER
/// @brief Compiling in DLL import mode

//-IMPORT-EXPORT----------------------------------------------------------------------------------//
#ifndef COFFEE_PLAYER
    #define COFFEE_PLAYER_API __declspec(dllexport)
    #define COFFEE_PLAYER_STATIC_API
    #define COFFEE_PLAYER_TEMPLATE_API __declspec(dllexport)
#else
    #define COFFEE_PLAYER_API
    #define COFFEE_PLAYER_STATIC_API __declspec(dllimport)
    #define COFFEE_PLAYER_TEMPLATE_API
#endif

#ifdef COFFEE_PLAYER
    #define COFFEE_PLAYER_EXPORT_STATICS false
#else
    #define COFFEE_PLAYER_EXPORT_STATICS true
#endif
//------------------------------------------------------------------------------------------------//

#include "coffee.h"

using namespace coffee;

#endif
