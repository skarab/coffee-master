#include "wide/ui/property/ui_property_manager.h"
#include "wide/ui/property/resource/ui_property_resource.h"
#include "wide/ui/property/ui_properties.h"

namespace coffee
{
namespace ui
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_ImplementSingleton(PropertyManager);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PropertyManager::PropertyManager()
    {
        COFFEE_CreateSingleton(PropertyManager);

        Register<PropertyBool>();
        Register<PropertyEnum>();
        Register<PropertyInt8>();
        Register<PropertyInt16>();
        Register<PropertyInt32>();
        Register<PropertyUInt8>();
        Register<PropertyUInt16>();
        Register<PropertyUInt32EnumMulti>();
        Register<PropertyUInt32>();
        Register<PropertyReal>();
        Register<PropertyArrayCombo>();
        Register<PropertyArray>();
        Register<PropertyBase>();
        Register<PropertyEuler>();
        Register<PropertyQuaternion>();
        Register<PropertyImage>();
        Register<PropertyColor>();
        Register<PropertyVector3>();
        Register<PropertyString>();
        Register<PropertyText>();
    }

    //--------------------------------------------------------------------------------------------//

    PropertyManager::~PropertyManager()
    {
        COFFEE_DestroySingleton(PropertyManager);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//
   
    Property* PropertyManager::CreatePropertyInterface(Window& parent_window,
        meta::ObjectInfo& object_info, const meta::Type* meta_type,
        const meta::Param* meta_param, uint32 flags)
    {
        if (!(flags&PROPERTY_FLAG_ResourceInstance) && !(flags&PROPERTY_FLAG_Array)
            && meta_type->GetInfo()==meta::TYPE_INFO_Class
            && static_cast<const meta::Class*>(meta_type)->IsKindOf<resource::Object>())
        {
            if(static_cast<resource::Object*>(object_info.GetData())->IsInstantiated())
            {
                Property* property_interface = COFFEE_New(PropertyResource);
                property_interface->Create(object_info, parent_window);
                return property_interface;
            }
        }

        for (uint32 index=0 ; index<_Interfaces.GetSize() ; ++index)
        {
            if ((_Interfaces[index]->_HandledType.GetLength()==0
                || _Interfaces[index]->_HandledType==meta_type->GetName())
                    && (_Interfaces[index]->_HandledParams.GetLength()==0
                || (meta_param!=NULL
                    && _Interfaces[index]->_HandledParams==meta_param->GetMetaType().GetName()))
                && _Interfaces[index]->_ItIsHandlingArray==((flags&PROPERTY_FLAG_Array)>0))
            {
                Property* property_interface = static_cast<Property*>(_Interfaces[index]->_MetaType->CreateObject());
                property_interface->Create(object_info, parent_window);
                return property_interface;
            }
        }

        if (meta_type->GetInfo()==meta::TYPE_INFO_Scalar
            && ((meta::Scalar*)meta_type)->GetFormat()==meta::SCALAR_FORMAT_Enum)
        {
            for (uint32 index=0 ; index<_Interfaces.GetSize() ; ++index)
            {
                if (_Interfaces[index]->_HandledType=="enum")
                {
                    Property* property_interface;
                    property_interface = static_cast<Property*>(_Interfaces[index]->_MetaType->CreateObject());
                    property_interface->Create(object_info, parent_window);
                    return property_interface;
                }
            }
        }
        return NULL;
    }

}
}
