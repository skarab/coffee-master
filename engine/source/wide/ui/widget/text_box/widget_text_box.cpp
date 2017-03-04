#include "wide/ui/widget/text_box/widget_text_box.h"
#include "wide/ui/widget/edit_box/widget_edit_box.h"
#include "wide/ui/window/ui_window_manager.h"
#include "wide/edition/selection/edition_selection_manager.h"

#define COFFEE_WIDGET_TEXT_BOX_HorizontalBorder   6

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::widget::TextBox);
        COFFEE_Ancestor(ui::widget::Widget);
    COFFEE_EndType();

namespace ui
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    TextBox::TextBox() :
        _ClientWindow(NULL),
        _HorizontalScrollBar(NULL),
        _VerticalScrollBar(NULL),
        _VisibilityStart(0),
        _ColumnIndex(NONE),
        _SavedLineIndex(NONE),
        _SavedColumnIndex(NONE)
    {
        _ScrollBarSize = GetRealScrollSize() + 2;
    }

    //--------------------------------------------------------------------------------------------//

    TextBox::~TextBox()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void TextBox::SetText(const basic::Text& text)
    {
        _Text = text;

        if(_Text.GetLineCount() == 0)
        {
            _VisibilityStart = 0;
        }
        else if(_VisibilityStart >= _Text.GetLineCount())
        {
            _VisibilityStart = _Text.GetLineCount() - 1;
        }

        _ColumnIndex = NONE;
        _UpdateContent();
        _GetEditBox(0).SetFocus();
        _GetEditBox(0).SetCursorPosition(0);
        _ComputeWidth();
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Text& TextBox::GetText() const
    {
        return _Text;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void TextBox::Create(Window* parent, const basic::Vector2i& position,
        const basic::Vector2i& size, uint32 style)
    {
        Widget::Create(parent, position, size, WINDOW_STYLE_None);
        SetExtendedStyle(style);

        GetLayout().SetStyle(
            LAYOUT_STYLE_VerticalCanvas
            | LAYOUT_STYLE_StickChildren);

        Window* frame_window = COFFEE_New(Window);
        frame_window->Create(
            this,
            basic::Vector2i(),
            basic::Vector2i(),
            WINDOW_STYLE_None);
        frame_window->GetLayout().SetStyle(
            LAYOUT_STYLE_HorizontalCanvas
            | LAYOUT_STYLE_StickChildren
            | LAYOUT_STYLE_HorizontalExpand);
        frame_window->GetLayout().SetCanvas(100, true);
        
        _ClientWindow = COFFEE_New(Window);
        _ClientWindow->Create(
            frame_window,
            basic::Vector2i(),
            basic::Vector2i(),
            WINDOW_STYLE_DrawFrame | WINDOW_STYLE_DrawClientSunken);
        _ClientWindow->GetLayout().SetStyle(
            LAYOUT_STYLE_VerticalCanvas
            | LAYOUT_STYLE_VerticalExpand);
        _ClientWindow->GetLayout().SetCanvas(100, true);
        
        _VerticalScrollBar = COFFEE_New(ScrollBar);
        _VerticalScrollBar->Create(frame_window, basic::Vector2i(), basic::Vector2i(),
            SCROLL_BAR_STYLE_Vertical);
        _VerticalScrollBar->SetControlSize(_ScrollBarSize);
        _VerticalScrollBar->GetLayout().SetCanvas((int32)_ScrollBarSize, false);
        _VerticalScrollBar->GetLayout().SetStyle(LAYOUT_STYLE_VerticalExpand);
        _VerticalScrollBar->SetScrollPosition(0);

        frame_window = COFFEE_New(Window);
        frame_window->Create(
            this,
            basic::Vector2i(),
            basic::Vector2i(),
            WINDOW_STYLE_None);
        frame_window->GetLayout().SetStyle(
            LAYOUT_STYLE_HorizontalCanvas
            | LAYOUT_STYLE_StickChildren
            | LAYOUT_STYLE_HorizontalExpand);
        frame_window->GetLayout().SetCanvas((int32)_ScrollBarSize, false);
        
        _HorizontalScrollBar = COFFEE_New(ScrollBar);
        _HorizontalScrollBar->Create(frame_window, basic::Vector2i(), basic::Vector2i(),
            SCROLL_BAR_STYLE_Horizontal);
        _HorizontalScrollBar->SetControlSize(_ScrollBarSize);
        _HorizontalScrollBar->GetLayout().SetCanvas(100, true);
        _HorizontalScrollBar->GetLayout().SetStyle(LAYOUT_STYLE_VerticalExpand);
        _HorizontalScrollBar->SetScrollPosition(0);

        Window* square_window = COFFEE_New(Window);
        square_window->Create(
            frame_window,
            basic::Vector2i(),
            basic::Vector2i(),
            WINDOW_STYLE_None);
        square_window->GetLayout().SetCanvas((int32)_ScrollBarSize, false);
        
        _UpdateClient();
    }

    //--------------------------------------------------------------------------------------------//

    void TextBox::ForceUpdate()
    {
        _UpdateClient(true);
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(TextBox, Widget)
        COFFEE_RegisterTargetEventHandler(EVENT_Scroll, Widget, _HorizontalScrollBar, OnHorizontalScroll)
        COFFEE_RegisterTargetEventHandler(EVENT_Scroll, Widget, _VerticalScrollBar, OnVerticalScroll)
        COFFEE_RegisterEventHandler(EVENT_Changed, Widget, OnTextChanged)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_SetFocus, Window, OnSetFocus)
        COFFEE_RegisterEventHandler(EVENT_Scroll, Widget, OnTextScroll)
        COFFEE_RegisterEventHandler(input::EVENT_KeyPressed, input::Handler, OnKeyPressed)
        COFFEE_RegisterEventHandler(input::EVENT_Command, input::Handler, OnCommand)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool TextBox::OnHorizontalScroll(shell::Event& event)
    {
        uint32 edit_box_index;
        uint32 edit_box_count(_ClientWindow->GetChildCount());

        for(edit_box_index = 0 ; edit_box_index < edit_box_count ; ++ edit_box_index)
            _GetEditBox(edit_box_index).SetVisibilityStart(_HorizontalScrollBar->GetScrollPosition());

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool TextBox::OnVerticalScroll(shell::Event& event)
    {
        uint32 visibility_start = _GetEditBox(0).GetVisibilityStart();

        _VisibilityStart = _VerticalScrollBar->GetScrollPosition();
        _UpdateContent();

        uint32 edit_box_index;
        uint32 edit_box_count(_ClientWindow->GetChildCount());

        for(edit_box_index = 0 ; edit_box_index < edit_box_count ; ++ edit_box_index)
            _GetEditBox(edit_box_index).SetVisibilityStart(visibility_start);

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool TextBox::OnTextChanged(shell::Event& event)
    {
        uint32 line_index;
        uint32 line_count;

        if(event.GetTarget() == this)
            return false;

        _ColumnIndex = NONE;
        line_count = _ClientWindow->GetChildCount();
        COFFEE_Assert(_VisibilityStart <= _Text.GetLineCount(),
            core::ERROR_CODE_Unexpected, "Unexpected error");
        line_count = Minimum(_Text.GetLineCount() - _VisibilityStart, line_count);

        if(line_count == 0)
        {
            line_count = 1;
            _Text.AddLine(basic::String());
        }

        for(line_index = 0 ; line_index < line_count ; ++ line_index)
        {
            EditBox* edit_box;

            if(HasExtendedStyle(TEXT_BOX_STYLE_DrawNumbers))
            {
                edit_box = (EditBox*) &_ClientWindow->GetChild(line_index).GetChild(1);
            }
            else
            {
                edit_box = (EditBox*) &_ClientWindow->GetChild(line_index);
            }

            if(edit_box==event.GetTarget())
                _Text[ line_index + _VisibilityStart ] = edit_box->GetText();
        }

        _Modify();

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool TextBox::OnSetFocus(shell::Event& event)
    {
        uint32 line_index;
        EditBox* edit_box;

        _ColumnIndex = NONE;
        line_index = _GetCursorLineIndex();

        if(line_index != NONE && line_index >= _Text.GetLineCount() - _VisibilityStart)
        {
            if(_Text.GetLineCount() < _VisibilityStart + 1)
            {
                line_index = 0;
            }
            else
            {
                line_index = _Text.GetLineCount() - _VisibilityStart - 1;
            }

            edit_box = &_GetEditBox(line_index);

            if(!edit_box->HasFocus())
            {
                edit_box->SetFocus();
                edit_box->SetCursorPosition(edit_box->GetText().GetLength());
            }
        }

        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool TextBox::OnTextScroll(shell::Event& event)
    {
        EditBox* edit_box = (EditBox*) event.GetTarget();
        uint32 edit_box_index;
        uint32 edit_box_count(_ClientWindow->GetChildCount());

        for(edit_box_index = 0 ; edit_box_index < edit_box_count ; ++ edit_box_index)
            _GetEditBox(edit_box_index).SetVisibilityStart(edit_box->GetVisibilityStart());

        _UpdateScrollBars();

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool TextBox::OnKeyPressed(shell::Event& event)
    {
        input::EventKey* parameter = (input::EventKey*)
            event.GetParameters().GetCustomParameter();
        uint32 line_index = _GetCursorLineIndex();

        if (line_index != NONE)
        {
            switch (parameter->Key)
            {
                case input::KEY_Return:
                case input::KEY_Accept:
                {
                    EditBox* edit_box = &_GetEditBox(line_index);
                    basic::String left_string, right_string;
                    int32 cursor_start(edit_box->GetCursorPosition());
                    int32 cursor_end(edit_box->GetCursorSize());

                    if(_Text.GetLineCount() == 0)
                        _Text.AddLine(basic::String());

                    if(cursor_end < 0)
                    {
                        cursor_start += cursor_end;
                        cursor_end = edit_box->GetCursorPosition();
                    }
                    else
                    {
                        cursor_end += edit_box->GetCursorPosition();
                    }

                    left_string = _Text[ line_index + _VisibilityStart ].GetLeft((uint32) cursor_start);

                    right_string = _Text[ line_index + _VisibilityStart ].GetRight(
                        _Text[ line_index + _VisibilityStart ].GetLength() - (uint32) cursor_end);

                    _Text[ line_index + _VisibilityStart ] = left_string;
                    _Text.AddLine(right_string, line_index + _VisibilityStart + 1);

                    if (line_index + 1 >= _ClientWindow->GetChildCount())
                    {
                        ++ _VisibilityStart;
                        -- line_index;
                    }

                    _UpdateContent();

                    _ColumnIndex = NONE;
                    edit_box = &_GetEditBox(line_index + 1);
                    edit_box->SetFocus();
                    edit_box->SetCursorSize(0);
                    edit_box->SetCursorPosition(0);

                    _Modify();
                    return true;
                } break;

                case input::KEY_Back:
                {
                    EditBox* edit_box = &_GetEditBox(line_index);

                    if((line_index > 0 || _VisibilityStart > 0) && edit_box->GetCursorPosition() == 0)
                    {
                        basic::String line(_Text[ line_index + _VisibilityStart ]);

                        _Text[ line_index + _VisibilityStart - 1 ] += line;
                        _Text.RemoveLine(line_index + _VisibilityStart);

                        if(line_index == 0)
                        {
                            -- _VisibilityStart;
                            ++ line_index;
                        }

                        _UpdateContent();
                        _ColumnIndex = NONE;

                        edit_box = &_GetEditBox(line_index - 1);
                        edit_box->SetFocus();
                        edit_box->SetCursorSize(0);
                        edit_box->SetCursorPosition(edit_box->GetText().GetLength() - line.GetLength());

                        _Modify();
                        return true;
                    }
                } break;

                case input::KEY_Up:
                {
                    if(line_index + _VisibilityStart > 0)
                    {
                        uint32 column_index;

                        if(_ColumnIndex == NONE)
                            _ColumnIndex = _GetEditBox(line_index).GetCursorPosition();

                        column_index = _ColumnIndex;

                        if(line_index + _VisibilityStart - 1 < _VisibilityStart)
                        {
                            -- _VisibilityStart;
                            ++ line_index;
                            _UpdateContent();
                        }

                        EditBox* edit_box = &_GetEditBox(line_index - 1);

                        edit_box->SetFocus();
                        edit_box->SetCursorPosition(column_index);
                        _ColumnIndex = column_index;
                        return true;
                    }
                } break;

                case input::KEY_Down:
                {
                    if(line_index + _VisibilityStart < _Text.GetLineCount() - 1)
                    {
                        uint32 column_index;

                        if(_ColumnIndex == NONE)
                            _ColumnIndex = _GetEditBox(line_index).GetCursorPosition();

                        column_index = _ColumnIndex;

                        if(line_index + 1 >= _ClientWindow->GetChildCount())
                        {
                            ++ _VisibilityStart;
                            -- line_index;
                            _UpdateContent();
                        }

                        EditBox* edit_box = &_GetEditBox(line_index + 1);

                        edit_box->SetFocus();
                        edit_box->SetCursorPosition(column_index);
                        _ColumnIndex = column_index;
                        return true;
                    }
                } break;

                case input::KEY_Left:
                {
                    uint32 column_index = _GetEditBox(line_index).GetCursorPosition();

                    if(column_index == 0 && line_index + _VisibilityStart > 0)
                    {
                        if(line_index + _VisibilityStart - 1 < _VisibilityStart)
                        {
                            -- _VisibilityStart;
                            ++ line_index;
                            _UpdateContent();
                        }

                        EditBox* edit_box = &_GetEditBox(line_index - 1);

                        edit_box->SetFocus();
                        edit_box->SetCursorPosition(edit_box->GetText().GetLength());
                        return true;
                    }
                } break;

                case input::KEY_Right:
                {
                    uint32 column_index = _GetEditBox(line_index).GetCursorPosition();

                    if(column_index == _GetEditBox(line_index).GetText().GetLength()
                        && line_index + _VisibilityStart < _Text.GetLineCount() - 1)
                    {
                        if(line_index + 1 >= _ClientWindow->GetChildCount())
                        {
                            ++ _VisibilityStart;
                            -- line_index;
                            _UpdateContent();
                        }

                        EditBox* edit_box = &_GetEditBox(line_index + 1);

                        edit_box->SetFocus();
                        edit_box->SetCursorPosition(0);
                        return true;
                    }
                } break;
            }
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool TextBox::OnCommand(shell::Event& event)
    {
        input::Command* command = (input::Command*)event.GetParameters().GetCustomParameter();
        if (command==edition::SelectionManager::CopyCommand)
        {
            uint32 line_index = _GetCursorLineIndex();

            if (line_index != NONE)
            {
                // .ToDo.

                return true;
            }
        }
        else if (command==edition::SelectionManager::CutCommand)
        {
            uint32 line_index = _GetCursorLineIndex();

            if (line_index != NONE)
            {
                // .ToDo.

                return true;
            }
        }
        else if (command==edition::SelectionManager::PasteCommand)
        {
            uint32 line_index = _GetCursorLineIndex();

            if (line_index != NONE)
            {
                const basic::Text& text = WindowManager::Get().GetClipBoard().PasteText();
                EditBox* edit_box = &_GetEditBox(line_index);
                int32 cursor_start;
                int32 cursor_stop;
                int32 char_index;
                basic::String new_text;
                basic::String end_string;

                if(_Text.GetLineCount() == 0)
                    _Text.AddLine(basic::String());

                cursor_start = Minimum(
                    edit_box->GetCursorPosition(), edit_box->GetCursorPosition() + edit_box->GetCursorSize());

                cursor_stop = Maximum(
                    edit_box->GetCursorPosition(), edit_box->GetCursorPosition() + edit_box->GetCursorSize());

                for(char_index = 0 ; char_index < cursor_start ; ++ char_index)
                    new_text += edit_box->GetText()[ char_index ];

                if(text.GetLineCount() > 0)
                    new_text += text.GetLine(0);

                for(char_index = cursor_stop ; char_index < (int32) edit_box->GetText().GetLength() ; char_index ++)
                    end_string += edit_box->GetText()[ char_index ];

                if(text.GetLineCount() < 2)
                {
                    new_text += end_string;
                    _Text[ line_index + _VisibilityStart ] = new_text;
                    edit_box->SetText(new_text);

                    if(text.GetLineCount() == 0)
                    {
                        edit_box->SetCursorPosition(cursor_start);
                    }
                    else
                    {
                        edit_box->SetCursorPosition(cursor_start + text.GetLine(0).GetLength());
                    }

                    edit_box->SetCursorSize(0);
                }
                else
                {
                    uint32 paste_index;

                    _Text[ line_index + _VisibilityStart ] = new_text;

                    for(paste_index = 1 ; paste_index < text.GetLineCount() ; ++ paste_index)
                        _Text.AddLine(text[ paste_index ], line_index + paste_index + _VisibilityStart);

                    if(end_string.GetLength() > 0)
                        _Text.AddLine(end_string, line_index + paste_index + _VisibilityStart);

                    edit_box->SetCursorSize(0);
                    _UpdateContent();
                }

                _Modify();

                return true;
            }
        }
        else if (command==edition::SelectionManager::DeleteCommand)
        {
            uint32 line_index = _GetCursorLineIndex();
            EditBox* edit_box = &_GetEditBox(line_index);
            if (line_index + _VisibilityStart < _Text.GetLineCount() - 1
                && edit_box->GetCursorPosition() == edit_box->GetText().GetLength())
            {
                uint32 cursor_position = edit_box->GetText().GetLength();
                _Text[ line_index + _VisibilityStart ] += _Text[ line_index + _VisibilityStart + 1 ];
                _Text.RemoveLine(line_index + _VisibilityStart + 1);
                _UpdateContent();
                _ColumnIndex = NONE;
                edit_box->SetFocus();
                edit_box->SetCursorSize(0);
                edit_box->SetCursorPosition(cursor_position);
                _Modify();
                return true;
            }
        }
        return true;
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    EditBox& TextBox::_GetEditBox(uint32 index)
    {
        if(HasExtendedStyle(TEXT_BOX_STYLE_DrawNumbers))
        {
            shell::EventHandler* handler =
                (shell::EventHandler *) &_ClientWindow->GetChild(index);

            if(handler->GetChildCount() == 0)
                return *((EditBox*) handler);

            return *((EditBox*) &handler->GetChild(1));
        }

        return *((EditBox*) &_ClientWindow->GetChild(index));
    }

    //--------------------------------------------------------------------------------------------//

    uint32 TextBox::_GetCursorLineIndex()
    {
        uint32 line_index;
        uint32 line_count;

        line_count = _ClientWindow->GetChildCount();

        for(line_index=0 ; line_index<line_count ; ++line_index)
        {
            EditBox* edit_box = &_GetEditBox(line_index);
            if(edit_box->HasFocus())
                return line_index;
        }

        return NONE;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void TextBox::_UpdateClientArea()
    {
        Window::_UpdateClientArea();

        if (_ClientWindow!=NULL)
            _UpdateClient();
    }

    //--------------------------------------------------------------------------------------------//

    void TextBox::_UpdateClient(bool it_has_to_force)
    {
        static bool it_is_updating(false);
        uint32 edit_box_count;
        uint32 edit_box_index;
        uint32 line_count;
        EditBox * edit_box;
        uint32 alive_count;

        edit_box_count = (uint32) _ClientWindow->GetSize().Y / (GetEditBoxSize() + 1) + 1;
        edit_box_count = Maximum(edit_box_count, (uint32)1);
        alive_count = Minimum(_Text.GetLineCount() - _VisibilityStart, edit_box_count);
        alive_count = Maximum(alive_count, (uint32)1);
        
        line_count = _ClientWindow->GetChildCount();

        if (it_is_updating || (!it_has_to_force && (edit_box_count == line_count)))
            return;

        _PushIndex();
        it_is_updating = true;
        _ClientWindow->DestroyChildren();

        for (edit_box_index=0 ; edit_box_index<edit_box_count ; ++edit_box_index)
        {
            Window* frame;

            if (HasExtendedStyle(TEXT_BOX_STYLE_DrawNumbers))
            {
                frame = COFFEE_New(Window);
                frame->Create(
                    _ClientWindow,
                    coffee::basic::Vector2i(0, edit_box_index * (GetEditBoxSize() + 1)),
                    coffee::basic::Vector2i(25, GetEditBoxSize()),
                    WINDOW_STYLE_None);
                frame->GetLayout().SetStyle(
                    LAYOUT_STYLE_HorizontalExpand
                    | LAYOUT_STYLE_HorizontalCanvas
                    | LAYOUT_STYLE_StickChildren);
                
                Label* number = COFFEE_New(Label);
                number->Create(frame, basic::Vector2i(), basic::Vector2i(10, GetEditBoxSize()));
                number->GetLayout().SetCanvas(25, false);
            }

            edit_box = COFFEE_New(EditBox);
            edit_box->Create(
                HasExtendedStyle(TEXT_BOX_STYLE_DrawNumbers) ? frame : _ClientWindow,
                coffee::basic::Vector2i(0,
                    HasExtendedStyle(TEXT_BOX_STYLE_DrawNumbers) ? 0 : (edit_box_index * (GetEditBoxSize() + 1))),
                20,
                HasExtendedStyle(TEXT_BOX_STYLE_DrawLines) ?
                    EDIT_BOX_STYLE_Default | EDIT_BOX_STYLE_NoClipBoard
                    : EDIT_BOX_STYLE_NoBorders | EDIT_BOX_STYLE_NoClipBoard
               );

            if (!IsEnabled() || edit_box_index>=alive_count)
                edit_box->Enable(false, false);

            if (HasExtendedStyle(TEXT_BOX_STYLE_DrawNumbers))
            {
                edit_box->GetLayout().SetCanvas(100, true);
            }
            else
            {
                edit_box->GetLayout().SetStyle(LAYOUT_STYLE_HorizontalExpand);
            }
        }
        _UpdateContent();
        it_is_updating = false;
    }

    //--------------------------------------------------------------------------------------------//

    void TextBox::_UpdateContent()
    {
        uint32 line_index;
        uint32 line_count;

        if (!GetSkin().IsAvailable())
            return;

        if (_Text.GetLineCount()==0)
            _Text.AddLine("");

        line_count = _ClientWindow->GetChildCount();
        _UpdateScrollBars();
        _ClearContent();
        COFFEE_Assert(_VisibilityStart <= _Text.GetLineCount(),
            core::ERROR_CODE_Unexpected, "Unexpected error");
        line_count = Minimum(_Text.GetLineCount() - _VisibilityStart, line_count);

        for(line_index = 0 ; line_index < line_count ; ++ line_index)
        {
            if(HasExtendedStyle(TEXT_BOX_STYLE_DrawNumbers))
            {
                Label* text_control;
                text_control = (Label*) &_ClientWindow->GetChild(line_index).GetChild(0);
                text_control->SetText(basic::String("%i", line_index + _VisibilityStart + 1));
            }

            _GetEditBox(line_index).SetText(_Text.GetLine(line_index + _VisibilityStart));
            _GetEditBox(line_index).Enable(true, false);
        }

        _PopIndex();
    }

    //--------------------------------------------------------------------------------------------//

    void TextBox::_ClearContent()
    {
        uint32 line_count = _ClientWindow->GetChildCount();

        for(uint32 line_index=0 ; line_index<line_count ; ++line_index)
        {
            _GetEditBox(line_index).SetText(basic::String());
            _GetEditBox(line_index).Enable(false, false);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void TextBox::_UpdateScrollBars()
    {
        uint32 line_count;

        line_count = _ClientWindow->GetChildCount();

        if(_Text.GetLineCount()>line_count && line_count>_Text.GetLineCount()-_VisibilityStart)
        {
            _VisibilityStart = _Text.GetLineCount() - line_count;
        }

        if(_VerticalScrollBar != NULL)
        {
            if(_Text.GetLineCount() <= line_count)
            {
                _VerticalScrollBar->SetScrollRange(0, 0);
            }
            else
            {
                _VerticalScrollBar->SetScrollRange(0, _Text.GetLineCount() - line_count);
            }

            _VerticalScrollBar->SetScrollPosition(_VisibilityStart);
        }

        if(_HorizontalScrollBar != NULL)
        {
            if(_GetEditBox(0).GetSkinWidget().GetCharacterSize('A').X
                * (_Width + COFFEE_WIDGET_TEXT_BOX_HorizontalBorder)
                <= (uint32) _ClientWindow->GetSize().X
               )
            {
                _HorizontalScrollBar->SetScrollRange(0, 0);
            }
            else
            {
                _HorizontalScrollBar->SetScrollRange(
                    0,
                    (_Width + COFFEE_WIDGET_TEXT_BOX_HorizontalBorder)
                    - (uint32) _ClientWindow->GetSize().X
                    / _GetEditBox(0).GetSkinWidget().GetCharacterSize('A').X
                   );
            }

            _HorizontalScrollBar->SetScrollPosition(_GetEditBox(0).GetVisibilityStart());
        }
    }

    //--------------------------------------------------------------------------------------------//

    void TextBox::_PushIndex()
    {
        EditBox * edit_box;
        uint32 line_count;
        uint32 line_index;

        if(_SavedLineIndex == NONE)
        {
            line_count = _ClientWindow->GetChildCount();

            for(line_index = 0 ; line_index < line_count ; ++ line_index)
            {
                edit_box = &_GetEditBox(line_index);

                if(edit_box->HasFocus())
                {
                    _SavedLineIndex = line_index;
                    _SavedColumnIndex = edit_box->GetCursorPosition();

                    break;
                }
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    void TextBox::_PopIndex()
    {
        EditBox * edit_box;

        if(_SavedLineIndex != NONE)
        {
            edit_box = &_GetEditBox(_SavedLineIndex);

            edit_box->SetFocus();
            edit_box->SetCursorPosition(_SavedColumnIndex);

            _SavedLineIndex = NONE;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void TextBox::_ComputeWidth()
    {
        uint32 line_index;
        uint32 width;

        _Width = 0;

        for(line_index = 0 ; line_index < _Text.GetLineCount() ; ++ line_index)
        {
            width = _Text[ line_index ].GetLength();

            if(width > _Width)
                _Width = width;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void TextBox::_Modify()
    {
        SendEvent(EVENT_Changed);
    }

}
}
}
#undef COFFEE_WIDGET_TEXT_BOX_HorizontalBorder
