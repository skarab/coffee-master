#include "kernel/basic/property/basic_property_list.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::PropertyList);
        COFFEE_Attribute(< basic::PropertyBase * >, _PropertyArray, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PropertyList::PropertyList()
    {
    }

    //--------------------------------------------------------------------------------------------//

    PropertyList::~PropertyList()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    uint32 PropertyList::GetPropertyCount() const
    {
        return _PropertyArray.GetSize();
    }

    //--------------------------------------------------------------------------------------------//

    const PropertyBase & PropertyList::GetProperty(uint32 property_index) const
    {
        return *_PropertyArray[ property_index ];
    }

    //--------------------------------------------------------------------------------------------//

    PropertyBase & PropertyList::GetProperty(uint32 property_index)
    {
        return *_PropertyArray[ property_index ];
    }

    //-QUERIES------------------------------------------------------------------------------------//

    PropertyBase * PropertyList::FindProperty(const basic::String & property_name) const
    {
        uint32 property_index;

        for(property_index = 0 ; property_index < _PropertyArray.GetSize() ; ++ property_index)
        {
            if(_PropertyArray[ property_index ]->GetName() == property_name)
                return _PropertyArray[ property_index ];
        }

        return NULL;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyList::AddProperty(PropertyBase & property, uint32 property_index)
    {
        _PropertyArray.AddItem(&property, property_index);
    }

    //--------------------------------------------------------------------------------------------//

    void PropertyList::RemoveProperty(PropertyBase & property)
    {
        _PropertyArray.RemoveItem(&property);
    }

    //--------------------------------------------------------------------------------------------//

    void PropertyList::RemoveProperty(uint32 property_index)
    {
        _PropertyArray.Remove(property_index);
    }

    //--------------------------------------------------------------------------------------------//

    void PropertyList::RemoveAllProperties()
    {
        _PropertyArray.Clear();
    }

}
}
