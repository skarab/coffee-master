#ifndef _COFFEE_UI_WIDGET_EDIT_BOX_H_
#define _COFFEE_UI_WIDGET_EDIT_BOX_H_

#include "coffee_includes.h"
#include "wide/ui/widget/widget.h"
#include "wide/ui/widget/edit_box/widget_edit_box_style.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// EditBox widget
    ///
    /// @see coffee::ui::widget::EDIT_BOX_STYLE
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API EditBox : public Widget
    {
        COFFEE_Type(EditBox);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        EditBox();
        ~EditBox();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetText(const basic::String& text);
        void SetEditedText(const basic::String& text);
        const basic::String& GetText() const;
        void SetCursorPosition(int32 cursor_position);
        int32 GetCursorPosition() const;
        void SetCursorSize(int32 cursor_size);
        int32 GetCursorSize() const;
        void SetVisibilityStart(int32 visibility_start);
        int32 GetVisibilityStart() const;
        int32 GetVisibilityStop() const;

        //-QUERIES--------------------------------------------------------------------------------//

        bool HasToRenderCursor() const;
        bool IsReadOnly() const;
        basic::String GetVisibleText() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(Window* parent, const basic::Vector2i& position, int32 width,
            uint32 style=EDIT_BOX_STYLE_Default);
        void Update();
        
        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(EditBox);
        COFFEE_Event bool OnKeyPressed(shell::Event& event);
        COFFEE_Event bool OnCharacterKeyPressed(shell::Event& event);
        COFFEE_Event bool OnMouseMove(shell::Event& event);
        COFFEE_Event bool OnMouseLeftButtonPressed(shell::Event& event);
        COFFEE_Event bool OnMouseLeftButtonReleased(shell::Event& event);
        COFFEE_Event bool OnMouseDoubleClick(shell::Event& event);
        COFFEE_Event bool OnCommand(shell::Event& event);

    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _UpdateClientArea();

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _UpdateVisibility();
        void _UpdateText(const basic::String & text);
        void _FitToContent();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::String _Text;
        int32 _CursorPosition;
        int32 _CursorSize;
        int32 _VisibilityStart;
        int32 _VisibilityStop;
        basic::Time _CursorTime;
        bool _ItHasToRenderCursor;
        bool _ItIsSelecting;
        int32 _OldVisibility;
        bool _ItHasToFit;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, EditBox);
}
}
}
#endif
