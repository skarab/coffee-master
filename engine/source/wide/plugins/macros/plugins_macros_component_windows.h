#ifdef COFFEE_OS_WINDOWS
#ifndef _COFFEE_PLUGINS_COMPONENT_MACROS_H_
#define _COFFEE_PLUGINS_COMPONENT_MACROS_H_

//-MACROS-----------------------------------------------------------------------------------------//

#define COMPONENT_API __declspec(dllexport)
#define COFFEE_RegisterComponent(_type_) COFFEE_RegisterType(true, _type_)

#define COFFEE_ExportComponent(_namespace_) \
    extern int32 WINAPI DllMain(HINSTANCE instance, uint32 reason, void* reserved) \
    { \
        switch (reason) \
        { \
            case DLL_PROCESS_ATTACH: \
                COFFEE_Assert(plugins::Object::_Loading==NULL, core::ERROR_CODE_Unexpected, "Bad plugin behavior"); \
                plugins::ComponentLibrary* plugin = COFFEE_New(plugins::ComponentLibrary); \
                plugin->_Initialize(); \
                plugin->Register<_namespace_::Component>(); \
                plugins::Object::_Loading = plugin; \
                break; \
        } \
        return 1; \
    } \

#endif
#endif
