#include "wide/ui/property/basic/text/ui_property_text.h"
#include "wide/ui/window/ui_window_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::PropertyText);
        COFFEE_Ancestor(ui::Property);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PropertyText::PropertyText() :
        _EditButton(NULL),
        _EditDialog(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    PropertyText::~PropertyText()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyText::CreateContent()
    {
        widget::Label* text;

        text = COFFEE_New(widget::Label);
        text->Create(this, basic::Vector2i(0, 0), basic::Vector2i(84, 16));
        text->SetText(GetName());
        text->GetLayout().SetCanvas(100, true);

        _EditButton = COFFEE_New(widget::Button);
        _EditButton->Create(this, basic::Vector2i(),
            basic::Vector2i(16, 16), widget::BUTTON_STYLE_PushLike);
        _EditButton->GetLayout().SetCanvas(16, false);
        _EditButton->SetHelpText(basic::String("Edit text"));
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(PropertyText, Property)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Pressed, widget::Widget, _EditButton, OnEdit)
        COFFEE_RegisterEventHandler(shell::EVENT_MESSAGE_Destroyed, shell::EventHandler, OnClose)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool PropertyText::OnEdit(shell::Event& event)
    {
        if (_EditDialog==NULL)
        {
            _EditDialog = COFFEE_New(PropertyTextDialog);
            _EditDialog->Create(NULL, basic::Vector2i(), basic::Vector2i(400, 300));
            _EditDialog->PositionToCenter();
            _EditDialog->SetTitleBarText(basic::String("Edit ") + GetName());
            _EditDialog->SetText(*(basic::Text *) GetData());

            COFFEE_RegisterExternEventHandler(shell::EVENT_MESSAGE_Destroyed,
                shell::EventHandler::GetClassMetaType(), *_EditDialog, OnCloseEditDialog);

            COFFEE_RegisterExternEventHandler(widget::EVENT_Changed,
                widget::Widget::GetClassMetaType(), *_EditDialog, OnTextChanged);
        }
        else
        {
            _EditDialog->Destroy();
            _EditDialog = NULL;
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyText::OnClose(shell::Event& event)
    {
        if (_EditDialog!=NULL)
        {
            COFFEE_UnregisterExternEventHandler(*_EditDialog);
            _EditDialog->Destroy();
            _EditDialog = NULL;
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyText::OnTextChanged(shell::Event& event)
    {
        if (event.GetTarget()!=_EditDialog)
            return false;

        PropertyList::OnPreModify(this);
        (*(basic::Text*)GetData()) = _EditDialog->GetText();
        SendEvent(PROPERTY_MESSAGE_Modified, this);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyText::OnCloseEditDialog(shell::Event& event)
    {
        if (event.GetTarget()==_EditDialog)
        {
            _EditDialog = NULL;
            _EditButton->SetState(widget::BUTTON_STATE_Off);
        }
        return true;
    }

}
}
