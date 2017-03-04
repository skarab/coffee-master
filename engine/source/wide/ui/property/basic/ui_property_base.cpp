//------------------------------------------------------------------------------------------------//
/// @file wide/ui/property/basic/ui_property_base.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/ui/property/basic/ui_property_base.h"
#include "wide/ui/property/ui_property_manager.h"
#include "wide/ui/property/ui_property_list.h"
#include "wide/ui/window/ui_window_manager.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::PropertyBase);
        COFFEE_Ancestor(ui::Property);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PropertyBase::PropertyBase() :
        _ObjectInfo(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    PropertyBase::~PropertyBase()
    {
        if (_ObjectInfo!=NULL)
            _ObjectInfo->Destroy();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyBase::CreateContent()
    {
        basic::PropertyBase* prop = (basic::PropertyBase *) GetData();

        if(prop->IsScalar())
        {
            _ObjectInfo = COFFEE_New(meta::ObjectInfo, 
                ((basic::PropertyScalar *) prop->GetObject())->GetObject(),
                (meta::Type*)prop->GetType(),
                &_Attribute);

            _ObjectInfo->SetName(prop->GetName());
            _Attribute._Param = COFFEE_New(meta::Param);
            PropertyManager::Get().CreatePropertyInterface(
                *this, *_ObjectInfo, prop->GetType(), NULL, 0);
        }
        else
        {
            _ObjectInfo = COFFEE_New(meta::ObjectInfo, 
                (void *) prop->GetObject(),
                (meta::Type*)prop->GetType(),
                &_Attribute);

            _ObjectInfo->SetName(prop->GetName());
            _Attribute._Param = COFFEE_New(meta::Param);

            if(PropertyManager::Get().CreatePropertyInterface(
                *this, *_ObjectInfo, prop->GetType(), NULL, PROPERTY_FLAG_Root)==NULL)
            {
                widget::Group* group;
                group = COFFEE_New(widget::Group);
                group->Create(this, basic::Vector2i(),
                    basic::Vector2i(GetClientRect().Size.X, 20));
                group->SetTitleBarText(prop->GetName());
                
                PropertyList* list;
                list = COFFEE_New(PropertyList);
                list->Create(*prop->GetObject(), basic::Vector2i(), basic::Vector2i(), group, false);
            }
        }
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(PropertyBase, Property)
    COFFEE_EndEventHandler()

}
}
//------------------------------------------------------------------------------------------------//
