#ifndef _COFFEE_SHELL_EVENT_HANDLER_METHOD_H_
#define _COFFEE_SHELL_EVENT_HANDLER_METHOD_H_

#include "coffee_includes.h"
#include "kernel/shell/event/shell_event.h"

namespace coffee
{
namespace shell
{
    //--------------------------------------------------------------------------------------------//
    /// Event handler method
    ///
    /// Used to register custom external event handler, external means not in the target
    /// hierarchy (parent or child).
    ///
    /// @see coffee::shell::EventHandler
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API EventHandlerMethod
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        EventHandlerMethod();
        EventHandlerMethod(const EventCode & handled_code, void * class_instance,
            bool (* handler_method)(void *, Event &));
        virtual ~EventHandlerMethod();

        //-OPERATORS------------------------------------------------------------------------------//

        EventHandlerMethod& operator=(const EventHandlerMethod & handler_method);
        bool operator==(const EventHandlerMethod & handler_method) const;

        //-ACCESSORS------------------------------------------------------------------------------//

        const EventCode & GetHandledCode() const;
        const void * GetClassInstance() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Call(Event & event);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        EventCode _HandledCode;
        void * _ClassInstance;
        bool (* _HandlerMethod)(void *, Event &);
    };
}
}
#endif
