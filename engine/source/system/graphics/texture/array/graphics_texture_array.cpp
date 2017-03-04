#include "system/graphics/texture/array/graphics_texture_array.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginResource(graphics, TextureArray, "Texture Array", "texture", 0);
        COFFEE_Ancestor(graphics::Texture);
        COFFEE_ResourceProperty(< basic::Image* >, _Images, meta::MODE_Serializeable | meta::MODE_Editable, 0);
        COFFEE_ResourceProperty(uint32, _Index, meta::MODE_None, 0);
    COFFEE_EndResource();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    TextureArray::TextureArray()
    {
    }

    //--------------------------------------------------------------------------------------------//

    TextureArray::~TextureArray()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const basic::Prow<basic::Image*, true>& TextureArray::GetImages() const
    {
        return _Images.Get();
    }

    //--------------------------------------------------------------------------------------------//

    basic::Prow<basic::Image*, true>& TextureArray::GrabImages()
    {
        return _Images.Grab();
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool TextureArray::IsValid() const
    {
        return _Images.Get().GetSize()>0;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool TextureArray::Initialize()
    {
        if (!IsValid())
            return true;

        basic::Prow<basic::Image*, true>& images = GrabImages();
        uint8* texels = (uint8*)COFFEE_Allocate(images[0]->GetWidth()*images[0]->GetHeight()*4*images.GetSize());
        for (uint32 i=0 ; i<images.GetSize() ; ++i)
        {
            COFFEE_Assert(images[i]->GetDataSize()==images[0]->GetDataSize(),
                core::ERROR_CODE_IncorrectUsage, "Texture array require each texture to be the same size");
            COFFEE_Assert(images[i]->GetComponentType()==meta::SCALAR_FORMAT_UInt8
                && images[i]->GetComponentCount()==4,
                core::ERROR_CODE_IncorrectUsage, "Texture array supports only RGBA8 for now");
            memcpy(texels+i*images[i]->GetDataSize(), images[i]->GetData(), images[i]->GetDataSize());
        }    

        glEnable(GL_TEXTURE_2D_ARRAY_EXT);
        glGenTextures(1, &_Index.Grab());
        glBindTexture(GL_TEXTURE_2D_ARRAY_EXT, _Index.Get());
        glTexImage3D(GL_TEXTURE_2D_ARRAY_EXT, 0, GL_RGBA8, images[0]->GetWidth(), images[0]->GetHeight(), images.GetSize(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texels);
        
        COFFEE_Free(texels);

        if (IsParameterEnabled(TEXTURE_PARAMETER_BilinearFiltering))
        {
            glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        else
        {
            glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }
        glDisable(GL_TEXTURE_2D_ARRAY_EXT);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool TextureArray::Finalize()
    {
        if (IsValid())
            glDeleteTextures(1, &_Index.Grab());
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void TextureArray::Bind(uint32 multi_texture_index)
    {
        if (IsValid())
        {
            glActiveTexture(GL_TEXTURE0 + multi_texture_index);
            glEnable(GL_TEXTURE_2D_ARRAY_EXT);
            glBindTexture(GL_TEXTURE_2D_ARRAY_EXT, _Index.Get());
        }
    }

    //--------------------------------------------------------------------------------------------//

    void TextureArray::UnBind(uint32 multi_texture_index)
    {
        if (IsValid())
        {
            glActiveTexture(GL_TEXTURE0 + multi_texture_index);
            glBindTexture(GL_TEXTURE_2D_ARRAY_EXT, 0);
            glDisable(GL_TEXTURE_2D_ARRAY_EXT);
        }
    }

}
}
