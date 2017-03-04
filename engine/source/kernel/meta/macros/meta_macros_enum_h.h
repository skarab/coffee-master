//------------------------------------------------------------------------------------------------//
/// Enum meta declaration macros (first pass processing)
//------------------------------------------------------------------------------------------------//

#undef COFFEE_BeginEnum
#undef COFFEE_EnumValue
#undef COFFEE_EndEnum

#ifdef COFFEE_EnumCPP
    #undef COFFEE_EnumCPP
#endif

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_BeginEnum
/// @brief Begin enum declaration
//------------------------------------------------------------------------------------------------//
#define COFFEE_BeginEnum(_namespace_, _enum_, _name_, _type_) \
    enum _enum_ \
    { \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_EnumValue
/// @brief Enum value declaration
//------------------------------------------------------------------------------------------------//
#define COFFEE_EnumValue(_enum_, _name_, _value_) \
    _enum_##_##_name_ = _value_, \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_EndEnum
/// @brief End enum declaration, add Count,None,Null values
//------------------------------------------------------------------------------------------------//
#define COFFEE_EndEnum(_export_api_, _export_statics_, _enum_) \
    _enum_##_Count, \
    _enum_##_None = -1, \
    _enum_##_Null = 0 \
    }; \
    \
    void _export_api_ _enum_##RegisterFunction(coffee::meta::Types::_TypeRegistration& type_to_register); \
    struct SRegisterEnum##_enum_ \
    { \
        SRegisterEnum##_enum_() \
        { \
            if (_export_statics_) \
                coffee::meta::Types::_AddTypeRegistration(&_enum_##RegisterFunction, NULL); \
        } \
    }; \
    static SRegisterEnum##_enum_ Enum##_enum_##Registered; \

