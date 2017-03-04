#ifndef _COFFEE_SHELL_EVENT_H_
#define _COFFEE_SHELL_EVENT_H_

#include "coffee_includes.h"
#include "kernel/shell/event/shell_event_code.h"
#include "kernel/shell/event/shell_event_parameters.h"
#include "kernel/shell/event/shell_event_flag.h"

namespace coffee
{
namespace shell
{
    class EventHandler;

    //--------------------------------------------------------------------------------------------//
    /// Event
    ///
    /// @see coffee::shell::EventHandler
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Event
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Event(const EventCode& code = EventCode(),
            const EventParameters& parameters = EventParameters());
        Event(const Event& event);
        ~Event();

        //-OPERATORS------------------------------------------------------------------------------//

        Event& operator=(const Event& event);
        bool operator ==(const Event& event) const;

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetCode(const EventCode& code) { _Code = code; }
        const EventCode& GetCode() const { return _Code; }
        void SetTarget(EventHandler* target) { _Target = target; }
        const EventHandler* GetTarget() const { return _Target; }
        EventHandler* GetTarget() { return _Target; }
        void SetParameters(const EventParameters& parameters) { _Parameters = parameters; }
        const EventParameters& GetParameters() const { return _Parameters; }
        EventParameters& GetParameters() { return _Parameters; }
        void SetFlags(uint32 flags) { _Flags = flags; }
        void EnableFlag(EVENT_FLAG flag, bool it_is_enabled) { COFFEE_EnableFlag(_Flags, flag, it_is_enabled); }
        bool IsFlagEnabled(EVENT_FLAG flag) { return COFFEE_IsFlagEnabled(_Flags, flag); }

        //-QUERIES--------------------------------------------------------------------------------//

        bool GetBoolean() const { return _Parameters.GetCustomParameter()!=0; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Set(
            const EventCode& code,
            const EventParameters& parameters = EventParameters(),
            uint32 flags = EVENT_FLAG_StopWhenHandled);

        //-VARIABLES------------------------------------------------------------------------------//

        static Event Null;

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        EventCode _Code;
        EventHandler* _Target;
        EventParameters _Parameters;
        uint32 _Flags;
    };
}
}
#endif
