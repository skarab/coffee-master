#include "wide/ui/property/basic/text/ui_property_string.h"
#include "wide/ui/window/ui_window_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::PropertyString);
        COFFEE_Ancestor(ui::Property);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PropertyString::PropertyString() :
        _Text(NULL),
        _EditBox(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    PropertyString::~PropertyString()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyString::CreateContent()
    {
        _Text = COFFEE_New(widget::Label);
        _Text->Create(this, basic::Vector2i(0, 0), basic::Vector2i(84, 16));
        _Text->SetText(GetName());
        _Text->GetLayout().SetCanvas(GetTextControlSize(), true);
        
        _EditBox = COFFEE_New(widget::EditBox);
        _EditBox->Create(this, basic::Vector2i(), 10);
        _EditBox->GetLayout().SetCanvas(100 - GetTextControlSize(), true);
        _EditBox->SetText(*(basic::String *) GetData());
        
        if (GetObjectInfo().IsAttribute() && GetObjectInfo().GetAttribute()._Param!=NULL
            && ((GetObjectInfo().GetAttribute()._Param->GetMode() & meta::MODE_ReadOnly) > 0))
        {
            _EditBox->Enable(false);
        }
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(PropertyString, Property)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Changed, widget::Widget, _EditBox, OnTextChanged)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool PropertyString::OnTextChanged(shell::Event& event)
    {
        PropertyList::OnPreModify(this);
        *((basic::String*)GetData()) = _EditBox->GetText();
        SendEvent(PROPERTY_MESSAGE_Modified, this);
        return true;
    }

}
}
