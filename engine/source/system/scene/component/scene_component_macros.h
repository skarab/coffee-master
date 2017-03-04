#ifndef _COFFEE_SCENE_COMPONENT_MACROS_H_
#define _COFFEE_SCENE_COMPONENT_MACROS_H_

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_Component
/// @brief Declare a component
/// @see component::Manager
//------------------------------------------------------------------------------------------------//
#define COFFEE_Component(_class_, _name_, _classification_) \
    public: \
        COFFEE_Type(_class_); \
        virtual const coffee::basic::String GetName() const { return _name_; } \
        virtual const coffee::basic::String GetClassification() const { return _classification_; } \
        static const coffee::basic::String GetStaticName() { return _name_; } \
        static const coffee::basic::String GetStaticClassification() { return _classification_; } \

#endif
