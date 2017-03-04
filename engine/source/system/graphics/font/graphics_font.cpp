#include "system/graphics/font/graphics_font.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/device/graphics_device.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginResource(graphics, Font, "Font", "font", 0);
        COFFEE_Ancestor(resource::Object);
        COFFEE_ResourceProperty(basic::Color, _Color, meta::MODE_Serializeable | meta::MODE_Editable, resource::PROPERTY_FLAG_Instantiable);
        COFFEE_ResourceProperty(< graphics::FontGlyph* >, _GlyphArray, meta::MODE_Serializeable, 0);
        COFFEE_ResourceProperty(uint32, _Height, meta::MODE_Serializeable, 0);
        COFFEE_ResourceProperty(uint8, _FirstCharacterCode, meta::MODE_Serializeable, 0);
        COFFEE_ResourceProperty(uint8, _LastCharacterCode, meta::MODE_Serializeable, 0);
        COFFEE_ResourceProperty(basic::Image, _GlyphImage, meta::MODE_Serializeable | meta::MODE_Editable, 0);
        COFFEE_ResourceProperty(uint32, _TextureIndex, 0, 0);
        COFFEE_ResourceProperty(uint32, _DisplayListIndex, 0, 0);
    COFFEE_EndResource();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Font::Font() :
        _Height(NULL),
        _FirstCharacterCode(0),
        _LastCharacterCode(0)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Font::~Font()
    {
        Destroy();
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Font::SetColor(const basic::Color& color)
    {
        _Color.Set(color);
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Color& Font::GetColor() const
    {
        return _Color.Get();
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Prow<FontGlyph*, true>& Font::GetGlyphArray() const
    {
        return _GlyphArray.Get();
    }

    //--------------------------------------------------------------------------------------------//

    basic::Prow<FontGlyph*, true>& Font::GrabGlyphArray()
    {
        return _GlyphArray.Grab();
    }

    //--------------------------------------------------------------------------------------------//

    void Font::SetHeight(uint32 height)
    {
        _Height.Set(height);
    }

    //--------------------------------------------------------------------------------------------//

    uint32 Font::GetHeight() const
    {
        return _Height.Get();
    }

    //--------------------------------------------------------------------------------------------//

    void Font::SetFirstCharacterCode(uint8 first_character_code)
    {
        _FirstCharacterCode.Set(first_character_code);
    }

    //--------------------------------------------------------------------------------------------//

    uint8 Font::GetFirstCharacterCode() const
    {
        return _FirstCharacterCode.Get();
    }

    //--------------------------------------------------------------------------------------------//

    void Font::SetLastCharacterCode(uint8 last_character_code)
    {
        _LastCharacterCode.Set(last_character_code);
    }

    //--------------------------------------------------------------------------------------------//

    uint8 Font::GetLastCharacterCode() const
    {
        return _LastCharacterCode.Get();
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Image& Font::GetGlyphImage() const
    {
        return _GlyphImage.Get();
    }

    //--------------------------------------------------------------------------------------------//

    basic::Image& Font::GrabGlyphImage()
    {
        return _GlyphImage.Grab();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool Font::Initialize()
    {
        if (_GlyphImage.GetValue().IsEmpty())
            return true;

        glGenTextures(1, &_TextureIndex.Grab());
        glBindTexture(GL_TEXTURE_2D, _TextureIndex.Get());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA8, _GlyphImage.Get().GetWidth(), _GlyphImage.Get().GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, _GlyphImage.Get().GetData());
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _GlyphImage.Get().GetWidth(), _GlyphImage.Get().GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _GlyphImage.Get().GetData());

        _DisplayListIndex.Set(glGenLists(_LastCharacterCode.Get() - _FirstCharacterCode.Get() + 1));

        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _TextureIndex.Get());

        basic::Vector2 position, size;

        for (uint32 i=0 ; i<(uint32)_LastCharacterCode.Get()-(uint32)_FirstCharacterCode.Get()+1 ; ++i)
        {
            position.Set(
                _GlyphArray.Get()[ i ]->GetPosition().X / ((real) _GlyphImage.Get().GetWidth()),
                _GlyphArray.Get()[ i ]->GetPosition().Y / ((real) _GlyphImage.Get().GetHeight()));

            size.Set(
                _GlyphArray.Get()[ i ]->GetSize().X / ((real) _GlyphImage.Get().GetWidth()),
                _GlyphArray.Get()[ i ]->GetSize().Y / ((real) _GlyphImage.Get().GetHeight()));

            glNewList(_DisplayListIndex.Get() + i, GL_COMPILE);
                glBegin(GL_QUADS);
                    glTexCoord2f(position.X, position.Y + size.Y);
                    glVertex2i(0, 0);
                    glTexCoord2f(position.X + size.X, position.Y + size.Y);
                    glVertex2i(_GlyphArray.Get()[ i ]->GetSize().X, 0);
                    glTexCoord2f(position.X + size.X, position.Y);
                    glVertex2i(_GlyphArray.Get()[ i ]->GetSize().X, _GlyphArray.Get()[ i ]->GetSize().Y);
                    glTexCoord2f(position.X, position.Y);
                    glVertex2i(0, _GlyphArray.Get()[ i ]->GetSize().Y);
                glEnd();
            glEndList();
        }

        glDisable(GL_TEXTURE_2D);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Font::Finalize()
    {
        if (_GlyphImage.GetValue().IsEmpty())
            return true;

        glDeleteLists(_DisplayListIndex.Get(), _LastCharacterCode.Get()-_FirstCharacterCode.Get()+1);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void Font::Print(const basic::String& text, const basic::Vector2i& position) const
    {
        uint32 char_index;

        if (!IsAvailable() || _GlyphImage.Get().IsEmpty())
            return;

        Renderer::Get().SetShadeModel(RENDER_STATE_SHADE_MODEL_Flat);
        Renderer::Get().EnableDepthTest(false);
        Renderer::Get().SetColor(GetColor());
        Renderer::Get().SetBlendingFactors(RENDER_STATE_BLENDING_FACTOR_SourceAlpha, RENDER_STATE_BLENDING_FACTOR_SourceAlphaInversed);
        Renderer::Get().EnableBlending(true);

        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _TextureIndex.Get());

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0, Device::Get().GetWidth(), 0, Device::Get().GetHeight(), -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glTranslated(position.X, Device::Get().GetHeight() - (real) position.Y, 0.0f);
        glListBase(_DisplayListIndex.Get());
                
        for (char_index=0 ; char_index<text.GetLength() ; ++char_index)
        {
            unsigned char c = text.GetBuffer()[char_index]-_FirstCharacterCode.Get();

            if (c<=_LastCharacterCode.Get()-_FirstCharacterCode.Get())
            {
                glCallLists(1, GL_UNSIGNED_BYTE, &c);
                glTranslated(_GlyphArray.Get()[c]->GetSize().X, 0, 0);
            }
        }

        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glDisable(GL_TEXTURE_2D);
    }

    //--------------------------------------------------------------------------------------------//

    void Font::Destroy()
    {
        if (!IsInstantiated())
        {
            _GlyphArray.GrabValue().Erase();
            _Height.SetValue(0);
            _FirstCharacterCode.SetValue(0);
            _LastCharacterCode.SetValue(0);
        }
    }

    //--------------------------------------------------------------------------------------------//

    bool Font::ExtractGlyph(basic::Image& glyph_image, char glyph)
    {
        FontGlyph* glyph_info;
        uint32 y_index;

        if (glyph<_FirstCharacterCode.Get() || glyph>_LastCharacterCode.Get())
            return false;

        glyph_info = _GlyphArray.Get()[glyph-_FirstCharacterCode.Get()];

        glyph_image.Create(
            glyph_info->GetSize().X,
            glyph_info->GetSize().Y,
            1, meta::SCALAR_FORMAT_UInt8, 4);

        for(y_index=0 ; y_index<(uint32)glyph_info->GetSize().Y ; ++y_index)
        {
            COFFEE_Copy(((uint8 *) glyph_image.GetData()) + y_index * glyph_info->GetSize().X * 4,
                ((const uint8 *) _GlyphImage.Get().GetData()) + (y_index + glyph_info->GetPosition().Y)
                * _GlyphImage.Get().GetWidth() * 4 + glyph_info->GetPosition().X * 4,
                glyph_info->GetSize().X * 4);
        }

        return true;
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    bool Font::OnInstantiateProperty(resource::PropertyBase& property,
        resource::PropertyBase& source_property, bool it_is_instantiating)
    {
        if (&property==&_Color)
        {
            if (it_is_instantiating)
            {
                _Color.GrabValue() = static_cast<resource::Property<basic::Color>&>(source_property).Get();
            }
            return true;
        }
        return false;
    }

}
}
//------------------------------------------------------------------------------------------------//
