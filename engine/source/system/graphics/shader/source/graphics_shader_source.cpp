#include "system/graphics/shader/source/graphics_shader_source.h"
#include "system/graphics/device/graphics_device.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::ShaderSource);
        COFFEE_Attribute(basic::Text, _VertexShader, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Text, _GeometryShader, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Text, _FragmentShader, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(graphics::SHADER_SOURCE_INPUT, _GeometryInput, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(graphics::SHADER_SOURCE_OUTPUT, _GeometryOutput, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(uint32, _GeometryMaxOutputVertex, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ShaderSource::ShaderSource() :
        _ProgramIndex(NONE),
        _VertexShaderIndex(NONE),
        _GeometryShaderIndex(NONE),
        _FragmentShaderIndex(NONE),
        _GeometryInput(SHADER_SOURCE_INPUT_Triangles),
        _GeometryOutput(SHADER_SOURCE_OUTPUT_TriangleStrip),
        _GeometryMaxOutputVertex(18)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ShaderSource::~ShaderSource()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool ShaderSource::Create()
    {
        char* vs_data;
        char* gs_data;
        char* fs_data;
        basic::Text output;

        _VertexShaderIndex = NONE;
        _GeometryShaderIndex = NONE;
        _FragmentShaderIndex = NONE;

        COFFEE_GRAPHICS_Debug();

        _ProgramIndex = glCreateProgram();

        vs_data = GetVertexShader().GenerateTextBuffer();
        if (vs_data!=NULL)
        {
            _VertexShaderIndex = glCreateShader(GL_VERTEX_SHADER_ARB);
            glShaderSource(_VertexShaderIndex, 1, (const char **) &vs_data, NULL);
            glCompileShader(_VertexShaderIndex);
            COFFEE_Free(vs_data);
            
            GLint status;
            glGetShaderiv(_VertexShaderIndex, GL_COMPILE_STATUS, &status);
            if (status==GL_FALSE)
            {
                char log[4096];
                int size(0);
                glGetShaderInfoLog(_VertexShaderIndex, 4095, &size, log);
                log[size] = NULL_CHAR;
                COFFEE_Warning(basic::String("vertex_shader compilation failed:\n%s", log).GetBuffer());
                COFFEE_GRAPHICS_Debug();
                return false;
            }
        }

        if (Device::Get().IsSupporting(DEVICE_SUPPORT_GeometryShader))
        {
            gs_data = GetGeometryShader().GenerateTextBuffer();
            if (gs_data!=NULL)
            {
                uint32 input;
                switch (GetGeometryInput())
                {
                    case SHADER_SOURCE_INPUT_Points:                   input = GL_POINTS; break;
                    case SHADER_SOURCE_INPUT_Lines:                    input = GL_LINES; break;
                    case SHADER_SOURCE_INPUT_LineStrip:                input = GL_LINE_STRIP; break;
                    case SHADER_SOURCE_INPUT_LinesAdjacency:           input = GL_LINES_ADJACENCY_EXT; break;
                    case SHADER_SOURCE_INPUT_LineStripAdjacency:       input = GL_LINE_STRIP_ADJACENCY_EXT; break;
                    case SHADER_SOURCE_INPUT_Triangles:                input = GL_TRIANGLES; break;
                    case SHADER_SOURCE_INPUT_TriangleStrip:            input = GL_TRIANGLE_STRIP; break;
                    case SHADER_SOURCE_INPUT_TriangleFan:              input = GL_TRIANGLE_FAN; break;
                    case SHADER_SOURCE_INPUT_TrianglesAdjacency:       input = GL_TRIANGLES_ADJACENCY_EXT; break;
                    case SHADER_SOURCE_INPUT_TriangleStripAdjacency:   input = GL_TRIANGLE_STRIP_ADJACENCY_EXT; break;
                    default: COFFEE_Error(core::ERROR_CODE_Unexpected, "Unexpected error"); break;
                }
                glProgramParameteriEXT(_ProgramIndex, GL_GEOMETRY_INPUT_TYPE_EXT, input);

                uint32 output;
                switch (GetGeometryOutput())
                {
                    case SHADER_SOURCE_OUTPUT_Points:          output = GL_POINTS; break;
                    case SHADER_SOURCE_OUTPUT_LineStrip:       output = GL_LINE_STRIP; break;
                    case SHADER_SOURCE_OUTPUT_TriangleStrip:   output = GL_TRIANGLE_STRIP; break;
                    default: COFFEE_Error(core::ERROR_CODE_Unexpected, "Unexpected error"); break;
                }
                glProgramParameteriEXT(_ProgramIndex, GL_GEOMETRY_OUTPUT_TYPE_EXT, output);

                glProgramParameteriEXT(_ProgramIndex, GL_GEOMETRY_VERTICES_OUT_EXT, GetGeometryMaxOutputVertex());

                _GeometryShaderIndex = glCreateShader(GL_GEOMETRY_SHADER_EXT);
                glShaderSource(_GeometryShaderIndex, 1, (const char **) &gs_data, NULL);
                glCompileShader(_GeometryShaderIndex);
                COFFEE_Free(gs_data);
                
                GLint status;
                glGetShaderiv(_GeometryShaderIndex, GL_COMPILE_STATUS, &status);
                if (status==GL_FALSE)
                {
                    char log[4096];
                    int size(0);
                    glGetShaderInfoLog(_GeometryShaderIndex, 4095, &size, log);
                    log[size] = NULL_CHAR;
                    COFFEE_Warning(basic::String("geometry_shader compilation failed:\n%s", log).GetBuffer());
                    COFFEE_GRAPHICS_Debug();
                    return false;
                }
            }
        }

        fs_data = GetFragmentShader().GenerateTextBuffer();
        if (fs_data!=NULL)
        {
            _FragmentShaderIndex = glCreateShader(GL_FRAGMENT_SHADER_ARB);
            glShaderSource(_FragmentShaderIndex, 1, (const char **) &fs_data, NULL);
            glCompileShader(_FragmentShaderIndex);
            COFFEE_Free(fs_data);
            
            GLint status;
            glGetShaderiv(_FragmentShaderIndex, GL_COMPILE_STATUS, &status);
            if (status==GL_FALSE)
            {
                char log[4096];
                int size(0);
                glGetShaderInfoLog(_FragmentShaderIndex, 4095, &size, log);
                log[size] = NULL_CHAR;
                COFFEE_Warning(basic::String("fragment_shader compilation failed:\n%s", log).GetBuffer());
                COFFEE_GRAPHICS_Debug();
                return false;
            }
        }

        if (_VertexShaderIndex!=NONE)
            glAttachShader(_ProgramIndex, _VertexShaderIndex);
        
        if (_GeometryShaderIndex!=NONE)
            glAttachShader(_ProgramIndex, _GeometryShaderIndex);
        
        if (_FragmentShaderIndex!=NONE)
            glAttachShader(_ProgramIndex, _FragmentShaderIndex);
        
        {
            glLinkProgram(_ProgramIndex);
            GLint status;
            glGetProgramiv(_ProgramIndex, GL_LINK_STATUS, &status);
            if (status==GL_FALSE)
            {
                char log[4096];
                int size(0);
                glGetProgramInfoLog(_ProgramIndex, 4095, &size, log);
                log[size] = NULL_CHAR;
                COFFEE_Warning(basic::String("shader linkage failed:\n%s", log).GetBuffer());
                COFFEE_GRAPHICS_Debug();
                return false;
            }
        }

        /*
            Enable this only when importing the shader since it causes performance lose.
            It mays check for correct binding of uniforms as well...
        {
            glValidateProgram(_ProgramIndex);
            GLint status;
            glGetProgramiv(_ProgramIndex, GL_VALIDATE_STATUS, &status);
            if (status==GL_FALSE)
            {
                char log[4096];
                int size(0);
                glGetProgramInfoLog(_ProgramIndex, 4095, &size, log);
                log[size] = NULL_CHAR;
                COFFEE_Warning(basic::String("shader validation failed:\n%s", log).GetBuffer());
                COFFEE_GRAPHICS_Debug();
                return false;
            }
        }*/
        COFFEE_GRAPHICS_Debug();
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void ShaderSource::Destroy()
    {
        COFFEE_GRAPHICS_Debug();
        if (_VertexShaderIndex!=NONE)
        {
            glDetachShader(_ProgramIndex, _VertexShaderIndex);
            glDeleteShader(_VertexShaderIndex);
        }

        if (_GeometryShaderIndex!=NONE)
        {
            glDetachShader(_ProgramIndex, _GeometryShaderIndex);
            glDeleteShader(_GeometryShaderIndex);
        }

        if (_FragmentShaderIndex!=NONE)
        {
            glDetachShader(_ProgramIndex, _FragmentShaderIndex);
            glDeleteShader(_FragmentShaderIndex);
        }

        glDeleteProgram(_ProgramIndex);
        COFFEE_GRAPHICS_Debug();
    }

    //--------------------------------------------------------------------------------------------//

    void ShaderSource::Bind()
    {
        glUseProgram(_ProgramIndex);        
    }

    //--------------------------------------------------------------------------------------------//

    void ShaderSource::UnBind()
    {
        glUseProgram(0);
    }
    
    //--------------------------------------------------------------------------------------------//

    bool ShaderSource::InitializeProperty(ShaderProperty& property)
    {
        glUseProgram(_ProgramIndex);
        uint32 identifier = glGetUniformLocation(_ProgramIndex,
            basic::String(property.GetName()).GetBuffer());
        property.SetIdentifier(identifier);
        glUseProgram(0);
        return identifier!=NONE;
    }

    //--------------------------------------------------------------------------------------------//

    void ShaderSource::BindProperty(ShaderProperty& property)
    {
        if (property.GetIdentifier()==NONE)
            return;

        int32 slot;
        switch (property.GetType())
        {
            case SHADER_PROPERTY_TYPE_Texture:
                slot = (int32)property.GetEvaluator() - (int32)SHADER_EVALUATOR_MultiTexture0;
                glUniform1i(property.GetIdentifier(), slot);
                break;

            case SHADER_PROPERTY_TYPE_Real:
                glUniform1f(property.GetIdentifier(), *(real*)property.GetValue().GetScalarObject());
                break;

            case SHADER_PROPERTY_TYPE_Boolean:
                glUniform1i(property.GetIdentifier(), *(int32*)property.GetValue().GetScalarObject());
                break;

            case SHADER_PROPERTY_TYPE_Integer:
                glUniform1i(property.GetIdentifier(), *(int32*)property.GetValue().GetScalarObject());
                break;

            case SHADER_PROPERTY_TYPE_Vector2:
                glUniform2fv(property.GetIdentifier(), 1, &((basic::Vector2*) property.GetValue().GetObject())->X);
                break;

            case SHADER_PROPERTY_TYPE_Vector3:
                glUniform3fv(property.GetIdentifier(), 1, &((basic::Vector3*) property.GetValue().GetObject())->X);
                break;

            case SHADER_PROPERTY_TYPE_Color:
                glUniform4fv(property.GetIdentifier(), 1, ((basic::Color*) property.GetValue().GetObject())->GetBuffer());
                break;

            case SHADER_PROPERTY_TYPE_Matrix4x4:
                glUniformMatrix4fv(property.GetIdentifier(), 1, GL_FALSE, ((basic::Matrix*) property.GetValue().GetObject())->GetData());
                break;
        }
    }

}
}
