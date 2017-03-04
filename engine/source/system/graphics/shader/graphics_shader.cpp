#include "system/graphics/shader/graphics_shader.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/device/graphics_device.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginResource(graphics, Shader, "Shader", "shader", 0);
        COFFEE_Ancestor(resource::Object);
        COFFEE_ResourceProperty(graphics::ShaderSource, _Source, meta::MODE_Serializeable | meta::MODE_Editable, 0);
        COFFEE_ResourcePropertyCustom(< graphics::ShaderProperty* >, _Properties, COFFEE_New(meta::ParamArray, meta::MODE_Serializeable
            | meta::MODE_Editable, "Name"), resource::PROPERTY_FLAG_Instantiable);
        COFFEE_ResourcePropertyCustom(< graphics::ShaderProperty* >, _Textures, COFFEE_New(meta::ParamArray, meta::MODE_Serializeable
            | meta::MODE_Editable, "Name"), resource::PROPERTY_FLAG_Instantiable);
        COFFEE_ResourceProperty(graphics::RenderState, _RenderState, meta::MODE_Serializeable | meta::MODE_Editable, 0);
        COFFEE_ResourcePropertyCustom(uint32, _VertexBufferState, COFFEE_New(meta::ParamEnumMulti, meta::MODE_Serializeable | meta::MODE_Editable,
            basic::String("graphics::VERTEX_BUFFER_TYPE")), 0);
    COFFEE_EndResource();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Shader::Shader()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Shader::~Shader()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Shader::EnableVertexBuffer(const VERTEX_BUFFER_TYPE& vertex_buffer_type, bool it_has_to_enable)
    {
        if (it_has_to_enable)
        {
            _VertexBufferState.Set(_VertexBufferState.Get() | (1 << (uint32) vertex_buffer_type));
        }
        else
        {
            _VertexBufferState.Set(_VertexBufferState.Get() & (~(1 << (uint32) vertex_buffer_type)));
        }
    }

    //--------------------------------------------------------------------------------------------//

    bool Shader::IsVertexBufferEnabled(const VERTEX_BUFFER_TYPE& vertex_buffer_type) const
    {
        return ((_VertexBufferState.Get() & (1 << (uint32) vertex_buffer_type)) > 0);
    }

    //--------------------------------------------------------------------------------------------//

    void Shader::SetVertexBufferStates(uint32 states)
    {
        _VertexBufferState.Set(states);
    }

    //--------------------------------------------------------------------------------------------//

    basic::Prow<ShaderProperty*, true>& Shader::GrabProperties()
    {
        return _Properties.Grab();
    }

    //--------------------------------------------------------------------------------------------//

    basic::Prow<ShaderProperty*, true>& Shader::GrabTextures()
    {
        return _Textures.Grab();
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Shader::IsOpaque() const
    {
        return !_RenderState.Get().IsBlendingEnabled();
    }

    //--------------------------------------------------------------------------------------------//

    bool Shader::IsReadyToInitialize() const
    {
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    ShaderProperty* Shader::FindProperty(basic::String property_name)
    {
        for (uint32 index=0 ; index<_Properties.Get().GetSize() ; ++index)
        {
            if (_Properties.Get()[index]->GetName()==property_name)
                return _Properties.Grab()[index];
        }
        
        for (uint32 index=0 ; index<_Textures.Get().GetSize() ; ++index)
        {
            if (_Textures.Get()[index]->GetName()==property_name)
                return _Textures.Grab()[index];
        }

        return NULL;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool Shader::Initialize()
    {
        COFFEE_Log(core::Log::None, "Compiling shader %s", GetFilePath().GetBuffer());

        if (!_Source.GrabValue().Create())
            return false;

        if (!_GenerateProperties())
            return false;

        for (uint32 index=0 ; index<_Textures.Get().GetSize() ; ++index)
        {
            if (!_InitializeProperty(*_Textures.Grab()[index]))
                COFFEE_Log(core::Log::Warning, "%s: property %s is broken or unsupported", GetFilePath().GetBuffer(), _Textures.Grab()[index]->GetName().GetBuffer());
        }

        for (uint32 index=0 ; index<_Properties.Get().GetSize() ; ++index)
        {
            if (!_InitializeProperty(*_Properties.Grab()[index]))
                COFFEE_Log(core::Log::Warning, "%s: property %s is broken or unsupported", GetFilePath().GetBuffer(), _Properties.Grab()[index]->GetName().GetBuffer());
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Shader::Finalize()
    {
        _Source.GrabValue().Destroy();
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Shader::Bind()
    {
        if (!IsAvailable())
            return true;

        for (uint32 index=0 ; index<_Properties.Get().GetSize() ; ++index)
        {
            if (_Properties.Get()[index]->IsEnabled()
                && _Properties.Get()[index]->GetIdentifier()==NONE)
            {
                _InitializeProperty(*_Properties.Get()[index]);
            }
        }

        for (uint32 index=0 ; index<_Textures.Get().GetSize() ; ++index)
        {
            if (_Textures.Get()[index]->IsEnabled()
                && _Textures.Get()[index]->GetIdentifier()==NONE)
            {
                _InitializeProperty(*_Textures.Get()[index]);
            }
        }

        _Source.Grab().Bind();

        Renderer::Get().SetRenderState(_RenderState.Get());

        for (uint32 index=0 ; index<_Textures.Get().GetSize() ; ++index)
        {
            if (_Textures.Get()[index]->IsEnabled()
                && !_BindProperty(*_Textures.Get()[index]))
            {
                return false;
            }
        }

        for (uint32 index=0 ; index<_Properties.Get().GetSize() ; ++index)
        {
            if (_Properties.Get()[index]->IsEnabled()
                && !_BindProperty(*_Properties.Get()[index]))
            {
                return false;
            }
        }

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Shader::UnBind()
    {
        if (!IsAvailable())
            return true;

        _Source.Grab().UnBind();
        
        /* No need to do this for now
        for (uint32 index=0 ; index<_Properties.Get().GetSize() ; ++index)
        {
            if (_Properties.Get()[index]->IsEnabled()
                && !_UnBindProperty(*_Properties.Get()[index]))
            {
                return false;
            }
        }
        */

        for (uint32 index=0 ; index<_Textures.Get().GetSize() ; ++index)
        {
            if (_Textures.Get()[index]->IsEnabled()
                && !_UnBindProperty(*_Textures.Get()[index]))
            {
                return false;
            }
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void Shader::SetPropertyEvaluator(basic::String property_name, SHADER_EVALUATOR evaluator)
    {
        ShaderProperty* property = FindProperty(property_name);
        if (property!=NULL)
        {
            property->SetEvaluator(evaluator);
        }
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    bool Shader::OnInstantiateProperty(resource::PropertyBase& property,
        resource::PropertyBase& source_property, bool it_is_instantiating)
    {
        if (&property==&_Properties || &property==&_Textures)
        {
            basic::Prow<ShaderProperty*, true>& properties = &property==&_Properties?_Properties.GrabValue():_Textures.GrabValue();
            properties.Erase();
            
            if (it_is_instantiating)
            {
                basic::Prow<ShaderProperty*, true>& source_properties =
                    static_cast<resource::Property< basic::Prow<ShaderProperty*, true> >& >(source_property).Grab();
                for (uint32 index=0 ; index<source_properties.GetSize() ; ++index)
                {
                    properties.AddItem(COFFEE_New(ShaderProperty, *source_properties[index]));
                }
            }            
            return true;
        }
        return false;
    }

    //-FUNCTIONS----------------------------------------------------------------------------------//

    SHADER_PROPERTY_TYPE _GetPropertyTypeFromGLSL(const basic::String& glsl_name)
    {
        if (glsl_name == "sampler2D")              return SHADER_PROPERTY_TYPE_Texture;
        else if (glsl_name == "usampler2D")        return SHADER_PROPERTY_TYPE_Texture;
        else if (glsl_name == "sampler2DRect")     return SHADER_PROPERTY_TYPE_Texture;
        else if (glsl_name == "usampler2DRect")    return SHADER_PROPERTY_TYPE_Texture;
        else if (glsl_name == "sampler2DArray")    return SHADER_PROPERTY_TYPE_Texture;
        else if (glsl_name == "sampler3D")         return SHADER_PROPERTY_TYPE_Texture;
        else if (glsl_name == "float")             return SHADER_PROPERTY_TYPE_Real;
        else if (glsl_name == "bool")              return SHADER_PROPERTY_TYPE_Boolean;
        else if (glsl_name == "int")               return SHADER_PROPERTY_TYPE_Integer;
        else if (glsl_name == "vec2")              return SHADER_PROPERTY_TYPE_Vector2;
        else if (glsl_name == "vec3")              return SHADER_PROPERTY_TYPE_Vector3;
        else if (glsl_name == "vec4")              return SHADER_PROPERTY_TYPE_Color;
        else if (glsl_name == "mat4")              return SHADER_PROPERTY_TYPE_Matrix4x4;

        return SHADER_PROPERTY_TYPE_None;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 _FindProperty(const basic::String& name, const basic::Prow<ShaderProperty*, true>& property_array)
    {
        for (uint32 index=0 ; index<property_array.GetSize() ; ++index)
        {
            if (property_array[index]->GetName()==name)
                return index;
        }
        return NONE;
    }

    //--------------------------------------------------------------------------------------------//

    bool _GeneratePropertiesFromGLSL(
        basic::Prow<ShaderProperty*, true>& property_array,
        const basic::Text& glsl_text)
    {
        uint32 line_index;
        basic::String word;

        for (line_index=0 ; line_index<glsl_text.GetLineCount() ; ++line_index)
        {
            int32 word_index(NONE);

            while (glsl_text.GetLine(line_index).GetNextWord(word, word_index))
            {
                if(word == "uniform"
                    && glsl_text.GetLine(line_index).GetNextWord(word, word_index))
                {
                    SHADER_PROPERTY_TYPE property_type = _GetPropertyTypeFromGLSL(word);
                    glsl_text.GetLine(line_index).GetNextWord(word, word_index);
                    --word;

                    if(property_type==SHADER_PROPERTY_TYPE_None)
                    {
                        return false;
                    }
                    else if(word.GetLength()==0)
                    {
                        return false;
                    }
                    else
                    {
                        ShaderProperty* property;
                        property = COFFEE_New(ShaderProperty, word, property_type);
                        property_array.AddItem(property);
                    }
                }
            }
        }
        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool Shader::_GenerateProperties()
    {
        // Move all properties
        {
            basic::Prow<ShaderProperty*, true>& properties = _Properties.Grab();
            basic::Prow<ShaderProperty*, true>& textures = _Textures.Grab();

            for (uint32 index=0 ; index<textures.GetSize() ; ++index)
            {
                properties.AddItem(textures[index]);
                textures[index] = NULL;
            }

            textures.Erase();
        }

        basic::Prow<ShaderProperty*, true> properties;
        int32 property_index;

        // Generate properties
        if(!_GeneratePropertiesFromGLSL(properties, GetSource().GetVertexShader())
            || !_GeneratePropertiesFromGLSL(properties, GetSource().GetGeometryShader())
            || !_GeneratePropertiesFromGLSL(properties, GetSource().GetFragmentShader()))
        {
            properties.Erase();
            return false;
        }

        // Remove unused properties
        for (property_index=0 ; property_index<(int32)_Properties.Grab().GetSize() ; ++property_index)
        {
            if (_Properties.Grab()[property_index]==NULL)
            {
                _Properties.Grab().Remove(property_index);
                --property_index;
                continue;
            }

            uint32 index = _FindProperty(_Properties.Grab()[property_index]->GetName(), properties);

            if (index==NONE || _Properties.Grab()[property_index]->GetType()!=properties[index]->GetType())
            {
                _Properties.Grab().Remove(property_index);
                --property_index;
            }
            else
            {
                properties.Remove(index);
            }
        }

        // Add new properties
        for (property_index=0 ; property_index<(int32)properties.GetSize() ; ++property_index)
        {
            _Properties.Grab().AddItem(properties[property_index]);
            properties[property_index] = NULL;
        }

        // Sort properties
        {
            basic::Prow<ShaderProperty*, true>& properties = _Properties.Grab();
            basic::Prow<ShaderProperty*, true>& textures = _Textures.Grab();

            for (int32 index=0 ; index<(int32)properties.GetSize() ; ++index)
            {
                if (properties[index]->GetType()==SHADER_PROPERTY_TYPE_Texture)
                {
                    textures.AddItem(properties[index]);
                    properties[index] = NULL;
                    properties.Remove(index);
                    --index;
                }
            }
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Shader::_InitializeProperty(ShaderProperty& property)
    {
        return _Source.Grab().InitializeProperty(property);
    }

    //--------------------------------------------------------------------------------------------//

    bool Shader::_BindProperty(ShaderProperty& prop)
    {
        if (prop.HasToBindTexture())
        {
            static_cast<Texture*>(prop.GetValue().GetObject())->Bind(
                (uint32)prop.GetEvaluator()-(uint32)SHADER_EVALUATOR_MultiTexture0);
        }

        _Source.Grab().BindProperty(prop);        
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Shader::_UnBindProperty(ShaderProperty& prop)
    {
        if (prop.HasToBindTexture())
        {
            static_cast<Texture*>(prop.GetValue().GetObject())->UnBind(
                (uint32)prop.GetEvaluator()-(uint32)SHADER_EVALUATOR_MultiTexture0);
        }
        return true;
    }

}
}
