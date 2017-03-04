#include "wide/ui/skin/ui_skin_theme.h"
#include "coffee.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::SkinTheme);
        COFFEE_Attribute(graphics::Font, _Font, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_AttributeCustom(real, _Transparency, COFFEE_New(meta::ParamScalarReal, meta::MODE_Default, 0.0f, 1.0f));
        COFFEE_Attribute(basic::Color, _Shadows, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Color, _Bump, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Color, _Window, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Color, _WindowLight, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Color, _WindowDark, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Color, _WindowRaised, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Color, _WindowSunken, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Color, _ActiveItems, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Color, _Dialog, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Color, _DialogActive, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(graphics::Font, _DialogFont, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Color, _EditZone, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(graphics::Font, _EditZoneFont, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SkinTheme::SkinTheme()
    {
    }

    //--------------------------------------------------------------------------------------------//

    SkinTheme::~SkinTheme()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const graphics::Font& SkinTheme::GetFont() const
    {
        return _Font;
    }

    //--------------------------------------------------------------------------------------------//

    graphics::Font& SkinTheme::GetFont()
    {
        return _Font;
    }

    //--------------------------------------------------------------------------------------------//

    basic::Color SkinTheme::GetFontColor() const
    {
        if (_Font.IsAvailable())
            return _Font.GetColor();
        return basic::Color(0.6f, 0.6f, 0.6f, 1.0f);
    }
        
    //--------------------------------------------------------------------------------------------//

    const real SkinTheme::GetTransparency() const
    {
        return _Transparency;
    }

    //--------------------------------------------------------------------------------------------//

    const real SkinTheme::GetAlpha() const
    {
        return (1.0f - _Transparency);
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Color& SkinTheme::GetShadows() const
    {
        return _Shadows;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Color& SkinTheme::GetBump() const
    {
        return _Bump;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Color& SkinTheme::GetWindow() const
    {
        return _Window;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Color& SkinTheme::GetWindowLight() const
    {
        return _WindowLight;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Color& SkinTheme::GetWindowDark() const
    {
        return _WindowDark;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Color& SkinTheme::GetWindowRaised() const
    {
        return _WindowRaised;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Color& SkinTheme::GetWindowSunken() const
    {
        return _WindowSunken;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Color& SkinTheme::GetActiveItems() const
    {
        return _ActiveItems;
    }
        
    //--------------------------------------------------------------------------------------------//

    const basic::Color& SkinTheme::GetDialog() const
    {
        return _Dialog;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Color& SkinTheme::GetDialogActive() const
    {
        return _DialogActive;
    }

    //--------------------------------------------------------------------------------------------//

    const graphics::Font& SkinTheme::GetDialogFont() const
    {
        return _DialogFont;
    }

    //--------------------------------------------------------------------------------------------//

    graphics::Font& SkinTheme::GetDialogFont()
    {
        return _DialogFont;
    }

    //--------------------------------------------------------------------------------------------//

    basic::Color SkinTheme::GetDialogFontColor() const
    {
        if (_DialogFont.IsAvailable())
            return _DialogFont.GetColor();
        return basic::Color(0.8f, 0.8f, 0.8f, 1.0f);
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Color& SkinTheme::GetEditZone() const
    {
        return _EditZone;
    }

    //--------------------------------------------------------------------------------------------//

    const graphics::Font& SkinTheme::GetEditZoneFont() const
    {
        return _EditZoneFont;
    }

    //--------------------------------------------------------------------------------------------//

    graphics::Font& SkinTheme::GetEditZoneFont()
    {
        return _EditZoneFont;
    }

    //--------------------------------------------------------------------------------------------//

    basic::Color SkinTheme::GetEditZoneFontColor() const
    {
        if (_EditZoneFont.IsAvailable())
            return _EditZoneFont.GetColor();
        return basic::Color(0.8f, 0.8f, 0.8f, 1.0f);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SkinTheme::SetDefaults()
    {
        _Font = resource::Manager::Get().Load(
            storage::Path("/coffee/import/skins/default/default.font"));
        _Font.SetColor(GetFontColor());
        _Transparency = 0.24f;
        _Shadows.Set(0.0f, 0.0f, 0.0f, 0.0f);
        _Bump.Set(0.0f, 0.0f, 0.0f, 0.0f);
        _Window.Set(0.14f, 0.14f, 0.14f);
        _WindowLight.Set(0.24f, 0.24f, 0.24f);
        _WindowDark.Set(0.0f, 0.0f, 0.0f);
        _WindowRaised.Set(0.21f, 0.21f, 0.21f);
        _WindowSunken.Set(0.12f, 0.12f, 0.12f);
        _ActiveItems.Set(0.12f, 0.37f, 0.35f);
        _Dialog.Set(0.15f, 0.15f, 0.15f);
        _DialogActive.Set(0.11f, 0.11f, 0.11f);
        _DialogFont = resource::Manager::Get().Load(
            storage::Path("/coffee/import/skins/default/default.font"));
        _DialogFont.SetColor(GetDialogFontColor());
        _EditZone.Set(0.07f, 0.07f, 0.07f);
        _EditZoneFont = resource::Manager::Get().Load(
            storage::Path("/coffee/import/skins/default/default.font"));
        _EditZoneFont.SetColor(GetEditZoneFontColor());
    }

}
}
