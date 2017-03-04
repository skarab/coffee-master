#ifndef _COFFEE_META_ENUM_VALUE_H_
#define _COFFEE_META_ENUM_VALUE_H_

#include "coffee_includes.h"
#include "kernel/basic/alpha/string/basic_string.h"

namespace coffee
{
namespace meta
{
    //--------------------------------------------------------------------------------------------//
    /// Contain data about the enum value
    /// @see coffee::meta::Enum
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API EnumValue
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        EnumValue(basic::String name, uint32 value);
        virtual ~EnumValue();

        //-ACCESSORS------------------------------------------------------------------------------//

        const basic::String& GetName() const;
        uint32 GetValue() const;

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::String _Name;
        uint32 _Value;
    };
}
}
#endif
