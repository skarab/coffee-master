#include "wide/ui/widget/combo_box/widget_combo_box.h"
#include "wide/ui/window/ui_window_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::widget::ComboBox);
        COFFEE_Ancestor(ui::widget::Widget);
    COFFEE_EndType();

namespace ui
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ComboBox::ComboBox() :
        _EditBox(NULL),
        _ComboList(NULL),
        _ComboButton(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ComboBox::~ComboBox()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    uint32 ComboBox::GetSelectedIndex() const
    {
        return _ComboList->GetSelectedIndex();
    }

    //--------------------------------------------------------------------------------------------//

    basic::String ComboBox::GetSelectedString() const
    {
        if (GetSelectedIndex()==NONE)
            return "";

        return GetItemString(GetSelectedIndex());
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Prow< basic::String*, true >& ComboBox::GetItemArray() const
    {
        return _ComboList->GetItemArray();
    }

    //--------------------------------------------------------------------------------------------//

    const basic::String& ComboBox::GetItemString(uint32 item_index) const
    {
        return _ComboList->GetItemString(item_index);
    }

    //--------------------------------------------------------------------------------------------//

    const void* ComboBox::GetItemData(uint32 item_index) const
    {
        return _ComboList->GetItemData(item_index);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ComboBox::Create(Window* parent, const basic::Vector2i& position, int32 width,
        uint32 style)
    {
        Window::Create(
            parent,
            position,
            basic::Vector2i(width, GetEditBoxSize() + GetBorders().Y * 2),
            WINDOW_STYLE_Focusable | style);

        GetLayout().SetStyle(
            LAYOUT_STYLE_HorizontalCanvas
            | LAYOUT_STYLE_StickChildren);

        _EditBox = COFFEE_New(EditBox);
        _EditBox->Create(this, basic::Vector2i(1, 0), 10, EDIT_BOX_STYLE_ReadOnly);
        _EditBox->GetLayout().SetCanvas(100, true);

        _ComboButton = COFFEE_New(Button);
        _ComboButton->Create(this,
            basic::Vector2i(basic::Vector2i().X, 0),
            basic::Vector2i(GetButtonSize(), GetButtonSize()),
            BUTTON_STYLE_Default);
        _ComboButton->GetLayout().SetCanvas(GetButtonSize(), false);
        _ComboButton->SetImage(SKIN_ICON_Combo);

        _ComboList = COFFEE_New(ListView);
        _ComboList->Create(this,
            basic::Vector2i(GetBorders().X, GetSize().Y + GetBorders().Y),
            basic::Vector2i(GetSize().X - GetBorders().X * 2, GetSize().Y * 6));
        _ComboList->SetStyle(WINDOW_STYLE_NoParentClip
            | WINDOW_STYLE_Activable);
        _ComboList->Show(false);
    }

    //--------------------------------------------------------------------------------------------//

    int32 ComboBox::AddItem(basic::String string, void* data)
    {
        return _ComboList->AddItem(string, data);
    }

    //--------------------------------------------------------------------------------------------//

    void ComboBox::RemoveItems()
    {
        _EditBox->SetText("");
        _ComboList->RemoveItems();
    }

    //--------------------------------------------------------------------------------------------//

    bool ComboBox::SelectItem(uint32 item_index)
    {
        if (_ComboList->SelectItem(item_index))
        {
            _EditBox->SetText(*_ComboList->GetItemArray()[_ComboList->GetSelectedIndex()]);
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool ComboBox::SelectItem(basic::String string)
    {
        if (_ComboList->SelectItem(string))
        {
            _EditBox->SetText(*_ComboList->GetItemArray()[_ComboList->GetSelectedIndex()]);
            return true;
        }
        return false;
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(ComboBox, Widget)
        COFFEE_RegisterTargetEventHandler(EVENT_Pressed, Widget, _ComboButton, OnComboButton)
        COFFEE_RegisterTargetEventHandler(EVENT_Select, Widget, _EditBox, OnSelectText)
        COFFEE_RegisterTargetEventHandler(WINDOW_EVENT_Deactivate, Window, _ComboList, OnComboListKillFocus)
        COFFEE_RegisterTargetEventHandler(EVENT_Select, Widget, _ComboList, OnComboListSelectItem)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool ComboBox::OnComboButton(shell::Event& event)
    {
        if(!_ComboList->HasState(WINDOW_STATE_Visible))
            _ComboList->Activate();

        _ComboList->Show(!_ComboList->HasState(WINDOW_STATE_Visible));

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool ComboBox::OnSelectText(shell::Event& event)
    {
        if (!_ComboList->HasState(WINDOW_STATE_Visible))
            _ComboList->Activate();

        _ComboList->Show(!_ComboList->HasState(WINDOW_STATE_Visible));
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool ComboBox::OnComboListKillFocus(shell::Event& event)
    {
        if (_ComboList->HasState(WINDOW_STATE_Visible))
            _ComboList->Show(false);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool ComboBox::OnComboListSelectItem(shell::Event& event)
    {
        if (_ComboList->GetSelectedIndex() != NONE)
            _EditBox->SetText(*_ComboList->GetItemArray()[_ComboList->GetSelectedIndex()]);

        if (_ComboList->HasState(WINDOW_STATE_Visible))
        {
            _ComboList->Show(false);

            Window* activable_parent = FindActivableParent();
            if (activable_parent != NULL)
            {
                _ComboButton->SetFocus();
                activable_parent->Activate();
            }
        }

        SendEvent(EVENT_Select);
        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ComboBox::_UpdateClientArea()
    {
        Window::_UpdateClientArea();

        if(_ComboList != NULL)
        {
            _ComboList->SetPosition(basic::Vector2i(
                GetBorders().X, GetSize().Y + GetBorders().Y));
            _ComboList->SetSize(basic::Vector2i(
                GetSize().X - GetBorders().X * 2, GetSize().Y * 6));
            _ComboList->PositionToDesktop();
        }
    }

}
}
}
