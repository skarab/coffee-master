#ifndef _COFFEE_WIDE_APPLICATION_MACROS_H_
#define _COFFEE_WIDE_APPLICATION_MACROS_H_

#include "wide/application/macros/application_macros_windows.h"
#include "wide/application/macros/application_macros_unix.h"

//-DEFINES----------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_RegisterApplication
/// @brief Register the application module
///
/// This is needed one time per project.
/// It will register your application, and launch the Coffee engine.
///
/// @param[in] _interface_application_class_ Your Application class
/// @param[in] _debug_modes_ The debug modes you want
///
/// @see coffee::Application, coffee_debug.h
//------------------------------------------------------------------------------------------------//
#define COFFEE_RegisterApplication(_interface_application_class_, _debug_modes_) \
    COFFEE_BeginApplication(_interface_application_class_) \
        coffee::Engine engine(command_line, _debug_modes_); \
        if (engine.Update()) \
        { \
            COFFEE_RegisterModule(_interface_application_class_); \
            while(engine.Update()); \
        } \
    COFFEE_EndApplication(_interface_application_class_); \

#endif
