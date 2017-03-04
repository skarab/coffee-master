//------------------------------------------------------------------------------------------------//
/// @file kernel/resource/property/resource_property_base.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "kernel/resource/property/resource_property_base.h"
#include "wide/ui/property/resource/ui_property_resource_property.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(resource::PropertyBase);
        COFFEE_Attribute(uint32, _Flags, meta::MODE_Serializeable);
    COFFEE_EndType();

namespace resource
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PropertyBase::PropertyBase() :
        _SourceProperty(NULL),
        _Flags(0)
    {
    }

    //--------------------------------------------------------------------------------------------//

    PropertyBase::~PropertyBase()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void PropertyBase::SetSourceProperty(PropertyBase * source_property)
    {
        _SourceProperty = source_property;
    }

    //--------------------------------------------------------------------------------------------//

    const PropertyBase & PropertyBase::GetSourceProperty() const
    {
        return *_SourceProperty;
    }

    //--------------------------------------------------------------------------------------------//

    PropertyBase & PropertyBase::GetSourceProperty()
    {
        return *_SourceProperty;
    }

    //--------------------------------------------------------------------------------------------//

    void PropertyBase::SetFlags(uint32 flags)
    {
        _Flags = flags;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 PropertyBase::GetFlags() const
    {
        return _Flags;
    }

    //-QUERIES--------------------------------------------------------------------------------------------------------//

    void PropertyBase::EnableFlag(const PROPERTY_FLAG& flag, bool it_has_to_enable)
    {
        COFFEE_EnableFlag(_Flags, flag, it_has_to_enable);
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyBase::IsFlagEnabled(const PROPERTY_FLAG & flag) const
    {
        return COFFEE_IsFlagEnabled(_Flags, flag);
    }

    //--------------------------------------------------------------------------------------------//

    const PropertyBase & PropertyBase::GetProperty() const
    {
        if(IsFlagEnabled(PROPERTY_FLAG_Enabled) || _SourceProperty == NULL)
            return *this;

        return GetSourceProperty();
    }

    //--------------------------------------------------------------------------------------------//

    PropertyBase& PropertyBase::GrabProperty()
    {
        if(IsFlagEnabled(PROPERTY_FLAG_Enabled) || _SourceProperty==NULL)
            return *this;

        return GetSourceProperty();
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyBase::IsSource() const
    {
        return _SourceProperty==NULL;
    }

}
}
//------------------------------------------------------------------------------------------------//
