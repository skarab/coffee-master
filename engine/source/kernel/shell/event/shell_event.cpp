#include "kernel/shell/event/shell_event.h"
#include "kernel/shell/event/shell_event_handler.h"

namespace coffee
{
namespace shell
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Event::Event(const EventCode& code, const EventParameters& parameters) :
        _Code(code),
        _Target(NULL),
        _Parameters(parameters),
        _Flags(EVENT_FLAG_StopWhenHandled)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Event::Event(const Event& event) :
        _Code(event._Code),
        _Target(event._Target),
        _Parameters(event._Parameters),
        _Flags(event._Flags)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Event::~Event()
    {
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    Event& Event::operator=(const Event& event)
    {
        _Code = event._Code;
        _Target = event._Target;
        _Parameters = event._Parameters;
        _Flags = event._Flags;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    bool Event::operator ==(const Event& event) const
    {
        return (_Code == event._Code)
            && (_Target == event._Target)
            && (_Parameters == event._Parameters)
            && (_Flags == event._Flags);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Event::Set(
        const EventCode& code,
        const EventParameters& parameters,
        uint32 flags)
    {
        _Code = code;
        _Target = NULL;
        _Parameters = parameters;
        _Flags = flags;
    }

    //-VARIABLES----------------------------------------------------------------------------------//

    Event Event::Null;
}
}
