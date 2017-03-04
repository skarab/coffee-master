//------------------------------------------------------------------------------------------------//
/// @file wide/ui/property/array/ui_property_array_combo.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/ui/property/array/ui_property_array_combo.h"
#include "wide/ui/property/ui_property_list.h"
#include "wide/ui/window/ui_window_manager.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::PropertyArrayCombo);
        COFFEE_Ancestor(ui::Property);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PropertyArrayCombo::PropertyArrayCombo() :
        _Group(NULL),
        _ComboBox(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    PropertyArrayCombo::~PropertyArrayCombo()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyArrayCombo::CreateContent()
    {
        _Group = COFFEE_New(widget::Group);
        _Group->Create(this, basic::Vector2i(),
            basic::Vector2i(GetClientRect().Size.X, 20));
        _Group->SetTitleBarText(GetName());
        
        _InitializeContent();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(PropertyArrayCombo, Property)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Select, widget::Widget, _ComboBox, OnSelectItem)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool PropertyArrayCombo::OnSelectItem(shell::Event& event)
    {
        _CreateHierarchy(_ComboBox->GetSelectedIndex());
        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyArrayCombo::_InitializeContent()
    {
        _ComboBox = COFFEE_New(widget::ComboBox);
        _ComboBox->Create(_Group, basic::Vector2i(),
            _Group->GetClientRect().Size.X);
        _ComboBox->GetLayout().SetStyle(LAYOUT_STYLE_HorizontalCanvas | LAYOUT_STYLE_StickChildren
            | LAYOUT_STYLE_HorizontalExpand);
        
        for(uint32 child_index=0 ; child_index<GetObjectInfo().GetChildCount() ; ++child_index)
        {
            basic::String name("Object %i", child_index);
            meta::ObjectInfo* object;
            meta::ParamArrayCombo* meta_param =
                (meta::ParamArrayCombo *) GetObjectInfo().GetAttribute()._Param;

            object = GetObjectInfo().GetChild(child_index).FindByNameAndType(
                meta_param->GetAttributeName(), basic::String::GetClassMetaType());

            if(object==NULL)
            {
                uint32 ancestor_index(0);
                uint32 attribute_index(0);
                meta::Attribute * attribute;
                ulong_ptr attribute_offset;
                bool it_has_found(false);

                while (((meta::Class&)GetObjectInfo().GetChild(child_index).GetType()).FindNextAttribute(
                    ancestor_index, attribute_index, &attribute, attribute_offset))
                {
                    if (attribute->_Type==&basic::String::GetClassMetaType()
                        && *attribute->_Name==meta_param->GetAttributeName())
                    {
                        name = *(basic::String *)((ulong_ptr) GetObjectInfo().GetChild(child_index).GetData()
                            + attribute_offset);
                        it_has_found = true;
                        break;
                    }
                }

                if(!it_has_found)
                {
                    meta::Enum* enum_type = (meta::Enum*)meta::Types::Get().FindType(
                        meta_param->GetAttributeName());
                    COFFEE_Assert(enum_type!=NULL, core::ERROR_CODE_MetaSystem, "Invalid enum type");
                    name = enum_type->GetValues()[child_index]->GetName();
                }
            }
            else
            {
                name = *(basic::String *) object->GetData();
            }

            _ComboBox->AddItem(name);
        }

        if(GetObjectInfo().GetChildCount() == 0)
        {
            _CreateHierarchy(NONE);
        }
        else
        {
            _CreateHierarchy(0);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void PropertyArrayCombo::_CreateHierarchy(uint32 item_index)
    {
        for (int32 child_index=0 ; child_index<(int32)_Group->GetChildCount() ; ++child_index)
        {
            Window* child = &_Group->GetChildWindow(child_index);
            if (child!=&_Group->GetGrooveButton() && child!=_ComboBox)
            {
                int32 count = (int32)_Group->GetChildCount();
                child->Destroy();
                if (count!=_Group->GetChildCount())
                    --child_index;
            }
        }

        if(item_index!=NONE)
        {
            _ComboBox->SelectItem(item_index);

            PropertyList::CreateHierarchy(
                GetObjectInfo().GetChild(item_index),
                *_Group,
                PROPERTY_FLAG_Root);
        }

        _Group->GetLayout().Update();
    }

}
}
//------------------------------------------------------------------------------------------------//
