#ifndef _COFFEE_UI_SKIN_WIDGET_H_
#define _COFFEE_UI_SKIN_WIDGET_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/widget/widgets.h"
#include "wide/ui/skin/ui_skin_context.h"
#include "wide/ui/window/ui_window.h"
#include "wide/ui/skin/ui_skin_widget_state.h"
#include "wide/ui/skin/ui_skin_theme.h"
#include "system/graphics/font/graphics_font.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Skin widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API SkinWidget : public meta::Object
    {
        COFFEE_Type(SkinWidget);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SkinWidget();
        SkinWidget(basic::String name, meta::Class& widget_type);
        virtual ~SkinWidget();

        //-ACCESSORS------------------------------------------------------------------------------//

        const basic::String& GetName() const;
        const meta::Class& GetWidgetType() const;
        void SetBorderSize(const basic::Vector2i& border_size);
        const basic::Vector2i& GetBorderSize() const;
        void SetFont(graphics::Font& font);
        const graphics::Font& GetFont() const;
        graphics::Font& GetFont();
        void SetShadowsColor(const basic::Color& color);
        void EnableShadows(bool it_has_to_enable_shadows);
        bool HasShadowsEnabled() const;
        const basic::Color& GetShadowsColor() const;
        void SetBumpColor(const basic::Color& color);
        void EnableBump(bool it_has_to_enable_bump);
        bool HasBumpEnabled() const;
        const basic::Color& GetBumpColor() const;

        //-QUERIES--------------------------------------------------------------------------------//

        basic::Vector2i GetCharacterSize(char character) const;
        uint32 GetTextWidth(const basic::String& text) const;
        uint32 GetFontHeight() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void ApplyTheme(SkinTheme& theme);
        virtual void Render(Window& window, const SkinContext& paint_context);

    protected:

        //-ACCESSORS------------------------------------------------------------------------------//

        void _SetState(SkinWidgetState& state);
        const SkinWidgetState& _GetState() const;

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::String _Name;
        meta::Class* _WidgetType;
        basic::Vector2i _BorderSize;
        graphics::Font _Font;
        SkinWidgetState* _State;
        bool _ItHasShadowsEnabled;
        basic::Color _ShadowsColor;
        bool _ItHasBumpEnabled;
        basic::Color _BumpColor;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, SkinWidget);
}
}
#endif
