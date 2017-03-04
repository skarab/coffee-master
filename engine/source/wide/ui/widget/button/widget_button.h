#ifndef _COFFEE_UI_WIDGET_BUTTON_H_
#define _COFFEE_UI_WIDGET_BUTTON_H_

#include "coffee_includes.h"
#include "wide/ui/widget/widget.h"
#include "wide/ui/widget/button/widget_button_style.h"
#include "wide/ui/widget/button/widget_button_state.h"
#include "wide/ui/widget/image/widget_image.h"
#include "wide/ui/skin/ui_skin_icon.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Button widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Button : public Widget
    {
        COFFEE_Type(Button);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Button();
        virtual ~Button();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetState(const BUTTON_STATE& state);
        const BUTTON_STATE& GetState();
        void SetText(const basic::String& text);
        const basic::String& GetText() const;
        void SetColor(const basic::Color& color);
        const basic::Color& GetColor() const;
        bool HasToOverwriteColor() const;
        void SetImage(graphics::Texture texture_instance);
        void SetImage(storage::Path texture_path);
        void SetImage(const SKIN_ICON& icon);
        void SetNoImage();
        void SetHelpText(const basic::String& help_text);

        //-QUERIES--------------------------------------------------------------------------------//

        bool HasImage() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void Create(Window* parent, const basic::Vector2i& position,
            const basic::Vector2i& size, uint32 style=BUTTON_STYLE_Default);
        
        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(Button);
        COFFEE_Event bool OnBeginCursorOver(shell::Event& event);
        COFFEE_Event bool OnEndCursorOver(shell::Event& event);
        COFFEE_Event bool OnMouseLeftButtonPressed(shell::Event& event);
        COFFEE_Event bool OnMouseLeftButtonReleased(shell::Event& event);
        COFFEE_Event bool OnMouseRightButtonReleased(shell::Event& event);
        COFFEE_Event bool OnMouseDoubleClick(shell::Event& event);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _DestroyImage();
        virtual void _UpdateClientArea();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        BUTTON_STATE _State;
        basic::String _Text;
        basic::Color _Color;
        bool _ItHasToOverwriteColor;
        Image* _Image;
        basic::String _HelpText;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Button);
}
}
}
#endif
