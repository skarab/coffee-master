//------------------------------------------------------------------------------------------------//
/// @file kernel/shell/state/shell_state.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "kernel/shell/state/shell_state.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
namespace shell
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    State::State() :
        _Identifier(NULL),
        _ClassInstance(NULL),
        _EnterMethod(NULL),
        _LeaveMethod(NULL),
        _UpdateMethod(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    State::State(uint32 identifier, void * class_instance,
        void (* enter_method)(void *, Event & event),
        void (* leave_method)(void *, Event & event),
        void (* update_method)(void *, Event & event)) :
            _Identifier(identifier),
            _ClassInstance(class_instance),
            _EnterMethod(enter_method),
            _LeaveMethod(leave_method),
            _UpdateMethod(update_method)
    {
    }

    //--------------------------------------------------------------------------------------------//

    State::~State()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    uint32 State::GetIdentifier() const
    {
        return _Identifier;
    }

    //--------------------------------------------------------------------------------------------//

    void State::SetTriggerEvent(const Event & trigger_event)
    {
        _TriggerEvent = trigger_event;
    }

    //--------------------------------------------------------------------------------------------//

    const Event & State::GetTriggerEvent() const
    {
        return _TriggerEvent;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void State::Enter()
    {
        (*_EnterMethod)(_ClassInstance, _TriggerEvent);
    }

    //--------------------------------------------------------------------------------------------//

    void State::Leave()
    {
        (*_LeaveMethod)(_ClassInstance, _TriggerEvent);
    }

    //--------------------------------------------------------------------------------------------//

    void State::Update()
    {
        (*_UpdateMethod)(_ClassInstance, _TriggerEvent);
    }

}
}
//------------------------------------------------------------------------------------------------//
