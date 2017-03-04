#ifndef _COFFEE_META_TYPE_ENUM_H_
#define _COFFEE_META_TYPE_ENUM_H_

#include "coffee_includes.h"
#include "kernel/meta/type/scalar/meta_scalar.h"
#include "kernel/meta/type/enum/meta_enum_value.h"
#include "kernel/meta/type/enum/meta_enum_type.h"
#include "kernel/basic/container/basic_containers.h"

namespace coffee
{
namespace meta
{
    //--------------------------------------------------------------------------------------------//
    /// Enum contains all information about an enum type
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Enum : public Scalar
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Enum(basic::String name, const basic::String& friendly_name, const ENUM_TYPE& type);
        ~Enum();

        //-ACCESSORS------------------------------------------------------------------------------//

        const basic::String& GetFriendlyName() const;
        const ENUM_TYPE& GetType() const;
        const basic::Prow<EnumValue*, true>& GetValues() const;

        //-QUERIES--------------------------------------------------------------------------------//

        uint32 GetValue(const basic::String& name) const;
        basic::String GetName(uint32 value) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void AddValue(const basic::String& name, uint32 value);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::String _FriendlyName;
        ENUM_TYPE _Type;
        basic::Prow<EnumValue*, true> _ValueArray;
    };
}
}
#endif
