#include "system/graphics/texture/graphics_texture.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginResource(graphics, Texture, "Texture", "texture", 0);
        COFFEE_Ancestor(resource::Object);
        COFFEE_ResourceProperty(graphics::TEXTURE_PARAMETER, _Parameters, meta::MODE_Serializeable | meta::MODE_Editable, 0);
    COFFEE_EndResource();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Texture::Texture() :
        _Parameters(TEXTURE_PARAMETER_Null)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Texture::~Texture()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Texture::SetParameters(uint32 parameters)
    {
        _Parameters.Set(parameters);
    }

    //--------------------------------------------------------------------------------------------//

    void Texture::EnableParameter(const TEXTURE_PARAMETER& parameter, bool it_has_to_enable)
    {
        if(it_has_to_enable)
        {
            _Parameters.Set(_Parameters.Get() | (uint32) parameter);
        }
        else
        {
            _Parameters.Set(_Parameters.Get() & ~parameter);
        }
    }

    //--------------------------------------------------------------------------------------------//

    bool Texture::IsParameterEnabled(const TEXTURE_PARAMETER& parameter) const
    {
        return (_Parameters.Get() & (uint32) parameter) != 0;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool Texture::Initialize()
    {
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Texture::Finalize()
    {
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void Texture::Bind(uint32 multi_texture_index)
    {
        if (IsInstantiated() && IsAvailable())
            return ((Texture*)&GetResource())->Bind(multi_texture_index);
    }

    //--------------------------------------------------------------------------------------------//

    void Texture::UnBind(uint32 multi_texture_index)
    {
        if (IsInstantiated() && IsAvailable())
            return ((Texture*)&GetResource())->UnBind(multi_texture_index);
    }

}
}
