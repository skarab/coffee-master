#ifndef _COFFEE_UI_SKIN_DEFAULT_THEME_H_
#define _COFFEE_UI_SKIN_DEFAULT_THEME_H_

#include "coffee_includes.h"
#include "system/graphics/font/graphics_font.h"
#include "system/graphics/font/graphics_font.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Skin theme
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API SkinTheme : public meta::Object
    {
        COFFEE_Type(SkinTheme);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SkinTheme();
        ~SkinTheme();

        //-ACCESSORS------------------------------------------------------------------------------//

        const graphics::Font& GetFont() const;
        graphics::Font& GetFont();
        basic::Color GetFontColor() const;
        const real GetTransparency() const;
        const real GetAlpha() const;
        const basic::Color& GetShadows() const;
        const basic::Color& GetBump() const;
        const basic::Color& GetWindow() const;
        const basic::Color& GetWindowLight() const;
        const basic::Color& GetWindowDark() const;
        const basic::Color& GetWindowRaised() const;
        const basic::Color& GetWindowSunken() const;
        const basic::Color& GetActiveItems() const;
        const basic::Color& GetDialog() const;
        const basic::Color& GetDialogActive() const;
        const graphics::Font& GetDialogFont() const;
        graphics::Font& GetDialogFont();
        basic::Color GetDialogFontColor() const;
        const basic::Color& GetEditZone() const;
        const graphics::Font& GetEditZoneFont() const;
        graphics::Font& GetEditZoneFont();
        basic::Color GetEditZoneFontColor() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void SetDefaults();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        graphics::Font _Font;
        real _Transparency;
        basic::Color _Shadows;
        basic::Color _Bump;
        basic::Color _Window;
        basic::Color _WindowLight;
        basic::Color _WindowDark;
        basic::Color _WindowRaised;
        basic::Color _WindowSunken;
        basic::Color _ActiveItems;
        basic::Color _Dialog;
        basic::Color _DialogActive;
        graphics::Font _DialogFont;
        basic::Color _EditZone;
        graphics::Font _EditZoneFont;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, SkinTheme);
}
}
#endif
