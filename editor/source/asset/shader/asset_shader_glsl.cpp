#include "asset/shader/asset_shader_glsl.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(asset::ShaderGLSL);
        COFFEE_Ancestor(asset::Importer);
        COFFEE_AttributeCustom(uint32, _VertexBufferStates, COFFEE_New(meta::ParamEnumMulti, meta::MODE_Serializeable | meta::MODE_Editable,
            basic::String("graphics::VERTEX_BUFFER_TYPE")));
        COFFEE_Attribute(graphics::RenderState, _RenderStates, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(graphics::SHADER_SOURCE_INPUT, _GeometryInput, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(graphics::SHADER_SOURCE_OUTPUT, _GeometryOutput, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(uint32, _GeometryMaxOutputVertex, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_AttributeCustom(< graphics::ShaderProperty* >, _Properties, COFFEE_New(meta::ParamArray, meta::MODE_Serializeable
            | meta::MODE_Editable, "Name"));
        COFFEE_AttributeCustom(< graphics::ShaderProperty* >, _Textures, COFFEE_New(meta::ParamArray, meta::MODE_Serializeable
            | meta::MODE_Editable, "Name"));
    COFFEE_EndType();

namespace asset
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ShaderGLSL::ShaderGLSL() :
        _VertexBufferStates(0),
        _GeometryInput(graphics::SHADER_SOURCE_INPUT_Triangles),
        _GeometryOutput(graphics::SHADER_SOURCE_OUTPUT_TriangleStrip),
        _GeometryMaxOutputVertex(18)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ShaderGLSL::~ShaderGLSL()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool ShaderGLSL::IsSupporting(const basic::String& file_extension)
    {
        return file_extension=="glsl";
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool ShaderGLSL::Import()
    {
        storage::Data* file_data = storage::System::Get().GetFileData(GetAssetPath());
        if (file_data==NULL)
            return false;
        if (file_data->GetSize()==0)
        {
            COFFEE_Delete(file_data);
            return false;
        }

        storage::Path file_path = Manager::Get().GetResourcePath(GetAssetPath())
            + "/" + GetAssetPath().GetFileNameWithoutExtension() + ".shader";

        graphics::Shader* shader;
        shader = COFFEE_New(graphics::Shader);

        basic::Text shader_text, vertex_text, geometry_text, fragment_text;
        shader_text.Set(file_data->GetBuffer(), file_data->GetSize());
        
        basic::Text* current(NULL);
        for (uint32 index=0 ; index<shader_text.GetLineCount() ; ++index)
        {
            const basic::String& line = shader_text.GetLine(index);
            if (line.IsPrefixed("//"))
            {
                if (line.IsContaining("vertex_shader"))
                {
                    current = &vertex_text;
                }
                else if (line.IsContaining("geometry_shader"))
                {
                    current = &geometry_text;
                }
                else if (line.IsContaining("fragment_shader"))
                {
                    current = &fragment_text;
                }
            }
            else if (current!=NULL)
            {
                if (line.IsContaining("#include"))
                {
                    uint32 i = line.Find('\"');
                    uint32 j = line.FindLast('\"');
                    if (i==NONE || j==NONE || i==j)
                    {
                        COFFEE_Warning("Include is broken");
                    }
                    else
                    {
                        storage::Path filepath = GetAssetPath().GetPath()+"/"+line.GetCenter(i+1, j-1);
                        storage::Data* data = storage::System::Get().GetFileData(filepath);
                        if (data==NULL)
                        {
                             COFFEE_Warning("Include file doesn't exist");
                        }
                        else
                        {
                            basic::Text inc;
                            inc.Set(data->GetBuffer(), data->GetSize());
                            *current += inc;
                            COFFEE_Delete(data);
                        }
                    }
                }
                else
                {
                    current->AddLine(line);
                }
            }
        }

        shader->GrabSource().SetVertexShader(vertex_text);
        shader->GrabSource().SetGeometryShader(geometry_text);
        shader->GrabSource().SetFragmentShader(fragment_text);
        COFFEE_Delete(file_data);

        shader->GrabSource().SetGeometryInput(_GeometryInput);
        shader->GrabSource().SetGeometryOutput(_GeometryOutput);
        shader->GrabSource().SetGeometryMaxOutputVertex(_GeometryMaxOutputVertex);

        shader->GrabProperties() = _Properties;
        shader->GrabTextures() = _Textures;
        
        if (!shader->Initialize())
        {
            memset(_Properties.GetLinearBuffer(), NULL, sizeof(void*)*_Properties.GetSize());
            memset(_Textures.GetLinearBuffer(), NULL, sizeof(void*)*_Textures.GetSize());
            COFFEE_Delete(shader);
            return false;
        }

        shader->GrabRenderState() = _RenderStates;
        shader->SetVertexBufferStates(_VertexBufferStates);

        shader->PreCreateLOD(0);
        resource::Chunk* resource_chunk;
        resource_chunk = resource::Manager::Get().Create(file_path);
        resource_chunk->AddLOD(*shader);
        
        DeleteImportedResources();
        AddImportedResource(resource_chunk);
        
        // Create material
        graphics::Material* material = COFFEE_New(graphics::Material);
        material->PreCreateLOD(0);
        material->GrabShader() = resource::Manager::Get().Load(file_path);
        file_path = Manager::Get().GetResourcePath(GetAssetPath())
            + "/" + GetAssetPath().GetFileNameWithoutExtension() + ".material";
        resource_chunk = resource::Manager::Get().Create(file_path);
        resource_chunk->AddLOD(*material);

        AddImportedResource(resource_chunk);        
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void ShaderGLSL::OnPostSaveResources()
    {
        if (_Resources.GetSize()>0 && _Resources[0]->GetLOD(0).GetData().IsKindOf<graphics::Shader>())
        {
            graphics::Shader& shader = static_cast<graphics::Shader&>(_Resources[0]->GetLOD(0).GetData());
            memset(_Properties.GetLinearBuffer(), NULL, sizeof(void*)*_Properties.GetSize());
            memset(_Textures.GetLinearBuffer(), NULL, sizeof(void*)*_Textures.GetSize());
            _Properties = shader.GrabProperties();
            _Textures = shader.GrabTextures();        
            memset(shader.GrabProperties().GetLinearBuffer(), NULL, sizeof(void*)*_Properties.GetSize());
            memset(shader.GrabTextures().GetLinearBuffer(), NULL, sizeof(void*)*_Textures.GetSize());
        }
    }

}
}
