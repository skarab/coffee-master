#ifndef _COFFEE_GRAPHICS_MATERIAL_H_
#define _COFFEE_GRAPHICS_MATERIAL_H_

#include "coffee_includes.h"
#include "system/graphics/shader/graphics_shader.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Material
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Material : public resource::Object
    {
        COFFEE_Resource(Material);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Material();
        ~Material();

        //-ACCESSORS------------------------------------------------------------------------------//

        const Shader& GetShader() const { return _Shader.Get(); }
        Shader& GrabShader() { return _Shader.Grab(); }
        const RenderState& GetRenderState() const { return _Shader.Get().GetRenderState(); }
        RenderState& GrabRenderState() { return _Shader.Grab().GrabRenderState(); }
        
        //-QUERIES--------------------------------------------------------------------------------//

        bool IsOpaque() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Initialize();
        bool Finalize();
        bool Bind();
        bool UnBind();
        
        //-HANDLERS-------------------------------------------------------------------------------//

        bool OnInstantiateProperty(resource::PropertyBase& property, resource::PropertyBase& source_property, bool it_is_instantiating);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        resource::Property< Shader > _Shader;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Material);
}
}
#endif
