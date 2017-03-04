//------------------------------------------------------------------------------------------------//
// Singleton macros enforce that the class can't be instantiated more than once, by throwing an
// error in case of incorrect usage.
//
// Put COFFEE_DeclareSingleton in the header, COFFEE_ImplementSingleton in the cpp,
// and COFFEE_CreateSingleton / COFFEE_DestroySingleton in the contructors / destructor.
// The instance may be retrieved using _class_::Get()
//------------------------------------------------------------------------------------------------//
#ifndef _COFFEE_CORE_MACROS_SINGLETON_H_
#define _COFFEE_CORE_MACROS_SINGLETON_H_

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_DeclareSingleton
/// @brief Declare singleton class
//------------------------------------------------------------------------------------------------//
#define COFFEE_DeclareSingleton(_class_) \
    private: static _class_* _Instance; \
    public: static _class_& Get(); \
    public: static bool IsInstantiated();

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_ImplementSingleton
/// @brief Implement singleton class
//------------------------------------------------------------------------------------------------//
#define COFFEE_ImplementSingleton(_class_) \
    _class_* _class_::_Instance = NULL; \
    _class_& _class_::Get() { return *_Instance; } \
    bool _class_::IsInstantiated() { return (_Instance != NULL); }

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_CreateSingleton
/// @brief Constructor of the singleton
//------------------------------------------------------------------------------------------------//
#define COFFEE_CreateSingleton(_singleton_) \
    COFFEE_Assert(_Instance==NULL, coffee::core::ERROR_CODE_IncorrectUsage, \
        "An instance of " #_singleton_ " already exist."); \
    _Instance = this;

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_DestroySingleton
/// @brief Destructor of the singleton
//------------------------------------------------------------------------------------------------//
#define COFFEE_DestroySingleton(_singleton_) \
    COFFEE_Assert(_Instance!=NULL, coffee::core::ERROR_CODE_IncorrectUsage, \
        "Destroying invalid instance of " #_singleton_); \
    _Instance = NULL;

#endif
