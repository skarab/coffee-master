#include "kernel/shell/event/shell_event_handler_method.h"

namespace coffee
{
namespace shell
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    EventHandlerMethod::EventHandlerMethod() :
        _ClassInstance(NULL),
        _HandlerMethod(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    EventHandlerMethod::EventHandlerMethod(
        const EventCode & handled_code,
        void * class_instance,
        bool (* handler_method)(void *, Event &)) :
            _HandledCode(handled_code),
            _ClassInstance(class_instance),
            _HandlerMethod(handler_method)
    {
    }

    //--------------------------------------------------------------------------------------------//

    EventHandlerMethod::~EventHandlerMethod()
    {
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    EventHandlerMethod& EventHandlerMethod::operator=(const EventHandlerMethod & handler_method)
    {
        _HandledCode = handler_method._HandledCode;
        _ClassInstance = handler_method._ClassInstance;
        _HandlerMethod = handler_method._HandlerMethod;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    bool EventHandlerMethod::operator==(const EventHandlerMethod & handler_method) const
    {
        return (_HandledCode == handler_method._HandledCode)
            && (_ClassInstance == handler_method._ClassInstance)
            && (_HandlerMethod == handler_method._HandlerMethod);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const EventCode & EventHandlerMethod::GetHandledCode() const
    {
        return _HandledCode;
    }

    //--------------------------------------------------------------------------------------------//

    const void * EventHandlerMethod::GetClassInstance() const
    {
        return _ClassInstance;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool EventHandlerMethod::Call(Event & event)
    {
        return (*_HandlerMethod)(_ClassInstance, event);
    }

}
}
