#include "system/graphics/material/graphics_material.h"
#include "system/graphics/renderer/graphics_renderer.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginResource(graphics, Material, "Material", "material", 0);
        COFFEE_Ancestor(resource::Object);
        COFFEE_ResourceProperty(graphics::Shader, _Shader, meta::MODE_Serializeable | meta::MODE_Editable,
            resource::PROPERTY_FLAG_Instantiable);
    COFFEE_EndResource();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Material::Material()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Material::~Material()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Material::IsOpaque() const
    {
        return !_Shader.Get().IsAvailable() || !_Shader.Get().GetRenderState().IsBlendingEnabled();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool Material::Initialize()
    {
        if (_Shader.Get().GetFilePath().IsEmpty())
        {
            _Shader = graphics::Shader(resource::Manager::Get().Load(
                storage::Path("/coffee/import/shaders/default.shader")));
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Material::Finalize()
    {
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Material::Bind()
    {
        if (!IsAvailable() || !_Shader.Get().IsAvailable())
            return true;

        if (Renderer::Get().IsLockingMaterial())
            return false;

        return _Shader.Grab().Bind();
    }

    //--------------------------------------------------------------------------------------------//

    bool Material::UnBind()
    {
        if (!IsAvailable() || !_Shader.Get().IsAvailable())
            return true;

        if (Renderer::Get().IsLockingMaterial())
            return false;

        return _Shader.Grab().UnBind();
    }
    
    //-HANDLERS-----------------------------------------------------------------------------------//

    bool Material::OnInstantiateProperty(resource::PropertyBase& property, resource::PropertyBase& source_property, bool it_is_instantiating)
    {
        if (&property==&_Shader)
        {
            Shader& shader = _Shader.GrabValue();
            shader = graphics::Shader(resource::Manager::Get().Load(
                storage::Path("/coffee/import/shaders/none.shader")));

            if (it_is_instantiating)
            {
                Shader& source_shader = static_cast< resource::Property<Shader>& >(source_property).Grab();
                _Shader.SetValue(source_shader);
            }
            return true;
        }
        return false;
    }

}
}
