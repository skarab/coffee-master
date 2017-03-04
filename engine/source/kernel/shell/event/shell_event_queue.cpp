#include "kernel/shell/event/shell_event_queue.h"
#include "kernel/shell/event/shell_event_handler.h"
#include "coffee.h"

namespace coffee
{
namespace shell
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    EventQueue::EventQueue() :
        _FreeCounter(0)
    {
    }

    //--------------------------------------------------------------------------------------------//

    EventQueue::~EventQueue()
    {
        COFFEE_Assert(IsEmpty(), core::ERROR_CODE_Unexpected,
            "Destroying event queue containing events");
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool EventQueue::IsEmpty() const
    {
        return Events.IsEmpty();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void EventQueue::AddEvent(const Event & event)
    {
        Events.AddItem(event);

        COFFEE_Assert(Events.GetSize()<(uint32)(Engine::Get().HasMode(RUN_MODE_Events)?32:999),
            core::ERROR_CODE_Unexpected, "Infinite loop detected.");
    }

    //--------------------------------------------------------------------------------------------//

    bool EventQueue::PickEvent(Event & event)
    {
        if (Events.GetSize()>0)
        {
            event = Events[0];
            Events.Remove(0);
            _FreeCounter = 100;
            return true;
        }
        if (_FreeCounter>0)
            --_FreeCounter;
        if (_FreeCounter==0)
        {
            Events.Erase();
            _FreeCounter = -1;
        }
        return false;
    }

}
}
