#include "wide/ui/skin/ui_skin_widget.h"
#include "wide/ui/skin/ui_skin.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::SkinWidget);
        COFFEE_Attribute(basic::String, _Name, meta::MODE_Serializeable);
        COFFEE_Attribute(basic::Vector2i, _BorderSize, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(graphics::Font, _Font, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(bool, _ItHasShadowsEnabled, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Color, _ShadowsColor, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(bool, _ItHasBumpEnabled, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Color, _BumpColor, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SkinWidget::SkinWidget() :
        _WidgetType(NULL),
        _State(NULL),
        _ItHasShadowsEnabled(false),
        _ItHasBumpEnabled(false)
    {
    }

    //--------------------------------------------------------------------------------------------//

    SkinWidget::SkinWidget(basic::String name, meta::Class& widget_type) :
        _Name(name),
        _WidgetType(&widget_type),
        _BorderSize(2, 2),
        _State(NULL),
        _ItHasShadowsEnabled(false),
        _ItHasBumpEnabled(false)
    {
    }

    //--------------------------------------------------------------------------------------------//

    SkinWidget::~SkinWidget()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const basic::String& SkinWidget::GetName() const
    {
        return _Name;
    }

    //--------------------------------------------------------------------------------------------//

    const meta::Class& SkinWidget::GetWidgetType() const
    {
        return *_WidgetType;
    }

    //--------------------------------------------------------------------------------------------//

    void SkinWidget::SetBorderSize(const basic::Vector2i& border_size)
    {
        _BorderSize = border_size;
    }

    void SkinWidget::SetFont(graphics::Font& font)
    {
        _Font = font;
    }

    //--------------------------------------------------------------------------------------------//

    const graphics::Font& SkinWidget::GetFont() const
    {
        return _Font;
    }

    //--------------------------------------------------------------------------------------------//

    graphics::Font& SkinWidget::GetFont()
    {
        return _Font;
    }

    //--------------------------------------------------------------------------------------------//

    void SkinWidget::SetShadowsColor(const basic::Color& color)
    {
        _ShadowsColor = color;
    }

    //--------------------------------------------------------------------------------------------//

    void SkinWidget::EnableShadows(bool it_has_to_enable_shadows)
    {
        _ItHasShadowsEnabled = it_has_to_enable_shadows;
    }

    //--------------------------------------------------------------------------------------------//

    bool SkinWidget::HasShadowsEnabled() const
    {
        return _ItHasShadowsEnabled;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Color& SkinWidget::GetShadowsColor() const
    {
        return _ShadowsColor;
    }

    //--------------------------------------------------------------------------------------------//

    void SkinWidget::SetBumpColor(const basic::Color& color)
    {
        _BumpColor = color;
    }

    //--------------------------------------------------------------------------------------------//

    void SkinWidget::EnableBump(bool it_has_to_enable_bump)
    {
        _ItHasBumpEnabled = it_has_to_enable_bump;
    }

    //--------------------------------------------------------------------------------------------//

    bool SkinWidget::HasBumpEnabled() const
    {
        return _ItHasBumpEnabled;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Color& SkinWidget::GetBumpColor() const
    {
        return _BumpColor;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    const basic::Vector2i& SkinWidget::GetBorderSize() const
    {
        return _BorderSize;
    }

    //--------------------------------------------------------------------------------------------//

    basic::Vector2i SkinWidget::GetCharacterSize(char character) const
    {
        basic::Vector2i size;
        if (_Font.IsAvailable())
        {
            size.Y = _Font.GetHeight();

            if (character>=_Font.GetFirstCharacterCode()
                && character<=_Font.GetLastCharacterCode())
            {
                size.X = _Font.GetGlyphArray()[
                    character-_Font.GetFirstCharacterCode()]->GetSize().X;
            }
        }
        return size;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 SkinWidget::GetTextWidth(const basic::String & text) const
    {
        uint32 width(0);
        for (uint32 char_index=0 ; char_index<text.GetLength() ; ++char_index)
            width += GetCharacterSize(text[char_index]).X;
        return width;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 SkinWidget::GetFontHeight() const
    {
        if (_Font.IsAvailable())
            return _Font.GetHeight();
        return 0;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SkinWidget::ApplyTheme(SkinTheme& theme)
    {
        _Font = theme.GetFont();
    }

    //--------------------------------------------------------------------------------------------//

    void SkinWidget::Render(Window& window, const SkinContext& paint_context)
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void SkinWidget::_SetState(SkinWidgetState& state)
    {
        _State = &state;
        _Font.SetColor(_State->GetFontColor());
    }

    //--------------------------------------------------------------------------------------------//

    const SkinWidgetState& SkinWidget::_GetState() const
    {
        return *_State;
    }

}
}
