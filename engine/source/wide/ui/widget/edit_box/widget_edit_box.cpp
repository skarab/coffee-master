#include "wide/ui/widget/edit_box/widget_edit_box.h"
#include "wide/ui/window/ui_window_manager.h"
#include "wide/edition/selection/edition_selection_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::widget::EditBox);
        COFFEE_Ancestor(ui::widget::Widget);
    COFFEE_EndType();

namespace ui
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    EditBox::EditBox() :
        _CursorPosition(0),
        _CursorSize(0),
        _VisibilityStart(0),
        _VisibilityStop(0),
        _ItHasToRenderCursor(false),
        _ItIsSelecting(false),
        _OldVisibility(0),
        _ItHasToFit(false)
    {
    }

    //--------------------------------------------------------------------------------------------//

    EditBox::~EditBox()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void EditBox::SetText(const basic::String& text)
    {
        _Text = text;
        _CursorPosition = 0;
        _CursorSize = 0;
        _VisibilityStart = 0;
        _UpdateVisibility();
        _FitToContent();
    }

    //--------------------------------------------------------------------------------------------//

    void EditBox::SetEditedText(const basic::String& text)
    {
        if (text!=_Text)
        {
            int32 cursor_position = _CursorPosition;
            int32 visibility_start = _VisibilityStart;
            SetText(text);
            SetCursorPosition(cursor_position);
            SetVisibilityStart(visibility_start);
        }
    }

    //--------------------------------------------------------------------------------------------//

    const basic::String& EditBox::GetText() const
    {
        return _Text;
    }

    //--------------------------------------------------------------------------------------------//

    void EditBox::SetCursorPosition(int32 cursor_position)
    {
        _CursorPosition = Minimum(cursor_position, (int32) _Text.GetLength());
        _CursorSize = 0;
    }

    //--------------------------------------------------------------------------------------------//

    int32 EditBox::GetCursorPosition() const
    {
        return _CursorPosition;
    }

    //--------------------------------------------------------------------------------------------//

    void EditBox::SetCursorSize(int32 cursor_size)
    {
        _CursorSize = cursor_size;
    }

    //--------------------------------------------------------------------------------------------//

    int32 EditBox::GetCursorSize() const
    {
        return _CursorSize;
    }

    //--------------------------------------------------------------------------------------------//

    void EditBox::SetVisibilityStart(int32 visibility_start)
    {
        _VisibilityStart = visibility_start;
        _OldVisibility = _VisibilityStart;
    }

    //--------------------------------------------------------------------------------------------//

    int32 EditBox::GetVisibilityStart() const
    {
        return _VisibilityStart;
    }

    //--------------------------------------------------------------------------------------------//

    int32 EditBox::GetVisibilityStop() const
    {
        return _VisibilityStop;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool EditBox::HasToRenderCursor() const
    {
        return _ItHasToRenderCursor && !IsReadOnly();
    }

    //--------------------------------------------------------------------------------------------//

    bool EditBox::IsReadOnly() const
    {
        return HasExtendedStyle((uint32) EDIT_BOX_STYLE_ReadOnly) || !IsEnabled();
    }

    //--------------------------------------------------------------------------------------------//

    basic::String EditBox::GetVisibleText() const
    {
        return GetText().GetCenter(GetVisibilityStart(), GetVisibilityStop());
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void EditBox::Create(Window* parent, const basic::Vector2i& position, int32 width,
        uint32 style)
    {
        Window::Create(
            parent,
            position,
            basic::Vector2i(width, GetEditBoxSize()),
            WINDOW_STYLE_Focusable);

        SetExtendedStyle(style);
    }

    //--------------------------------------------------------------------------------------------//

    void EditBox::Update()
    {
        if (HasFocus() && !IsReadOnly())
        {
            _CursorTime += input::Module::Get().GetTimeStep();
            _ItHasToRenderCursor = (((int) _CursorTime.GetMilliSecondCount()) % 800) > 400;
        }

        if (IsEnabled() && HasFocus())
            _UpdateVisibility();

        Window::Update();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(EditBox, Widget)
        COFFEE_RegisterEventHandler(input::EVENT_KeyPressed, input::Handler, OnKeyPressed)
        COFFEE_RegisterEventHandler(input::EVENT_CharacterKeyPressed, input::Handler, OnCharacterKeyPressed)
        COFFEE_RegisterEventHandler(input::EVENT_MouseMove, input::Handler, OnMouseMove)
        COFFEE_RegisterEventHandler(input::EVENT_MouseLeftButtonPressed, input::Handler, OnMouseLeftButtonPressed)
        COFFEE_RegisterEventHandler(input::EVENT_MouseLeftButtonReleased, input::Handler, OnMouseLeftButtonReleased)
        COFFEE_RegisterEventHandler(input::EVENT_MouseDoubleClick, input::Handler, OnMouseDoubleClick)
        COFFEE_RegisterEventHandler(input::EVENT_Command, input::Handler, OnCommand)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool EditBox::OnKeyPressed(shell::Event& event)
    {
        input::EventKey* parameter = (input::EventKey*)
            event.GetParameters().GetCustomParameter();
        if (HasFocus() && !IsReadOnly())
        {
            _UpdateVisibility();

            int32 cursor_start = Minimum(_CursorPosition, _CursorPosition + _CursorSize);
            int32 cursor_stop = Maximum(_CursorPosition, _CursorPosition + _CursorSize);

            switch (parameter->Key)
            {
                case input::KEY_Left:
                {
                    if (input::Keyboard::Get().IsButtonPressed(input::KEY_Shift))
                    {
                        if (_CursorPosition + _CursorSize > 0)
                            --_CursorSize;

                        if (input::Keyboard::Get().IsButtonPressed(input::KEY_Control))
                        {
                            while (_CursorPosition+_CursorSize>0 && GetText()[_CursorPosition+_CursorSize-1]!=' ')
                                --_CursorSize;
                        }
                        return true;
                    }
                    else if (_CursorPosition > 0)
                    {
                        if (_CursorSize == 0)
                        {
                            --_CursorPosition;

                            if (input::Keyboard::Get().IsButtonPressed(input::KEY_Control))
                            {
                                while (_CursorPosition>0 && GetText()[_CursorPosition-1]!=' ')
                                    --_CursorPosition;
                            }
                        }
                        else
                        {
                            _CursorPosition = cursor_start;
                            _CursorSize = 0;
                        }
                        return true;
                    }
                } break;

                case input::KEY_Right:
                {
                    if (input::Keyboard::Get().IsButtonPressed(input::KEY_Shift))
                    {
                        if (_CursorPosition+_CursorSize<(int32) _Text.GetLength())
                            ++_CursorSize;

                        if (input::Keyboard::Get().IsButtonPressed(input::KEY_Control))
                        {
                            while (_CursorPosition+_CursorSize<(int32)_Text.GetLength()
                                && GetText()[_CursorPosition+_CursorSize]!=' ')
                            {
                                ++_CursorSize;
                            }
                        }
                        return true;
                    }
                    else if (_CursorPosition < (int32) _Text.GetLength())
                    {
                        if (_CursorSize == 0)
                        {
                            ++_CursorPosition;

                            if (input::Keyboard::Get().IsButtonPressed(input::KEY_Control))
                            {
                                while (_CursorPosition<(int32)_Text.GetLength() && GetText()[_CursorPosition ]!=' ')
                                    ++_CursorPosition;
                            }
                        }
                        else
                        {
                            _CursorPosition = cursor_stop;
                            _CursorSize = 0;
                        }
                        return true;
                    }
                } break;

                case input::KEY_Back:
                {
                    if (_CursorPosition > 0 || _CursorSize != 0)
                    {
                        int32 char_index;
                        basic::String new_text;

                        if (_CursorSize == 0 && cursor_start > 0)
                            --cursor_start;

                        for (char_index = 0 ; char_index < cursor_start ; char_index ++)
                            new_text += _Text[ char_index ];

                        for (char_index = cursor_stop ; char_index < (int32) _Text.GetLength() ; char_index ++)
                            new_text += _Text[ char_index ];

                        _UpdateText(new_text);
                        _CursorPosition = cursor_start;
                        _CursorSize = 0;
                        return true;
                    }
                } break;
            }
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool EditBox::OnCharacterKeyPressed(shell::Event& event)
    {
        if (HasFocus() && !IsReadOnly())
        {
            int32 cursor_start = Minimum(_CursorPosition, _CursorPosition + _CursorSize);
            int32 cursor_stop = Maximum(_CursorPosition, _CursorPosition + _CursorSize);
            int32 char_index;
            basic::String new_text;
            int32 stop(cursor_stop);

            for(char_index = 0 ; char_index < cursor_start ; char_index ++)
                new_text += _Text[ char_index ];

            char chara;
            ulong_ptr ptr = (ulong_ptr)event.GetParameters().GetCustomParameter();
            memcpy(&chara, &ptr, 1);
            new_text += chara;

            if(_CursorSize == 0 && input::Keyboard::Get().IsReplacing())
                ++ stop;

            for(char_index = stop ; char_index < (int32) _Text.GetLength() ; char_index ++)
                new_text += _Text[ char_index ];

            _UpdateText(new_text);
            _CursorPosition = cursor_start + 1;
            _CursorSize = 0;

            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool EditBox::OnMouseMove(shell::Event& event)
    {
        input::EventMouse* parameter = (input::EventMouse*)
            event.GetParameters().GetCustomParameter();

        if (_ItIsSelecting && IsEnabled())
        {
            int32 size(2);
            int32 mouse_pos_x;
            int32 cursor_position;
            WindowContext context;

            context.Create(this);
            mouse_pos_x = parameter->Position.X - context.GetDesktopWindowRect().GetMinimum().X - 2;
            cursor_position = _VisibilityStart;

            while(size < mouse_pos_x && cursor_position < (int32) GetText().GetLength())
            {
                size += GetSkinWidget().GetCharacterSize(GetText()[cursor_position]).X;
                ++cursor_position;
            }

            _CursorSize = cursor_position - _CursorPosition;
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool EditBox::OnMouseLeftButtonPressed(shell::Event& event)
    {
        input::EventMouse* parameter = (input::EventMouse*)
            event.GetParameters().GetCustomParameter();

        if (IsEnabled())
        {
            int32 size(2);
            int32 mouse_pos_x;
            WindowContext context;

            context.Create(this);
            mouse_pos_x = parameter->Position.X - context.GetDesktopWindowRect().GetMinimum().X - 2;
            _CursorPosition = _VisibilityStart;

            while(size<mouse_pos_x && _CursorPosition<(int32)GetText().GetLength())
            {
                size += GetSkinWidget().GetCharacterSize(GetText()[_CursorPosition]).X;
                ++_CursorPosition;
            }

            _CursorSize = 0;
            _ItIsSelecting = true;

            if(_CursorPosition > (int32)_Text.GetLength())
                _CursorPosition = (int32)_Text.GetLength();

            _UpdateVisibility();
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool EditBox::OnMouseLeftButtonReleased(shell::Event& event)
    {
        if (IsEnabled())
        {
            _ItIsSelecting = false;
            SendEvent(EVENT_Select);
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool EditBox::OnMouseDoubleClick(shell::Event& event)
    {
        if (IsEnabled())
            SendEvent(EVENT_Activate);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool EditBox::OnCommand(shell::Event& event)
    {
        if (HasExtendedStyle(EDIT_BOX_STYLE_NoClipBoard))
            return false;

        input::Command* command = (input::Command*)event.GetParameters().GetCustomParameter();
        if (command==edition::SelectionManager::CopyCommand)
        {
            if(HasFocus())
            {
                int32 cursor_start = Minimum(_CursorPosition, _CursorPosition + _CursorSize);
                int32 cursor_stop = Maximum(_CursorPosition, _CursorPosition + _CursorSize);

                //if(!HasExtendedStyle(EDIT_BOX_STYLE_NoClipBoard))
                {
                    basic::Text text;
                    text.AddLine(_Text.GetCenter(cursor_start, cursor_stop - 1));
                    WindowManager::Get().GetClipBoard().CopyText(text);
                    return true;
                }
            }
        }
        else if (command==edition::SelectionManager::CutCommand)
        {
            if(HasFocus() && !IsReadOnly())
            {
                int32 cursor_start = Minimum(_CursorPosition, _CursorPosition + _CursorSize);
                int32 cursor_stop = Maximum(_CursorPosition, _CursorPosition + _CursorSize);

                //if(!HasExtendedStyle(EDIT_BOX_STYLE_NoClipBoard))
                {
                    basic::Text text;
                    basic::String new_string;
                    text.AddLine(_Text.GetCenter(cursor_start, cursor_stop - 1));
                    WindowManager::Get().GetClipBoard().CopyText(text);
                    new_string = _Text.GetLeft(cursor_start)
                        + _Text.GetRight(_Text.GetLength() - cursor_stop);
                    _UpdateText(new_string);
                    _CursorPosition = cursor_start;
                    _CursorSize = 0;
                    return true;
                }
            }
        }
        else if (command==edition::SelectionManager::PasteCommand)
        {
            if (HasFocus() && !IsReadOnly())
            {
                _UpdateVisibility();

                int32 cursor_start = Minimum(_CursorPosition, _CursorPosition + _CursorSize);
                int32 cursor_stop = Maximum(_CursorPosition, _CursorPosition + _CursorSize);

                if (!HasExtendedStyle(EDIT_BOX_STYLE_NoClipBoard))
                {
                    int32 char_index;
                    basic::String new_text;
                    const basic::Text& text = WindowManager::Get().GetClipBoard().PasteText();

                    for(char_index=0 ; char_index<cursor_start ; ++char_index)
                        new_text += _Text[char_index];

                    if(text.GetLineCount()>0)
                        new_text += text.GetLine(0);

                    for(char_index=cursor_stop ; char_index<(int32)_Text.GetLength() ; ++char_index)
                        new_text += _Text[char_index];

                    _UpdateText(new_text);

                    if (text.GetLineCount()>0)
                    {
                        _CursorPosition = cursor_start + text.GetLine(0).GetLength();
                    }
                    else
                    {
                        _CursorPosition = cursor_start;
                    }

                    _CursorSize = 0;
                    return true;
                }
            }
        }
        else if (command==edition::SelectionManager::DeleteCommand)
        {
            if (HasFocus() && !IsReadOnly())
            {
                if (_CursorPosition<(int32)_Text.GetLength() || _CursorSize!=0)
                {
                     _UpdateVisibility();

                    int32 cursor_start = Minimum(_CursorPosition, _CursorPosition + _CursorSize);
                    int32 cursor_stop = Maximum(_CursorPosition, _CursorPosition + _CursorSize);

                    int32 char_index;
                    basic::String new_text;

                    if (_CursorSize==0)
                        ++cursor_stop;

                    for (char_index=0 ; char_index<cursor_start ; ++char_index)
                        new_text += _Text[char_index];

                    for (char_index=cursor_stop ; char_index<(int32)_Text.GetLength() ; ++char_index)
                        new_text += _Text[char_index];

                    _UpdateText(new_text);
                    _CursorPosition = cursor_start;
                    _CursorSize = 0;
                    return true;
                }
            }
        }
        return HasFocus() && !IsReadOnly();
    }

    //-OPERATIONS-----------------------------------------------------------------------------//

    void EditBox::_UpdateClientArea()
    {
        Window::_UpdateClientArea();

        if (_ItHasToFit && HasExtendedStyle((uint32) EDIT_BOX_STYLE_FitToContent)
            && GetSkinWidget().GetFont().IsAvailable())
        {
            uint32 horizontal_size(0);
            basic::Vector2i window_size;

            window_size = GetSize();
            horizontal_size = GetSkinWidget().GetTextWidth(_Text);
            horizontal_size += GetBorders().X + 5;
            horizontal_size = Maximum(horizontal_size, (uint32)10);
            window_size.X = horizontal_size;
            SetSize(window_size);
            _ItHasToFit = false;
        }
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void EditBox::_UpdateVisibility()
    {
        int32 cursor_position;
        int32 char_index;
        int32 size;

        _VisibilityStop = GetText().GetLength();

        cursor_position = _CursorPosition + _CursorSize;

        if(_VisibilityStart > cursor_position - 1)
        {
            _VisibilityStart = Maximum(0, cursor_position - 1);
        }
        else
        {
            size = 2;

            for(char_index=_VisibilityStart ; char_index<cursor_position ; ++char_index)
            {
                size += GetSkinWidget().GetCharacterSize(GetText()[char_index]).X;
            }

            if(size>GetClientRect().Size.X)
            {
                _VisibilityStart = cursor_position;
                size = 2;

                while(size<GetClientRect().Size.X && _VisibilityStart>0)
                {
                    --_VisibilityStart;
                    size += GetSkinWidget().GetCharacterSize(GetText()[_VisibilityStart]).X;
                }

                ++_VisibilityStart;
            }
        }

        if(_VisibilityStart!=_OldVisibility)
        {
            SendEvent(EVENT_Scroll);
            _OldVisibility = _VisibilityStart;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void EditBox::_UpdateText(const basic::String& text)
    {
        _Text = text;
        SendEvent(EVENT_Changed);
        _FitToContent();
    }

    //--------------------------------------------------------------------------------------------//

    void EditBox::_FitToContent()
    {
        _ItHasToFit = true;
    }

}
}
}
