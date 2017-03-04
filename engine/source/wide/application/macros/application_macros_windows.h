#ifndef _COFFEE_WIDE_APPLICATION_MACROS_WINDOWS_H_
#define _COFFEE_WIDE_APPLICATION_MACROS_WINDOWS_H_
#ifdef COFFEE_OS_WINDOWS

//-DEFINES----------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_BeginApplication
/// @brief Begin application, used internally by COFFEE_RegisterApplication
/// @see COFFEE_RegisterApplication
//------------------------------------------------------------------------------------------------//
#define COFFEE_BeginApplication(_interface_application_class_) \
    int32 CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR arguments, \
        int nCmdShow) \
    { \
        LPSTR command_line = GetCommandLine(); \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_EndApplication
/// @brief End application, used internally by COFFEE_RegisterApplication
/// @see COFFEE_RegisterApplication
//------------------------------------------------------------------------------------------------//
#define COFFEE_EndApplication(_interface_application_class_) \
        return 0; \
    } \

#endif
#endif
