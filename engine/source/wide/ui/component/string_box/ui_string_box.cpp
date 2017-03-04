#include "wide/ui/component/string_box/ui_string_box.h"
#include "wide/ui/window/ui_window_manager.h"

namespace coffee
{
namespace ui
{
    //-FUNCTIONS----------------------------------------------------------------------------------//

    basic::String COFFEE_API DoStringBox(basic::String caption, basic::String message,
        basic::String default_string, basic::String accept_button)
    {
        StringBox* box = COFFEE_New(StringBox);
        box->Create(caption, message, default_string, accept_button);
        basic::String value;
        if (box->DoModal())
        {
            value = box->GetValue();
            box->Destroy();
        }
        return value;
    }
}

    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::StringBox);
        COFFEE_Ancestor(ui::widget::Dialog);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    StringBox::StringBox() :
        _MessageText(NULL),
        _EditBox(NULL),
        _AcceptButton(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    StringBox::~StringBox()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    const basic::String& StringBox::GetValue() const
    {
        return _EditBox->GetText();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void StringBox::Create(basic::String caption, basic::String message,
        basic::String default_string, basic::String accept_button)
    {
        widget::Dialog::Create(NULL, basic::Vector2i(100, 100), basic::Vector2i(400, 150));

        SetTitleBarText(caption);
        SetStyle(GetStyle() & ~(uint32) WINDOW_STYLE_Resizeable);
        PositionToCenter();

        _MessageText = COFFEE_New(widget::Label);
        _MessageText->Create(this, basic::Vector2i(10, 30), basic::Vector2i(360, 20));
        _MessageText->SetText(message);
        
        _EditBox = COFFEE_New(widget::EditBox);
        _EditBox->Create(this, basic::Vector2i(10, 60), 360);
        _EditBox->SetText(default_string);

        _AcceptButton = COFFEE_New(widget::Button);
        _AcceptButton->Create(this, basic::Vector2i(320, 90), basic::Vector2i(70, 20),
            widget::BUTTON_STYLE_Default);
        _AcceptButton->SetText(accept_button);
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(StringBox, widget::Dialog)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Pressed, widget::Widget, _AcceptButton, OnAccept)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool StringBox::OnAccept(shell::Event& event)
    {
        WindowManager::Get().AcceptModalWindow();
        return true;
    }

}
}
