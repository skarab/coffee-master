#ifndef _COFFEE_BASIC_PROPERTY_H_
#define _COFFEE_BASIC_PROPERTY_H_

#include "coffee_includes.h"
#include "kernel/basic/property/basic_property_base.h"
#include "kernel/basic/property/basic_property_template.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Property template
    ///
    /// @see coffee::basic::PropertyBase
    //--------------------------------------------------------------------------------------------//
    template< typename type > \
    class COFFEE_TEMPLATE_API Property : public PropertyBase
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Property();
        Property(String name);
        virtual ~Property();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void SetValue(const type & object);
        const type & GetValue() const;
    };

    #include "kernel/basic/property/basic_property.hpp"
}
}
#endif
