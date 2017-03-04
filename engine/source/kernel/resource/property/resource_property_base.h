#ifndef _COFFEE_RESOURCE_PROPERTY_BASE_H_
#define _COFFEE_RESOURCE_PROPERTY_BASE_H_

#include "coffee_includes.h"
#include "kernel/meta/meta.h"
#include "kernel/resource/property/resource_property_flag.h"

namespace coffee
{
namespace ui
{
    class PropertyResourceProperty;
}

namespace resource
{
    //--------------------------------------------------------------------------------------------//
    /// Resource property base class
    ///
    /// @see coffee::resource::Property
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyBase : public meta::Object
    {
        COFFEE_Type(PropertyBase);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyBase();
        virtual ~PropertyBase();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetSourceProperty(PropertyBase* source_property);
        const PropertyBase& GetSourceProperty() const;
        PropertyBase& GetSourceProperty();
        void SetFlags(uint32 flags);
        uint32 GetFlags() const;

        //-QUERIES--------------------------------------------------------------------------------//

        void EnableFlag(const PROPERTY_FLAG& flag, bool it_has_to_enable);
        bool IsFlagEnabled(const PROPERTY_FLAG& flag) const;
        const PropertyBase& GetProperty() const;
        PropertyBase& GrabProperty();
        bool IsSource() const;

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        PropertyBase* _SourceProperty;
        uint32 _Flags;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyBase);
}
}
#endif
