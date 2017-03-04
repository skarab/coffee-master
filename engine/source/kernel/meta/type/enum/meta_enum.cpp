#include "kernel/meta/type/enum/meta_enum.h"
#include "kernel/core/core.h"
#include "kernel/meta/meta_types.h"
#include "kernel/basic/alpha/basic_alpha.h"

namespace coffee
{
namespace meta
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Enum::Enum(basic::String name, const basic::String& friendly_name, const ENUM_TYPE& type) :
        Scalar(name),
        _FriendlyName(friendly_name),
        _Type(type)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Enum::~Enum()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const basic::String& Enum::GetFriendlyName() const
    {
        return _FriendlyName;
    }

    //--------------------------------------------------------------------------------------------//

    const ENUM_TYPE& Enum::GetType() const
    {
        return _Type;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Prow<EnumValue*, true>& Enum::GetValues() const
    {
        return _ValueArray;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    uint32 Enum::GetValue(const basic::String& name) const
    {
        for (uint32 i=0 ; i<_ValueArray.GetSize() ; ++i)
        {
            if (_ValueArray[i]->GetName()==name)
                return _ValueArray[i]->GetValue();
        }
        return NONE;
    }

    //--------------------------------------------------------------------------------------------//

    basic::String Enum::GetName(uint32 value) const
    {
        for (uint32 i=0 ; i<_ValueArray.GetSize() ; ++i)
        {
            if (_ValueArray[i]->GetValue()==value)
                return _ValueArray[i]->GetName();
        }
        return "";
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Enum::AddValue(const basic::String& name, uint32 value)
    {
        _ValueArray.AddItem(COFFEE_New(EnumValue, name, value));
    }

}
}
