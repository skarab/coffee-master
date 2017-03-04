//------------------------------------------------------------------------------------------------//
/// @file wide/ui/property/scalar/ui_property_bool.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/ui/property/scalar/ui_property_bool.h"
#include "wide/ui/window/ui_window_manager.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::PropertyBool);
        COFFEE_Ancestor(ui::Property);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PropertyBool::PropertyBool() :
        _CheckBox(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    PropertyBool::~PropertyBool()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyBool::CreateContent()
    {
        _CheckBox = COFFEE_New(widget::CheckBox);
        _CheckBox->Create(this, basic::Vector2i(), basic::Vector2i(GetClientRect().Size.X, 20),
            widget::CHECK_BOX_STYLE_Default);
        _CheckBox->SetText(GetName());
        _CheckBox->GetLayout().SetCanvas(100, true);

        if (*((bool*)GetData()))
            _CheckBox->SetState(widget::CHECK_BOX_STATE_Checked);

        if (GetObjectInfo().IsAttribute() && GetObjectInfo().GetAttribute()._Param!=NULL
            && ((GetObjectInfo().GetAttribute()._Param->GetMode() & meta::MODE_ReadOnly) > 0))
        {
            _CheckBox->Enable(false);
        }
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(PropertyBool, Property)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Pressed, widget::Widget, _CheckBox, OnCheck)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool PropertyBool::OnCheck(shell::Event& event)
    {
        PropertyList::OnPreModify(this);
        *((bool*)GetData()) = (_CheckBox->GetState()==widget::CHECK_BOX_STATE_Checked);
        SendEvent(PROPERTY_MESSAGE_Modified, this);
        return true;
    }

}
}
//------------------------------------------------------------------------------------------------//
