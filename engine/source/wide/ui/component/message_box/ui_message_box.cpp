#include "wide/ui/component/message_box/ui_message_box.h"
#include "wide/ui/window/ui_window_manager.h"

namespace coffee
{
namespace ui
{
    //-FUNCTIONS----------------------------------------------------------------------------------//

    bool COFFEE_API DoMessageBox(basic::String caption, basic::String message, uint32 flags)
    {
        MessageBox* message_box;
        message_box = COFFEE_New(MessageBox);
        message_box->Create(caption, message, flags);
        if (message_box->DoModal())
        {
            message_box->Destroy();
            return true;
        }
        return false;
    }
}

    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::MessageBox);
        COFFEE_Ancestor(ui::widget::Dialog);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    MessageBox::MessageBox() :
        _Flags(0),
        _MessageText(NULL),
        _OkButton(NULL),
        _CancelButton(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    MessageBox::~MessageBox()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void MessageBox::Create(basic::String caption, basic::String message, uint32 flags)
    {
        widget::Dialog::Create(NULL, basic::Vector2i(100, 100), basic::Vector2i(400, 150));

        SetTitleBarText(caption);
        SetStyle(GetStyle() & ~(uint32) WINDOW_STYLE_Resizeable);
        PositionToCenter();

        _Flags = flags;
        _MessageText = COFFEE_New(widget::Label);
        _MessageText->Create(this, basic::Vector2i(10, 30), basic::Vector2i(360, 20));
        _MessageText->SetText(message);
        
        if(_Flags==MESSAGE_BOX_FLAG_Ok)
        {
            _OkButton = COFFEE_New(widget::Button);
            _OkButton->Create(this, basic::Vector2i(320, 90), basic::Vector2i(70, 30),
                widget::BUTTON_STYLE_Default);
            _OkButton->SetText(basic::String("Ok"));
        }
        else if(_Flags!=MESSAGE_BOX_FLAG_None)
        {
            _OkButton = COFFEE_New(widget::Button);
            _OkButton->Create(this, basic::Vector2i(5, 90), basic::Vector2i(70, 30),
                widget::BUTTON_STYLE_Default);
            
            _CancelButton = COFFEE_New(widget::Button);
            _CancelButton->Create(this, basic::Vector2i(320, 90), basic::Vector2i(70, 30),
                widget::BUTTON_STYLE_Default);
            
            if(_Flags==MESSAGE_BOX_FLAG_OkCancel)
            {
                _OkButton->SetText(basic::String("Ok"));
                _CancelButton->SetText(basic::String("Cancel"));
            }
            else
            {
                _OkButton->SetText(basic::String("Yes"));
                _CancelButton->SetText(basic::String("No"));
            }
        }
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(MessageBox, widget::Dialog)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Pressed, widget::Widget, _OkButton, OnOk)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Pressed, widget::Widget, _CancelButton, OnCancel)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool MessageBox::OnOk(shell::Event& event)
    {
        WindowManager::Get().AcceptModalWindow();
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool MessageBox::OnCancel(shell::Event& event)
    {
        Destroy();
        return true;
    }

}
}
