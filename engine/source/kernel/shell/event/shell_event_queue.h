#ifndef _COFFEE_SHELL_EVENT_QUEUE_H_
#define _COFFEE_SHELL_EVENT_QUEUE_H_

#include "coffee_includes.h"
#include "kernel/basic/container/vector/basic_vector.h"
#include "kernel/shell/event/shell_event.h"

namespace coffee
{
namespace shell
{
    class EventHandler;

    //--------------------------------------------------------------------------------------------//
    /// Event queue
    ///
    /// Queue of events, which need to be processed by the event handler.
    ///
    /// @see coffee::shell::EventHandler
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API EventQueue
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        EventQueue();
        ~EventQueue();

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsEmpty() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void AddEvent(const Event & event);
        bool PickEvent(Event & event);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Vector< Event > Events;

    private:

        int32 _FreeCounter;
    };
}
}
#endif
