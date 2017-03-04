//------------------------------------------------------------------------------------------------//
/// @file system/graphics/font/graphics_font_glyph.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "system/graphics/font/graphics_font_glyph.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::FontGlyph);
        COFFEE_Attribute(basic::Vector2i, _Position, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Vector2i, _Size, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    FontGlyph::FontGlyph()
    {
    }

    //--------------------------------------------------------------------------------------------//

    FontGlyph::~FontGlyph()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void FontGlyph::SetPosition(const basic::Vector2i& position)
    {
        _Position = position;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Vector2i& FontGlyph::GetPosition()
    {
        return _Position;
    }

    //--------------------------------------------------------------------------------------------//

    void FontGlyph::SetSize(const basic::Vector2i& size)
    {
        _Size = size;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Vector2i& FontGlyph::GetSize()
    {
        return _Size;
    }

}
}
//------------------------------------------------------------------------------------------------//
