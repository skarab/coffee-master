#ifndef _COFFEE_SHELL_STATE_TRANSITION_H_
#define _COFFEE_SHELL_STATE_TRANSITION_H_

#include "coffee_includes.h"
#include "kernel/shell/event/shell_event_handler.h"

namespace coffee
{
namespace shell
{
    //--------------------------------------------------------------------------------------------//
    /// State transition
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API StateTransition
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        StateTransition();
        StateTransition(uint32 source_identifier, uint32 destination_identifier,
            void * class_instance,
            void (* enter_method)(void *, Event & event)=NULL,
            void (* leave_method)(void *, Event & event)=NULL,
            bool (* update_method)(void *, Event & event)=NULL);
        virtual ~StateTransition();

        //-ACCESSORS------------------------------------------------------------------------------//

        uint32 GetSourceIdentifier() const;
        uint32 GetDestinationIdentifier() const;
        void SetTriggerEvent(const Event & trigger_event);
        const Event & GetTriggerEvent() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Enter();
        void Leave();
        bool Update();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        uint32 _SourceIdentifier;
        uint32 _DestinationIdentifier;
        void * _ClassInstance;
        void (* _EnterMethod)(void *, Event & event);
        void (* _LeaveMethod)(void *, Event & event);
        bool (* _UpdateMethod)(void *, Event & event);
        Event _TriggerEvent;
    };
}
}
#endif
