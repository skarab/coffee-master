#ifndef _COFFEE_SHELL_MACROS_EVENT_HANDLER_H_
#define _COFFEE_SHELL_MACROS_EVENT_HANDLER_H_

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_SendEvent
/// @brief Send event
//------------------------------------------------------------------------------------------------//
#define COFFEE_SendEvent(_event_handler_, _event_code_identifier_, _event_code_class_) \
    (_event_handler_).SendEvent(coffee::shell::Event(coffee::shell::EventCode(_event_code_identifier_, _event_code_class_::GetClassMetaType()))); \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_SendEventParams
/// @brief Send event with parameters
//------------------------------------------------------------------------------------------------//
#define COFFEE_SendEventParams(_event_handler_, _event_code_identifier_, _event_code_class_, _event_parameters_) \
    (_event_handler_).SendEvent(coffee::shell::Event(coffee::shell::EventCode(_event_code_identifier_, _event_code_class_::GetClassMetaType()), _event_parameters_)); \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_DeclareEventHandler
/// @brief Declare event handler
//------------------------------------------------------------------------------------------------//
#define COFFEE_DeclareEventHandler(_class_) \
    public: \
    virtual bool _HandleEvent(coffee::shell::Event& event); \
    bool _InternHandleEvent(coffee::shell::Event& event); \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_DeclareAncestorEventHandler
/// @brief Declare ancestor event handler
//------------------------------------------------------------------------------------------------//
#define COFFEE_DeclareAncestorEventHandler(_class_) \
    bool _InternHandleAncestorEvent(coffee::shell::Event& event); \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_Event
/// @brief To be put before each event handler, not that it's only a token
//------------------------------------------------------------------------------------------------//
#define COFFEE_Event

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_BeginEventHandler
/// @brief Implement event handler
//------------------------------------------------------------------------------------------------//
#define COFFEE_BeginEventHandler(_class_, _parent_class_) \
    bool _class_::_HandleEvent(coffee::shell::Event & event) \
    { \
        return _InternHandleEvent(event) \
            || _InternHandleAncestorEvent(event); \
    } \
    \
    bool _class_::_InternHandleEvent(coffee::shell::Event & event) \
    { \
        bool (_parent_class_::*parent_func)(coffee::shell::Event &) = &_parent_class_::_InternHandleEvent; \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_RegisterEventHandler
/// @brief Register event handler
//------------------------------------------------------------------------------------------------//
#define COFFEE_RegisterEventHandler(_event_code_identifier_, _event_code_class_, _method_) \
    if((&event.GetCode().GetType() == &_event_code_class_::GetClassMetaType()) \
        && ((_event_code_identifier_ == NONE) \
        || (event.GetCode().GetIdentifier() == _event_code_identifier_) \
       ) && _method_(event)) \
    { \
        return true; \
    } \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_RegisterTargetEventHandler
/// @brief Register target event handler
//------------------------------------------------------------------------------------------------//
#define COFFEE_RegisterTargetEventHandler(_event_code_identifier_, _event_code_class_, _event_target_, _method_) \
    if((event.GetTarget() == _event_target_ && &event.GetCode().GetType() == &_event_code_class_::GetClassMetaType()) \
        && ((_event_code_identifier_ == NONE) \
        || (event.GetCode().GetIdentifier() == _event_code_identifier_) \
       ) && _method_(event)) \
    { \
        return true; \
    } \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_EndEventHandler
/// @brief End event handler implementation
//------------------------------------------------------------------------------------------------//
#define COFFEE_EndEventHandler() \
        return (this->*parent_func)(event); \
    } \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_DeclareExternEventHandler
/// @brief Extern event handler declaration
//------------------------------------------------------------------------------------------------//
#define COFFEE_DeclareExternEventHandler(_class_, _method_) \
    static bool EXTERN_HANDLER_##_method_(void * instance, coffee::shell::Event & event) \
    { \
        return ((_class_ *) instance)->_method_(event); \
    } \
    COFFEE_Event bool _method_(coffee::shell::Event & event); \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_RegisterExternEventHandler
/// @brief Register extern event handler
//------------------------------------------------------------------------------------------------//
#define COFFEE_RegisterExternEventHandler(_event_code_identifier_, _event_code_class_, _event_hander_, _method_) \
    (_event_hander_).Register(this, &EXTERN_HANDLER_##_method_, coffee::shell::EventCode(_event_code_identifier_, _event_code_class_))

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_UnregisterExternEventHandler
/// @brief Unregister extern event handler
//------------------------------------------------------------------------------------------------//
#define COFFEE_UnregisterExternEventHandler(_event_hander_) \
    (_event_hander_).Unregister(this)

#endif
