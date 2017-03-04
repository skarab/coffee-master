#ifndef _COFFEE_BASIC_PROPERTY_LIST_H_
#define _COFFEE_BASIC_PROPERTY_LIST_H_

#include "coffee_includes.h"
#include "kernel/basic/container/basic_containers.h"
#include "kernel/basic/property/basic_property_base.h"
#include "kernel/basic/property/basic_property.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Property list
    ///
    /// Simple class to handle list of properties.
    ///
    /// @see coffee::basic::PropertyBase
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyList : public meta::Object
    {
        COFFEE_Type(PropertyList);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyList();
        virtual ~PropertyList();

        //-ACCESSORS------------------------------------------------------------------------------//

        uint32 GetPropertyCount() const;
        const PropertyBase & GetProperty(uint32 property_index) const;
        PropertyBase & GetProperty(uint32 property_index);

        //-QUERIES--------------------------------------------------------------------------------//

        PropertyBase* FindProperty(const String& property_name) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void AddProperty(PropertyBase& property, uint32 property_index=NONE);
        void RemoveProperty(PropertyBase& property);
        void RemoveProperty(uint32 property_index);
        void RemoveAllProperties();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Prow< PropertyBase *, true > _PropertyArray;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyList);
}
}
#endif
