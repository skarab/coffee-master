#ifndef _COFFEE_META_MACROS_TYPE_H_
#define _COFFEE_META_MACROS_TYPE_H_

#include "kernel/meta/macros/meta_macros_enum_h.h"

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_RegisterType
/// @brief Register the type into meta::Types, using static mechanism
//------------------------------------------------------------------------------------------------//
#define COFFEE_RegisterType(_export_statics_, _class_) \
    struct SRegisterType##_class_ \
    { \
        SRegisterType##_class_() \
        { \
            if (_export_statics_) \
                coffee::meta::Types::_AddTypeRegistration(&_class_::_RegisterType, &_class_::CreateObject); \
        } \
    }; \
    static SRegisterType##_class_ Type##_class_##Registered; \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_Type
/// @brief Export meta type functionnalities
//------------------------------------------------------------------------------------------------//
#define COFFEE_Type(_class_) \
    public: \
    static void _RegisterType(coffee::meta::Types::_TypeRegistration& type_to_register); \
    private: \
    static coffee::meta::Class* MetaType; \
    public: \
    virtual coffee::meta::Class& GetMetaType(); \
    virtual const coffee::meta::Class& GetMetaType() const; \
    static coffee::meta::Class& GetClassMetaType(); \
    static coffee::meta::Object* CreateObject(); \
    virtual coffee::meta::Object* CastObject(void* object) const; \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_BeginType
/// @brief Begin meta type declaration and implements basic functionnalities
/// @note Be carefull that it creates an instance of the class to retrieve the members offsets
//------------------------------------------------------------------------------------------------//
#define COFFEE_BeginType(_class_) \
    coffee::meta::Class* _class_::MetaType = NULL; \
     \
    coffee::meta::Class& _class_::GetMetaType() \
    { \
        return *MetaType; \
    } \
    const coffee::meta::Class& _class_::GetMetaType() const \
    { \
        return *MetaType; \
    } \
    coffee::meta::Class& _class_::GetClassMetaType() \
    { \
        return *MetaType; \
    } \
    coffee::meta::Object* _class_::CreateObject() \
    { \
        return (coffee::meta::Object *) COFFEE_New(_class_); \
    } \
    coffee::meta::Object* _class_::CastObject(void* object) const \
    { \
        return (_class_*)object; \
    } \
     \
    void _class_::_RegisterType(coffee::meta::Types::_TypeRegistration& type_to_register) \
    { \
        coffee::meta::Class* type; \
        _class_ temp_instance; \
        type = COFFEE_New(coffee::meta::Class); \
        type->SetName(#_class_); \
        type->SetSize(sizeof(_class_)); \
        type->SetCreationMethod(type_to_register.Create); \
        coffee::meta::Types::Get()._RegisterType(*type); \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_Ancestor
/// @brief Declare an ancestor of the class
/// @note Multiple inheritance is not allowed
//------------------------------------------------------------------------------------------------//
#define COFFEE_Ancestor(_type_) \
        type->SetAncestor(#_type_); \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_Attribute
/// @brief Declare an attribute of the class
/// @note _type_ is prefixed by '*' for pointers, and surrounded by '<>' for arrays
//------------------------------------------------------------------------------------------------//
#define COFFEE_Attribute(_type_, _name_, _mode_) \
        type->AddAttribute(\
            #_name_, \
            #_type_, \
            (ulong_ptr) &temp_instance._name_ - (ulong_ptr) &temp_instance, \
            _mode_, \
            NULL); \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_AttributeCustom
/// @brief Declare an attribute of the class using custom params
/// @note _type_ is prefixed by '*' for pointers, and surrounded by '<>' for arrays
/// @see meta::Param
//------------------------------------------------------------------------------------------------//
#define COFFEE_AttributeCustom(_type_, _name_, _param_) \
        type->AddAttribute(\
            #_name_, \
            #_type_, \
            (ulong_ptr) &temp_instance._name_ - (ulong_ptr) &temp_instance, \
            0, \
            _param_); \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_EndType
/// @brief End the meta type declaration
//------------------------------------------------------------------------------------------------//
#define COFFEE_EndType() \
        MetaType = type; \
    } \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_FindType
/// @brief Retrieve a meta type using its name
//------------------------------------------------------------------------------------------------//
#define COFFEE_FindType \
    coffee::meta::Types::Get().FindType

#endif
