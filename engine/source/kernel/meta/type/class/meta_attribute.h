#ifndef _COFFEE_META_ATTRIBUTE_H_
#define _COFFEE_META_ATTRIBUTE_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_mode.h"
#include "kernel/meta/type/meta_type.h"

namespace coffee
{
namespace basic
{
    class String;
}

namespace meta
{
    class Param;

    //--------------------------------------------------------------------------------------------//
    /// Attribute information
    //--------------------------------------------------------------------------------------------//
    struct COFFEE_API Attribute
    {
        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Attribute();
        ~Attribute();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::String* _Name;
        Type* _Type;
        Param* _Param;
        ulong_ptr _Offset;
        bool _ItIsPointer;
        bool _ItIsArray;
        bool _ItIsWeak;
    };
}
}
#endif
