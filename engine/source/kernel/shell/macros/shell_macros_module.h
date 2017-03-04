#ifndef _COFFEE_SHELL_MACROS_MODULE_H_
#define _COFFEE_SHELL_MACROS_MODULE_H_

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_RegisterModule
/// @brief Register module
//------------------------------------------------------------------------------------------------//
#define COFFEE_RegisterModule(_module_class_) \
    coffee::shell::ModuleManager::Get().Register(* COFFEE_New(_module_class_))

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_RegisterChildModule
/// @brief Register child module
//------------------------------------------------------------------------------------------------//
#define COFFEE_RegisterChildModule(_module_class_) \
    SendEvent(coffee::shell::Event(coffee::shell::EventCode(coffee::shell::MODULE_EVENT_Register, coffee::shell::Module::GetClassMetaType()), coffee::shell::EventParameters(NULL, COFFEE_New(_module_class_))));

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_RegisterChildModuleInstance
/// @brief Register child module instance
//------------------------------------------------------------------------------------------------//
#define COFFEE_RegisterChildModuleInstance(_module_instance_) \
    SendEvent(coffee::shell::Event(coffee::shell::EventCode(coffee::shell::MODULE_EVENT_Register, coffee::shell::Module::GetClassMetaType()), coffee::shell::EventParameters(NULL, _module_instance_)));

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_DeclareModuleSingleton
/// @brief Declare a singleton module
//------------------------------------------------------------------------------------------------//
#define COFFEE_DeclareModuleSingleton(_class_) \
        private: static _class_* _Instance; \
        public: static _class_& Get(); \
        public: static bool IsInstantiated(); \
        public: static bool IsAvailable(); \
        
//------------------------------------------------------------------------------------------------//
/// @def COFFEE_ImplementModuleSingleton
/// @brief Implement a singleton module
//------------------------------------------------------------------------------------------------//
#define COFFEE_ImplementModuleSingleton(_class_) \
    _class_* _class_::_Instance = NULL; \
    _class_& _class_::Get() { return *_Instance; } \
    bool _class_::IsInstantiated() { return (_Instance != NULL); } \
    bool _class_::IsAvailable() { return ((_Instance != NULL) && _Instance->IsModuleAvailable()); } \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_CreateModuleSingleton
/// @brief Create the singleton in the constructor
//------------------------------------------------------------------------------------------------//
#define COFFEE_CreateModuleSingleton(_singleton_) \
    COFFEE_Assert(_Instance == NULL, coffee::core::ERROR_CODE_IncorrectUsage, "An instance of " #_singleton_ " already exist."); \
    _Instance = this;

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_DestroyModuleSingleton
/// @brief Destroy the singleton in the destructor
//------------------------------------------------------------------------------------------------//
#define COFFEE_DestroyModuleSingleton(_singleton_) \
    _Instance = NULL;

#endif
