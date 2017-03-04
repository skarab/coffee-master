#ifdef COFFEE_OS_WINDOWS
#ifndef _COFFEE_PLUGINS_MACROS_WINDOWS_H_
#define _COFFEE_PLUGINS_MACROS_WINDOWS_H_

//-MACROS-----------------------------------------------------------------------------------------//

#define COFFEE_RegisterPlugin(_class_) \
    extern int32 WINAPI DllMain(HINSTANCE instance, uint32 reason, void* reserved) \
    { \
        switch (reason) \
        { \
            case DLL_PROCESS_ATTACH: \
                COFFEE_Assert(plugins::Object::_Loading==NULL, core::ERROR_CODE_Unexpected, "Bad plugin behavior"); \
                _class_* plugin = COFFEE_New(_class_); \
                plugin->_Initialize(); \
                plugins::Object::_Loading = plugin; \
                break; \
        } \
        return 1; \
    } \

#endif
#endif
