//------------------------------------------------------------------------------------------------//
/// @file kernel/shell/state/shell_state_transition.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "kernel/shell/state/shell_state_transition.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
namespace shell
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    StateTransition::StateTransition() :
        _SourceIdentifier(NULL),
        _DestinationIdentifier(NULL),
        _ClassInstance(NULL),
        _EnterMethod(NULL),
        _LeaveMethod(NULL),
        _UpdateMethod(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    StateTransition::StateTransition(uint32 source_identifier, uint32 destination_identifier,
        void * class_instance,
        void (* enter_method)(void *, Event & event),
        void (* leave_method)(void *, Event & event),
        bool (* update_method)(void *, Event & event)) :
            _SourceIdentifier(source_identifier),
            _DestinationIdentifier(destination_identifier),
            _ClassInstance(class_instance),
            _EnterMethod(enter_method),
            _LeaveMethod(leave_method),
            _UpdateMethod(update_method)
    {
    }

    //--------------------------------------------------------------------------------------------//

    StateTransition::~StateTransition()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    uint32 StateTransition::GetSourceIdentifier() const
    {
        return _SourceIdentifier;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 StateTransition::GetDestinationIdentifier() const
    {
        return _DestinationIdentifier;
    }

    //--------------------------------------------------------------------------------------------//

    void StateTransition::SetTriggerEvent(const Event & trigger_event)
    {
        _TriggerEvent = trigger_event;
    }

    //--------------------------------------------------------------------------------------------//

    const Event & StateTransition::GetTriggerEvent() const
    {
        return _TriggerEvent;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void StateTransition::Enter()
    {
        if(_EnterMethod != NULL)
            (*_EnterMethod)(_ClassInstance, _TriggerEvent);
    }

    //--------------------------------------------------------------------------------------------//

    void StateTransition::Leave()
    {
        if(_LeaveMethod != NULL)
            (*_LeaveMethod)(_ClassInstance, _TriggerEvent);
    }

    //--------------------------------------------------------------------------------------------//

    bool StateTransition::Update()
    {
        if(_UpdateMethod != NULL)
            return (*_UpdateMethod)(_ClassInstance, _TriggerEvent);

        return true;
    }

}
}
//------------------------------------------------------------------------------------------------//
