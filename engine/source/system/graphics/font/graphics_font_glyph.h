#ifndef _COFFEE_GRAPHICS_FONT_GLYPH_H_
#define _COFFEE_GRAPHICS_FONT_GLYPH_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Font glyph
    ///
    /// It contains information about glyph position in the global image.
    ///
    /// @see coffee::graphics::Font
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API FontGlyph : public meta::Object
    {
        COFFEE_Type(FontGlyph);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        FontGlyph();
        ~FontGlyph();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetPosition(const basic::Vector2i& position);
        const basic::Vector2i& GetPosition();
        void SetSize(const basic::Vector2i& size);
        const basic::Vector2i& GetSize();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Vector2i _Position;
        basic::Vector2i _Size;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, FontGlyph);
}
}
#endif
