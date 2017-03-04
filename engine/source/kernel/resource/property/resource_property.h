#ifndef _COFFEE_RESOURCE_PROPERTY_H_
#define _COFFEE_RESOURCE_PROPERTY_H_

#include "coffee_includes.h"
#include "kernel/resource/property/resource_property_template.h"
#include "kernel/resource/property/resource_property_base.h"

namespace coffee
{
namespace resource
{
    //--------------------------------------------------------------------------------------------//
    /// Resource property template
    ///
    /// It manages resource properties.
    ///
    /// @see coffee::resource::PropertyBase, coffee::resource::Object
    //--------------------------------------------------------------------------------------------//
    template< typename type > \
    class COFFEE_TEMPLATE_API Property : public PropertyBase
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Property();
        Property(const type& value);
        virtual ~Property();

        //-OPERATIONS-----------------------------------------------------------------------------//

        /// Set property value, from source property if PROPERTY_FLAG_Enabled isn't set
        void Set(const type& value);

        /// Get property value, from source property if PROPERTY_FLAG_Enabled isn't set
        const type& Get() const;

        /// Get property value in R/W mode and set PROPERTY_FLAG_Enabled flag
        type& Grab();

        /// Set direct property value
        void SetValue(const type& value);

        /// Get direct property value
        const type& GetValue() const;

        /// Get direct property value in R/W mode
        type& GrabValue();

    //private:

        /// Used internally by the serialization system, consider this as private
        type& _metaValue();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        type _Value;
    };

    #include "kernel/resource/property/resource_property.hpp"
}
}
#endif
