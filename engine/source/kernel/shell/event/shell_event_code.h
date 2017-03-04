#ifndef _COFFEE_SHELL_EVENT_CODE_H_
#define _COFFEE_SHELL_EVENT_CODE_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_object.h"

namespace coffee
{
namespace shell
{
    //--------------------------------------------------------------------------------------------//
    /// Event code
    ///
    /// Event code is a pair of custom code and meta type, this allow one code list (enum) per
    /// meta type, so custom event code can be defined everywhere.
    ///
    /// @see coffee::shell::EventHandler
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API EventCode
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        EventCode();
        EventCode(const EventCode & code);
        EventCode(uint32 identifier, const meta::Class & type);
        ~EventCode();

        //-OPERATORS------------------------------------------------------------------------------//

        EventCode& operator = (const EventCode & code);
        bool operator ==(const EventCode & code) const;

        //-ACCESSORS------------------------------------------------------------------------------//

        uint32 GetIdentifier() const;
        const meta::Class & GetType() const;

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        uint32 _Identifier;
        const meta::Class * _Type;
    };
}
}
#endif
