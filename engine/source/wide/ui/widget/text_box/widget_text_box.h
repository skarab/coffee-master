#ifndef _COFFEE_UI_WIDGET_TEXT_BOX_H_
#define _COFFEE_UI_WIDGET_TEXT_BOX_H_

#include "coffee_includes.h"
#include "wide/ui/widget/widget.h"
#include "wide/ui/widget/edit_box/widget_edit_box.h"
#include "wide/ui/widget/scroll_bar/widget_scroll_bar.h"
#include "wide/ui/widget/text_box/widget_text_box_style.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// TextBox widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API TextBox : public Widget
    {
        COFFEE_Type(TextBox);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        TextBox();
        ~TextBox();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetText(const basic::Text& text);
        const basic::Text& GetText() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(Window* parent, const basic::Vector2i& position,
            const basic::Vector2i& size, uint32 style=TEXT_BOX_STYLE_Default);

        void ForceUpdate();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(TextBox);
        COFFEE_Event bool OnHorizontalScroll(shell::Event& event);
        COFFEE_Event bool OnVerticalScroll(shell::Event& event);
        COFFEE_Event bool OnTextChanged(shell::Event& event);
        COFFEE_Event bool OnSetFocus(shell::Event& event);
        COFFEE_Event bool OnTextScroll(shell::Event& event);
        COFFEE_Event bool OnKeyPressed(shell::Event& event);
        COFFEE_Event bool OnCommand(shell::Event& event);

    private:

        //-ACCESSORS------------------------------------------------------------------------------//

        EditBox& _GetEditBox(uint32 index);
        uint32 _GetCursorLineIndex();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _UpdateClientArea();
        void _UpdateClient(bool it_has_to_force=false);
        void _UpdateContent();
        void _ClearContent();
        void _UpdateScrollBars();
        void _PushIndex();
        void _PopIndex();
        void _ComputeWidth();
        void _Modify();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Window* _ClientWindow;
        ScrollBar* _HorizontalScrollBar;
        ScrollBar* _VerticalScrollBar;
        uint32 _ScrollBarSize;
        basic::Text _Text;
        uint32 _VisibilityStart;
        uint32 _ColumnIndex;
        uint32 _SavedLineIndex;
        uint32 _SavedColumnIndex;
        uint32 _Width;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, TextBox);
}
}
}
#endif
