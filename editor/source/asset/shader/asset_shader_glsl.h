#ifndef _EDITOR_ASSET_SHADER_GLSL_H_
#define _EDITOR_ASSET_SHADER_GLSL_H_

#include "coffee_editor_includes.h"
#include "asset/asset_importer.h"
#include "asset/asset_manager.h"
#include "asset/shader/asset_shader_property.h"

namespace coffee_editor
{
namespace asset
{
    //--------------------------------------------------------------------------------------------//
    /// GLSL shader importer
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API ShaderGLSL : public Importer
    {
        COFFEE_Type(ShaderGLSL);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ShaderGLSL();
        ~ShaderGLSL();

        //-QUERIES--------------------------------------------------------------------------------//

        static bool IsSupporting(const basic::String& file_extension);

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Import();
        void OnPostSaveResources();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        uint32 _VertexBufferStates;
        graphics::RenderState _RenderStates;
        graphics::SHADER_SOURCE_INPUT _GeometryInput;
        graphics::SHADER_SOURCE_OUTPUT _GeometryOutput;
        uint32 _GeometryMaxOutputVertex;
        basic::Prow<graphics::ShaderProperty*, true> _Properties;
        basic::Prow<graphics::ShaderProperty*, true> _Textures;
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, ShaderGLSL);
}
}
#endif
