#ifndef _COFFEE_SHELL_STATE_H_
#define _COFFEE_SHELL_STATE_H_

#include "coffee_includes.h"
#include "kernel/shell/event/shell_event_handler.h"

namespace coffee
{
namespace shell
{
    //--------------------------------------------------------------------------------------------//
    /// State
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API State
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        State();
        State(uint32 identifier, void * class_instance,
            void (* enter_method)(void *, Event & event),
            void (* leave_method)(void *, Event & event),
            void (* update_method)(void *, Event & event));
        virtual ~State();

        //-ACCESSORS------------------------------------------------------------------------------//

        uint32 GetIdentifier() const;
        void SetTriggerEvent(const Event & trigger_event);
        const Event & GetTriggerEvent() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Enter();
        void Leave();
        void Update();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        uint32 _Identifier;
        void * _ClassInstance;
        void (* _EnterMethod)(void *, Event & event);
        void (* _LeaveMethod)(void *, Event & event);
        void (* _UpdateMethod)(void *, Event & event);
        Event _TriggerEvent;
    };
}
}
#endif
