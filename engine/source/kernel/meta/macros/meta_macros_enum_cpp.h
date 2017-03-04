//------------------------------------------------------------------------------------------------//
// Enum meta declaration macros (second pass processing)
//------------------------------------------------------------------------------------------------//

#undef COFFEE_BeginEnum
#undef COFFEE_EnumValue
#undef COFFEE_EndEnum

#define COFFEE_EnumCPP

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_BeginEnum
/// @brief Register the enum type
//------------------------------------------------------------------------------------------------//
#define COFFEE_BeginEnum(_namespace_, _enum_, _name_, _type_) \
    void _enum_##RegisterFunction(coffee::meta::Types::_TypeRegistration& object_to_register) \
    { \
        coffee::meta::Enum* enum_type; \
        enum_type = COFFEE_New(coffee::meta::Enum, #_namespace_ "::" #_enum_, coffee::basic::String(_name_), coffee::meta::ENUM_TYPE_##_type_); \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_EnumValue
/// @brief Register an enum value
//------------------------------------------------------------------------------------------------//
#define COFFEE_EnumValue(_enum_, _name_, _value_) \
        enum_type->AddValue(basic::String(#_name_), _value_); \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_EndEnum
/// @brief Finalize enum registration
//------------------------------------------------------------------------------------------------//
#define COFFEE_EndEnum(_export_api_, _export_statics_, _enum_) \
        coffee::meta::Types::Get()._RegisterType(*enum_type); \
    } \

