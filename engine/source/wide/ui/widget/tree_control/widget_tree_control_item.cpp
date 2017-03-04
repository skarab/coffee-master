#include "wide/ui/widget/tree_control/widget_tree_control_item.h"
#include "wide/ui/window/ui_window_context.h"
#include "wide/ui/window/ui_window_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::widget::TreeControlItem);
        COFFEE_Ancestor(ui::widget::Widget);
    COFFEE_EndType();

namespace ui
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    TreeControlItem::TreeControlItem() :
        _ItemHeight(20),
        _TreeButton(NULL),
        _CheckBox(NULL),
        _Thumbnail(NULL),
        _ItIsOpen(false)
    {
    }

    //--------------------------------------------------------------------------------------------//

    TreeControlItem::~TreeControlItem()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void TreeControlItem::SetText(const basic::String& text)
    {
        _Text = text;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::String& TreeControlItem::GetText() const
    {
        return _Text;
    }

    //--------------------------------------------------------------------------------------------//

    const Button& TreeControlItem::GetTreeButton() const
    {
        return *_TreeButton;
    }

    //--------------------------------------------------------------------------------------------//

    Button& TreeControlItem::GetTreeButton()
    {
        return *_TreeButton;
    }

    //--------------------------------------------------------------------------------------------//

    void TreeControlItem::SetImage(const SKIN_ICON& icon)
    {
        if (HasExtendedStyle(VIEW_CONTROL_STYLE_ShowCheckBoxes))
            return;

        if (_Thumbnail!=NULL)
            _Thumbnail->Destroy();

        _Thumbnail = COFFEE_New(Image);
        _Thumbnail->Create(this, basic::Vector2i(_ItemHeight, 1),
            basic::Vector2i(_ItemHeight-2, _ItemHeight-2), IMAGE_STYLE_NoBorders);
        _Thumbnail->SetStyle(_Thumbnail->GetStyle() | (uint32) WINDOW_STYLE_NoParentClientClip);
        _Thumbnail->SetImage(icon);
    }
    
    //--------------------------------------------------------------------------------------------//

    void TreeControlItem::SetImage(storage::Path texture_path)
    {
        if (HasExtendedStyle(VIEW_CONTROL_STYLE_ShowCheckBoxes))
            return;

        if (_Thumbnail!=NULL)
            _Thumbnail->Destroy();

        _Thumbnail = COFFEE_New(Image);
        _Thumbnail->Create(this, basic::Vector2i(_ItemHeight, 1),
            basic::Vector2i(_ItemHeight-2, _ItemHeight-2), IMAGE_STYLE_NoBorders);
        _Thumbnail->SetStyle(_Thumbnail->GetStyle() | (uint32) WINDOW_STYLE_NoParentClientClip);
        _Thumbnail->SetImage(texture_path);
    }

    //--------------------------------------------------------------------------------------------//

    void TreeControlItem::SetImage(graphics::Texture texture_instance)
    {
        if (HasExtendedStyle(VIEW_CONTROL_STYLE_ShowCheckBoxes))
            return;

        if (_Thumbnail!=NULL)
            _Thumbnail->Destroy();

        _Thumbnail = COFFEE_New(Image);
        _Thumbnail->Create(this, basic::Vector2i(_ItemHeight, 1),
            basic::Vector2i(_ItemHeight-2, _ItemHeight-2), IMAGE_STYLE_NoBorders);
        _Thumbnail->SetStyle(_Thumbnail->GetStyle() | (uint32) WINDOW_STYLE_NoParentClientClip);
        _Thumbnail->SetImage(texture_instance);
    }

    //--------------------------------------------------------------------------------------------//

    int32 TreeControlItem::GetItemHeight() const
    {
        return _ItemHeight;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool TreeControlItem::IsOpen() const
    {
        return _ItIsOpen;
    }

    //--------------------------------------------------------------------------------------------//

    CHECK_BOX_STATE TreeControlItem::GetCheckBoxState() const
    {
        COFFEE_Assert(_CheckBox!=NULL, core::ERROR_CODE_IncorrectUsage, "TreeControlItem has no checkbox");
        return _CheckBox->GetState();
    }

    //--------------------------------------------------------------------------------------------//

    storage::Path TreeControlItem::GetPath() const
    {
        storage::Path path;
        if (HasParent() && GetParent().IsA<TreeControlItem>())
            path = static_cast<const TreeControlItem&>(GetParent()).GetPath();
        path += "/";
        path += GetText();
        return path;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void TreeControlItem::Create(Window* parent, const basic::Vector2i& position,
        const basic::Vector2i& size, uint32 style)
    {
        Window::Create(parent, position, size, WINDOW_STYLE_Focusable);

        SetExtendedStyle(style);
        SetText(basic::String("Item"));

        GetLayout().SetStyle(LAYOUT_STYLE_VerticalCanvas
            | LAYOUT_STYLE_VerticalShrink
            | LAYOUT_STYLE_StickChildren
            | LAYOUT_STYLE_HorizontalExpand);

        _TreeButton = COFFEE_New(Button);
        _TreeButton->Create(this, basic::Vector2i(1, 1),
            basic::Vector2i(_ItemHeight-6, _ItemHeight-6), BUTTON_STYLE_HideFrame);
        _TreeButton->SetStyle(_TreeButton->GetStyle() | (uint32) WINDOW_STYLE_NoParentClientClip);
        _TreeButton->SetImage(SKIN_ICON_Down);

        if (HasExtendedStyle(VIEW_CONTROL_STYLE_ShowCheckBoxes))
        {
            _CheckBox = COFFEE_New(CheckBox);
            _CheckBox->Create(this, basic::Vector2i(_ItemHeight, 1),
                basic::Vector2i(_ItemHeight-6, _ItemHeight-6), CHECK_BOX_STYLE_ThreeStates);
            _CheckBox->SetStyle(_CheckBox->GetStyle() | (uint32) WINDOW_STYLE_NoParentClientClip);
        }

        Open(false);
    }

    //--------------------------------------------------------------------------------------------//

    void TreeControlItem::Open(bool it_is_open)
    {
        bool notify = _ItIsOpen!=it_is_open;
        _ItIsOpen = it_is_open;
        if (_ItIsOpen)
        {
            _TreeButton->SetImage(ui::SKIN_ICON_Right);
            SetSize(basic::Vector2i(GetSize().X, GetLayout().ComputeWindowSize().Y));
            for (uint32 i=0 ; i<GetChildCount() ; ++i)
            {
                if (GetChild(i).IsA<TreeControlItem>())
                    GetChildWindow(i).Show(true);
            }
        }
        else
        {
            _TreeButton->SetImage(ui::SKIN_ICON_Down);
            SetSize(basic::Vector2i(GetSize().X, (int32)(_ItemHeight + 2 * GetBorders().Y)));
            for (uint32 i=0 ; i<GetChildCount() ; ++i)
            {
                if (GetChild(i).IsA<TreeControlItem>())
                    GetChildWindow(i).Show(false);
            }
        }
        
        if (notify)
        {
            SendEvent(EVENT_Select);
            SendEvent(EVENT_Changed);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void TreeControlItem::SetCheckBoxState(CHECK_BOX_STATE state)
    {
        COFFEE_Assert(_CheckBox!=NULL, core::ERROR_CODE_IncorrectUsage, "TreeControlItem has no checkbox");
        _CheckBox->SetState(state);
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(TreeControlItem, Widget)
        COFFEE_RegisterTargetEventHandler(EVENT_Pressed, Widget, _TreeButton, OnTreeButton)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_SetFocus, Window, OnSetFocus)
        COFFEE_RegisterEventHandler(input::EVENT_MouseDoubleClick, input::Handler, OnMouseDoubleClick)
        COFFEE_RegisterEventHandler(input::EVENT_MouseLeftButtonPressed, input::Handler, OnMouseLeftButtonPressed)
        COFFEE_RegisterEventHandler(input::EVENT_MouseLeftButtonReleased, input::Handler, OnMouseLeftButtonReleased)
        COFFEE_RegisterEventHandler(input::EVENT_MouseRightButtonPressed, input::Handler, OnMouseRightButtonPressed)
        COFFEE_RegisterTargetEventHandler(EVENT_Pressed, Widget, _CheckBox, OnCheckBox)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool TreeControlItem::OnTreeButton(shell::Event & event)
    {
        Open(!_ItIsOpen);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool TreeControlItem::OnSetFocus(shell::Event& event)
    {
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool TreeControlItem::OnMouseDoubleClick(shell::Event& event)
    {
        Open(!_ItIsOpen);
        SendEvent(EVENT_Activate);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool TreeControlItem::OnMouseLeftButtonPressed(shell::Event& event)
    {
        if (FindParent<TreeControl>()->GetSelectedItem()==this)
            SendEvent(EVENT_Edit);
        return false;
    }
    
    //--------------------------------------------------------------------------------------------//

    bool TreeControlItem::OnMouseLeftButtonReleased(shell::Event& event)
    {
        input::EventMouse* mouse_parameter = (input::EventMouse*)event.GetParameters().GetCustomParameter();
        bool it_is_inside = GetParentWindow().HitTest(mouse_parameter->Position, WINDOW_STYLE_Focusable)==this;
        if (it_is_inside)
            SendEvent(EVENT_Select);
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool TreeControlItem::OnMouseRightButtonPressed(shell::Event& event)
    {
        SendEvent(EVENT_ContextMenu);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool TreeControlItem::OnCheckBox(shell::Event& event)
    {
        // User click time
        if (event.GetParameters().GetCustomParameter()==NULL)
        {
            // Fix alternate check
            if (_CheckBox->GetState()==CHECK_BOX_STATE_AlternateChecked)
                _CheckBox->SetState(CHECK_BOX_STATE_UnChecked);

            // Forward to parent
            if (HasParent() && GetParent().IsA<TreeControlItem>())
                static_cast<TreeControlItem&>(GetParent())._CheckBox->SendEvent(EVENT_Pressed, (void*)1);
        }

        // Parents update
        if ((int32)event.GetParameters().GetCustomParameter()==1)
        {
            // Generate correct state from children
            uint32 state = 0;
            uint32 count = 0;
            for (uint32 i=0 ; i<GetChildCount() ; ++i)
            {
                if (GetChild(i).IsA<TreeControlItem>())
                {
                    if (static_cast<TreeControlItem&>(GetChild(i))._CheckBox->GetState()==CHECK_BOX_STATE_AlternateChecked)
                    {
                        state += GetChildCount()+1;
                        break;
                    }
                    else if (static_cast<TreeControlItem&>(GetChild(i))._CheckBox->GetState()==CHECK_BOX_STATE_Checked)
                    {
                        ++state;
                    }
                    ++count;
                }
            }

            // Forward the changes to parent if required
            if (state==0) {}
            else if (state==count) { state = 1; }
            else state = 2;
            if (_CheckBox->GetState()!=(CHECK_BOX_STATE)state)
            {
                _CheckBox->SetState((CHECK_BOX_STATE)state);

                if (HasParent() && GetParent().IsA<TreeControlItem>())
                    static_cast<TreeControlItem&>(GetParent())._CheckBox->SendEvent(EVENT_Pressed, (void*)1);
            }
        }

        // Set children states at user click time and recursively
        if (event.GetParameters().GetCustomParameter()==NULL
            || (int32)event.GetParameters().GetCustomParameter()==2)
        {
            for (uint32 i=0 ; i<GetChildCount() ; ++i)
            {
                if (GetChild(i).IsA<TreeControlItem>()
                    && static_cast<TreeControlItem&>(GetChild(i))._CheckBox->GetState()!=_CheckBox->GetState())
                {
                    static_cast<TreeControlItem&>(GetChild(i))._CheckBox->SetState(_CheckBox->GetState());
                    static_cast<TreeControlItem&>(GetChild(i))._CheckBox->SendEvent(EVENT_Pressed, (void*)2);
                }
            }
        }
        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void TreeControlItem::_UpdateClientArea()
    {
        Window::_UpdateClientArea();
        basic::Rectangle client_rect = GetClientRect();

        client_rect.Position = basic::Vector2i(
            client_rect.Position.X + _ItemHeight,
            client_rect.Position.Y + _ItemHeight + GetBorders().Y);
        client_rect.Size = basic::Vector2i(
            client_rect.Size.X - _ItemHeight,
            client_rect.Size.Y - _ItemHeight - GetBorders().Y);

        if (_TreeButton!=NULL)
        {
            _TreeButton->SetPosition(basic::Vector2i(
                -_ItemHeight+1-GetBorders().X/2,
                -_ItemHeight+1-GetBorders().Y));
        }

        if (_CheckBox!=NULL)
        {
            _CheckBox->SetPosition(basic::Vector2i(
                0, -_ItemHeight+1-GetBorders().Y));
        }
        else if (_Thumbnail!=NULL)
        {
            _Thumbnail->SetPosition(basic::Vector2i(
                0, -_ItemHeight+1-GetBorders().Y));
        }

        _SetClientRect(client_rect);
    }

}
}
}
