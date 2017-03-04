#ifndef _COFFEE_META_TYPE_TEMPLATES_H_
#define _COFFEE_META_TYPE_TEMPLATES_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_types.h"
#include "kernel/meta/type/scalar/meta_scalar.h"
#include "kernel/meta/type/class/meta_class.h"

namespace coffee
{
namespace meta
{
    //--------------------------------------------------------------------------------------------//
    /// Meta type template helper
    ///
    /// Used to retrieve internal meta type from object type.
    ///
    /// @usage coffee::meta::TYPE< uint8 >().Get()
    /// @note When given type isn't supported it will raise a compilation error.
    /// @see coffee::meta::Type
    //--------------------------------------------------------------------------------------------//
    template< typename type >
    struct COFFEE_TEMPLATE_API TYPE
    {
        //-OPERATIONS-----------------------------------------------------------------------------//

        Type& Get();
    };

    #include "kernel/meta/type/meta_type_templates.hpp"
}
}
#endif
