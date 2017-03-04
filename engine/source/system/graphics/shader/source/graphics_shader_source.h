#ifndef _COFFEE_GRAPHICS_SHADER_SOURCE_H_
#define _COFFEE_GRAPHICS_SHADER_SOURCE_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "kernel/resource/resources.h"
#include "system/graphics/shader/graphics_shader_property.h"
#include "system/graphics/shader/source/graphics_shader_source_input.h"
#include "system/graphics/shader/source/graphics_shader_source_output.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Graphics shader
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ShaderSource : public meta::Object
    {
        COFFEE_Type(ShaderSource);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ShaderSource();
        ~ShaderSource();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetVertexShader(const basic::Text& vertex_shader) { _VertexShader = vertex_shader; }
        const basic::Text& GetVertexShader() const { return _VertexShader; }
        void SetGeometryShader(const basic::Text& geometry_shader) { _GeometryShader = geometry_shader; }
        const basic::Text& GetGeometryShader() const { return _GeometryShader; }
        void SetFragmentShader(const basic::Text& fragment_shader) { _FragmentShader = fragment_shader; }
        const basic::Text& GetFragmentShader() const { return _FragmentShader; }
        void SetGeometryInput(SHADER_SOURCE_INPUT geometry_input) { _GeometryInput = geometry_input; }
        SHADER_SOURCE_INPUT GetGeometryInput() const { return _GeometryInput; }
        void SetGeometryOutput(SHADER_SOURCE_OUTPUT geometry_output) { _GeometryOutput = geometry_output; }
        SHADER_SOURCE_OUTPUT GetGeometryOutput() const { return _GeometryOutput; }
        void SetGeometryMaxOutputVertex(uint32 max_vertex_count) { _GeometryMaxOutputVertex = max_vertex_count; }
        uint32 GetGeometryMaxOutputVertex() const { return _GeometryMaxOutputVertex; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Create();
        void Destroy();
        void Bind();
        void UnBind();
        bool InitializeProperty(ShaderProperty& property);
        void BindProperty(ShaderProperty& property);
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Text _VertexShader;
        basic::Text _GeometryShader;
        basic::Text _FragmentShader;
        SHADER_SOURCE_INPUT _GeometryInput;
        SHADER_SOURCE_OUTPUT _GeometryOutput;
        uint32 _GeometryMaxOutputVertex;
        uint32 _ProgramIndex;
        uint32 _VertexShaderIndex;
        uint32 _GeometryShaderIndex;
        uint32 _FragmentShaderIndex;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ShaderSource);
}
}
#endif
