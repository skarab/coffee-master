#include "kernel/shell/event/shell_event_code.h"

namespace coffee
{
namespace shell
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    EventCode::EventCode() :
        _Identifier(NONE),
        _Type(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    EventCode::EventCode(const EventCode & code) :
        _Identifier(code._Identifier),
        _Type(code._Type)
    {
    }

    //--------------------------------------------------------------------------------------------//

    EventCode::EventCode(uint32 identifier, const meta::Class & type) :
        _Identifier(identifier),
        _Type(&type)
    {
    }

    //--------------------------------------------------------------------------------------------//

    EventCode::~EventCode()
    {
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    EventCode& EventCode::operator = (const EventCode & code)
    {
        _Identifier = code._Identifier;
        _Type = code._Type;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    bool EventCode::operator ==(const EventCode & code) const
    {
        return ((_Identifier == code._Identifier) && (_Type == code._Type));
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    uint32 EventCode::GetIdentifier() const
    {
        return _Identifier;
    }

    //--------------------------------------------------------------------------------------------//

    const meta::Class & EventCode::GetType() const
    {
        return *_Type;
    }

}
}
