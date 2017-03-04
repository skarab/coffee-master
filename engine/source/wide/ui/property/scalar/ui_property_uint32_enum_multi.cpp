//------------------------------------------------------------------------------------------------//
/// @file wide/ui/property/scalar/ui_property_uint32_enum_multi.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/ui/property/scalar/ui_property_uint32_enum_multi.h"
#include "wide/ui/property/ui_property_list.h"
#include "wide/ui/window/ui_window_manager.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::PropertyUInt32EnumMulti);
        COFFEE_Ancestor(ui::Property);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PropertyUInt32EnumMulti::PropertyUInt32EnumMulti() :
        _Group(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    PropertyUInt32EnumMulti::~PropertyUInt32EnumMulti()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyUInt32EnumMulti::CreateContent()
    {
        _Group = COFFEE_New(widget::Group);
        _Group->Create(this, basic::Vector2i(),
            basic::Vector2i(GetClientRect().Size.X, 20));
        _Group->SetTitleBarText(GetName());
        
        _InitializeContent();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(PropertyUInt32EnumMulti, Property)
        COFFEE_RegisterEventHandler(widget::EVENT_Pressed, widget::Widget, OnCheckItem)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool PropertyUInt32EnumMulti::OnCheckItem(shell::Event& event)
    {
        uint32 flag_index;
        widget::CheckBox* check_box;

        check_box = (widget::CheckBox*)event.GetTarget();
        flag_index = (uint32)check_box->GetData();
        _EnableFlag(flag_index, check_box->GetState()==widget::CHECK_BOX_STATE_Checked);
        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyUInt32EnumMulti::_EnableFlag(uint32 flag_index, bool it_has_to_enable)
    {
        PropertyList::OnPreModify(this);
        COFFEE_EnableFlag(*((uint32*)GetData()), 1<<flag_index, it_has_to_enable);
        SendEvent(PROPERTY_MESSAGE_Modified, this);
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyUInt32EnumMulti::_IsFlagEnabled(uint32 flag_index) const
    {
        return (((*((const uint32*)GetData())) & (1 << flag_index)) > 0);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyUInt32EnumMulti::_InitializeContent()
    {
        meta::ParamEnumMulti* meta_param;
        meta::Enum* enum_type;
        uint32 flag_index;

        meta_param = (meta::ParamEnumMulti*) GetObjectInfo().GetAttribute()._Param;
        enum_type = (meta::Enum*)meta::Types::Get().FindType(meta_param->GetEnumName());
        COFFEE_Assert(enum_type!=NULL, core::ERROR_CODE_MetaSystem, "Invalid enum type");

        for(flag_index=0 ; flag_index<enum_type->GetValues().GetSize() ; ++flag_index)
        {
            widget::CheckBox* check_box;
            check_box = COFFEE_New(widget::CheckBox);
            check_box->Create(_Group, basic::Vector2i(), basic::Vector2i(20, 20));
            check_box->GetLayout().SetStyle(LAYOUT_STYLE_HorizontalCanvas | LAYOUT_STYLE_HorizontalExpand);
            check_box->SetText(enum_type->GetValues()[flag_index]->GetName());
            check_box->SetState(_IsFlagEnabled(flag_index) ? widget::CHECK_BOX_STATE_Checked
                : widget::CHECK_BOX_STATE_UnChecked);
            check_box->SetData((void*)flag_index);

            if (GetObjectInfo().IsAttribute() && GetObjectInfo().GetAttribute()._Param!=NULL
                && ((GetObjectInfo().GetAttribute()._Param->GetMode() & meta::MODE_ReadOnly) > 0))
            {
                check_box->Enable(false);
            }
        }
    }

}
}
//------------------------------------------------------------------------------------------------//
