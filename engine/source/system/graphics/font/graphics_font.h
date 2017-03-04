#ifndef _COFFEE_GRAPHICS_FONT_H_
#define _COFFEE_GRAPHICS_FONT_H_

#include "coffee_includes.h"
#include "kernel/basic/raster/basic_raster.h"
#include "system/graphics/font/graphics_font.h"
#include "system/graphics/font/graphics_font_glyph.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Font based on glyph images.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Font : public resource::Object
    {
        COFFEE_Resource(Font);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Font();
        ~Font();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetColor(const basic::Color& color);
        const basic::Color& GetColor() const;
        const basic::Prow<FontGlyph*, true>& GetGlyphArray() const;
        basic::Prow<FontGlyph*, true>& GrabGlyphArray();
        void SetHeight(uint32 height);
        virtual uint32 GetHeight() const;
        void SetFirstCharacterCode(uint8 first_character_code);
        uint8 GetFirstCharacterCode() const;
        void SetLastCharacterCode(uint8 last_character_code);
        uint8 GetLastCharacterCode() const;
        const basic::Image& GetGlyphImage() const;
        basic::Image& GrabGlyphImage();

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual bool Initialize();
        virtual bool Finalize();

        void Print(const basic::String& text, const basic::Vector2i& position) const;
        void Destroy();
        bool ExtractGlyph(basic::Image& glyph_image, char glyph);

        //-HANDLERS-------------------------------------------------------------------------------//

        bool OnInstantiateProperty(resource::PropertyBase& property, resource::PropertyBase& source_property, bool it_is_instantiating);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        resource::Property<basic::Color> _Color;
        resource::Property<basic::Prow< FontGlyph*, true> > _GlyphArray;
        resource::Property<uint32> _Height;
        resource::Property<uint8> _FirstCharacterCode;
        resource::Property<uint8> _LastCharacterCode;
        resource::Property<basic::Image> _GlyphImage;
        resource::Property<uint32> _TextureIndex;
        resource::Property<uint32> _DisplayListIndex;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Font);
}
}
#endif
