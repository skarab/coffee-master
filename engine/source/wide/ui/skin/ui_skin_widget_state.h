#ifndef _COFFEE_UI_SKIN_DEFAULT_WIDGET_STATE_H_
#define _COFFEE_UI_SKIN_DEFAULT_WIDGET_STATE_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Default skin widget state
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API SkinWidgetState : public meta::Object
    {
        COFFEE_Type(SkinWidgetState);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SkinWidgetState();
        virtual ~SkinWidgetState();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetFontColor(const basic::Color& font_color);
        const basic::Color& GetFontColor() const;
        void SetColor(const basic::Color& color);
        const basic::Color& GetColor() const;
        basic::Color& GetColor();
        void SetHighlightColor(const basic::Color& highlight_color);
        const basic::Color& GetHighlightColor() const;
        basic::Color& GetHighlightColor();
        void SetShadowColor(const basic::Color& shadow_color);
        const basic::Color& GetShadowColor() const;
        basic::Color& GetShadowColor();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Color _FontColor;
        basic::Color _Color;
        basic::Color _HighlightColor;
        basic::Color _ShadowColor;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, SkinWidgetState);
}
}
#endif
