#ifndef _COFFEE_UI_MACROS_PROPERTY_H_
#define _COFFEE_UI_MACROS_PROPERTY_H_

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_PropertyInterface
/// @brief Declare a property interface
/// @see ui::PropertyManager
//------------------------------------------------------------------------------------------------//
#define COFFEE_PropertyInterface(_object_, _meta_type_name_, _meta_param_name_, _it_is_handling_array_) \
    public: \
        COFFEE_Type(_object_); \
        static coffee::basic::String GetHandledTypeName() { return _meta_type_name_; } \
        static coffee::basic::String GetHandledParamName() { return _meta_param_name_; } \
        static bool IsHandlingArray() { return _it_is_handling_array_; } \

#endif
