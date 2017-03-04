#ifndef _COFFEE_GRAPHICS_SHADER_H_
#define _COFFEE_GRAPHICS_SHADER_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "kernel/resource/resources.h"
#include "system/graphics/shader/source/graphics_shader_source.h"
#include "system/graphics/shader/graphics_shader_property.h"
#include "system/graphics/mesh/vertex_buffer/graphics_vertex_buffer_type.h"
#include "system/graphics/renderer/state/graphics_render_state.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Shader
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Shader : public resource::Object
    {
        COFFEE_Resource(Shader);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Shader();
        ~Shader();

        //-ACCESSORS------------------------------------------------------------------------------//

        const ShaderSource& GetSource() const { return _Source.Get(); }
        ShaderSource& GrabSource() { return _Source.Grab(); }
        const RenderState& GetRenderState() const { return _RenderState.Get(); }
        RenderState& GrabRenderState() { return _RenderState.Grab(); }
        void EnableVertexBuffer(const VERTEX_BUFFER_TYPE& vertex_buffer_type, bool it_has_to_enable);
        bool IsVertexBufferEnabled(const VERTEX_BUFFER_TYPE& vertex_buffer_type) const;
        void SetVertexBufferStates(uint32 states);
        basic::Prow<ShaderProperty*, true>& GrabProperties();
        basic::Prow<ShaderProperty*, true>& GrabTextures();

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsOpaque() const;
        virtual bool IsReadyToInitialize() const;
        ShaderProperty* FindProperty(basic::String property_name);

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Initialize();
        bool Finalize();
        bool Bind();
        bool UnBind();
        void SetPropertyEvaluator(basic::String property_name, SHADER_EVALUATOR evaluator);

        //-HANDLERS-------------------------------------------------------------------------------//

        bool OnInstantiateProperty(resource::PropertyBase& property,
            resource::PropertyBase& source_property, bool it_is_instantiating);

    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool _GenerateProperties();
        bool _InitializeProperty(ShaderProperty& property);
        bool _BindProperty(ShaderProperty& property);
        bool _UnBindProperty(ShaderProperty& property);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        resource::Property< ShaderSource > _Source;
        resource::Property< basic::Prow<ShaderProperty*, true> > _Properties;
        resource::Property< basic::Prow<ShaderProperty*, true> > _Textures;
        resource::Property< RenderState > _RenderState;
        resource::Property< uint32 > _VertexBufferState;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Shader);
}
}
#endif
