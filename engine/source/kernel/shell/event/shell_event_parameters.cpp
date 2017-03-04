#include "kernel/shell/event/shell_event_parameters.h"

namespace coffee
{
namespace shell
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    EventParameters::EventParameters(void* custom_parameter, meta::Object* object_parameter) :
        _CustomParameter(custom_parameter),
        _Parameter(object_parameter)
    {
    }

    //--------------------------------------------------------------------------------------------//

    EventParameters::EventParameters(const EventParameters& parameters) :
        _CustomParameter(parameters._CustomParameter),
        _Parameter(parameters._Parameter)
    {
    }

    //--------------------------------------------------------------------------------------------//

    EventParameters::~EventParameters()
    {
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    EventParameters& EventParameters::operator = (const EventParameters& parameters)
    {
        _CustomParameter = parameters._CustomParameter;
        _Parameter = parameters._Parameter;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    bool EventParameters::operator == (const EventParameters& parameters) const
    {
        return (_CustomParameter==parameters._CustomParameter)
            && (_Parameter==parameters._Parameter);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void EventParameters::SetCustomParameter(void* custom_parameter)
    {
        _CustomParameter = custom_parameter;
    }

    //--------------------------------------------------------------------------------------------//

    const void* EventParameters::GetCustomParameter() const
    {
        return _CustomParameter;
    }

    //--------------------------------------------------------------------------------------------//

    void EventParameters::SetParameter(meta::Object* object_parameter)
    {
        _Parameter = object_parameter;
    }

    //--------------------------------------------------------------------------------------------//

    const meta::Object* EventParameters::GetParameter() const
    {
        return _Parameter;
    }

}
}
