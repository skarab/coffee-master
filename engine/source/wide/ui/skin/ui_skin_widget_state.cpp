#include "wide/ui/skin/ui_skin_widget_state.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::SkinWidgetState);
        COFFEE_Attribute(basic::Color, _FontColor, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Color, _Color, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Color, _HighlightColor, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Color, _ShadowColor, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();
    
namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SkinWidgetState::SkinWidgetState()
    {
    }

    //--------------------------------------------------------------------------------------------//

    SkinWidgetState::~SkinWidgetState()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void SkinWidgetState::SetFontColor(const basic::Color& font_color)
    {
        _FontColor = font_color;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Color& SkinWidgetState::GetFontColor() const
    {
        return _FontColor;
    }

    //--------------------------------------------------------------------------------------------//

    void SkinWidgetState::SetColor(const basic::Color& color)
    {
        _Color = color;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Color& SkinWidgetState::GetColor() const
    {
        return _Color;
    }

    //--------------------------------------------------------------------------------------------//

    basic::Color& SkinWidgetState::GetColor()
    {
        return _Color;
    }

    //--------------------------------------------------------------------------------------------//

    void SkinWidgetState::SetHighlightColor(const basic::Color& highlight_color)
    {
        _HighlightColor = highlight_color;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Color& SkinWidgetState::GetHighlightColor() const
    {
        return _HighlightColor;
    }

    //--------------------------------------------------------------------------------------------//

    basic::Color& SkinWidgetState::GetHighlightColor()
    {
        return _HighlightColor;
    }

    //--------------------------------------------------------------------------------------------//

    void SkinWidgetState::SetShadowColor(const basic::Color& shadow_color)
    {
        _ShadowColor = shadow_color;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Color& SkinWidgetState::GetShadowColor() const
    {
        return _ShadowColor;
    }

    //--------------------------------------------------------------------------------------------//

    basic::Color& SkinWidgetState::GetShadowColor()
    {
        return _ShadowColor;
    }

}
}
