#include "wide/ui/component/rename_box/ui_rename_box.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::RenameBox);
        COFFEE_Ancestor(ui::widget::EditBox);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    RenameBox::RenameBox() :
        _ItHasToSkipChanges(true)
    {
    }

    //--------------------------------------------------------------------------------------------//

    RenameBox::~RenameBox()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void RenameBox::Create(Window* item, basic::String text)
    {
        COFFEE_Assert(item!=NULL, core::ERROR_CODE_IncorrectUsage, "Need to be attached to an item.");
        widget::EditBox::Create(item, basic::Vector2i(
            item->GetClientRect().GetMinimum().X+2, -item->GetClientRect().Position.Y+2),
            item->GetClientRect().Size.X-item->GetClientRect().GetMinimum().X-4);
        SetStyle(GetStyle() | WINDOW_STYLE_NoParentClip | WINDOW_STYLE_DrawFrame);
        SetText(text);
        SetFocus();
        SetCursorPosition(0);

        uint32 file_token = text.Find('.');
        SetCursorSize(file_token==NONE?text.GetLength():file_token);
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(RenameBox, widget::EditBox)
        COFFEE_RegisterEventHandler(input::EVENT_KeyReleased, input::Handler, OnKeyReleased)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_KillFocus, Window, OnKillFocus)
        COFFEE_RegisterEventHandler(widget::EVENT_Changed, widget::Widget, OnChanged)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool RenameBox::OnKeyReleased(shell::Event& event)
    {
        input::EventKey* parameter = (input::EventKey*)
            event.GetParameters().GetCustomParameter();
        if (parameter->Key==input::KEY_Return)
        {
            shell::EventCode event_code((uint32)widget::EVENT_Changed, widget::Widget::GetClassMetaType());
            shell::EventParameters event_parameters;
            shell::Event event;
            event.Set(event_code, event_parameters,
                shell::EVENT_FLAG_StopWhenHandled|shell::EVENT_FLAG_ForwardToParent);
            _ItHasToSkipChanges = false;
            shell::EventHandler::SendImmediateEvent(event);
            _ItHasToSkipChanges = true;
            Destroy();
        }
        return true;
    }
        
    //--------------------------------------------------------------------------------------------//

    bool RenameBox::OnKillFocus(shell::Event& event)
    {
        Destroy();
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool RenameBox::OnChanged(shell::Event& event)
    {
        return _ItHasToSkipChanges;
    }

}
}
