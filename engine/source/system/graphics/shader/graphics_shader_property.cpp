#include "system/graphics/shader/graphics_shader_property.h"
#include "system/graphics/shader/graphics_shader_evaluators.h"
#include "system/graphics/texture/graphics_texture.h"

#define COFFEE_NULL_TEXTURE "/coffee/import/textures/null.texture"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::ShaderProperty);
        COFFEE_Attribute(graphics::SHADER_PROPERTY_TYPE, _Type, meta::MODE_Serializeable);
        COFFEE_Attribute(basic::PropertyBase*, _Value, meta::MODE_Serializeable);
        COFFEE_Attribute(graphics::SHADER_EVALUATOR, _Evaluator, meta::MODE_Serializeable);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ShaderProperty::ShaderProperty() :
        _Type(SHADER_PROPERTY_TYPE_None),
        _Value(NULL),
        _Evaluator(SHADER_EVALUATOR_Disabled),
        _Identifier(NONE)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ShaderProperty::ShaderProperty(const ShaderProperty& property)
    {
        this->operator =(property);
    }
        
    //--------------------------------------------------------------------------------------------//

    ShaderProperty::ShaderProperty(basic::String name, const SHADER_PROPERTY_TYPE& type) :
        _Type(type),
        _Evaluator(SHADER_EVALUATOR_Disabled),
        _Identifier(NONE)
    {
        _Value = COFFEE_New(basic::PropertyBase, 
            name, COFFEE_FindType(SHADER_PROPERTY_TYPE_GetTypeName(type)));

        if (type==SHADER_PROPERTY_TYPE_Texture)
        {
            *static_cast<Texture*>(_Value->GetObject()) = resource::Manager::Get().Load(
                storage::Path(COFFEE_NULL_TEXTURE));
        }
    }

    //--------------------------------------------------------------------------------------------//

    ShaderProperty::~ShaderProperty()
    {
        if (_Value!=NULL)
            COFFEE_Delete(_Value);
    }

    //-OPERATORS------------------------------------------------------------------------------//

    ShaderProperty& ShaderProperty::operator=(const ShaderProperty& property)
    {
        _Type = property._Type;
        _Evaluator = property._Evaluator;
        _Identifier = property._Identifier;
        _Value = COFFEE_New(basic::PropertyBase, 
            property.GetName(), COFFEE_FindType(SHADER_PROPERTY_TYPE_GetTypeName(_Type)));

        switch(_Type)
        {
            case SHADER_PROPERTY_TYPE_Texture:
                *static_cast<Texture*>(_Value->GetObject()) = *static_cast<Texture*>(property._Value->GetObject());
                break;
            case SHADER_PROPERTY_TYPE_Real:
                *reinterpret_cast<real*>(_Value->GetScalarObject()) = *reinterpret_cast<real*>(property._Value->GetScalarObject());
                break;
            case SHADER_PROPERTY_TYPE_Boolean:
                *reinterpret_cast<bool*>(_Value->GetScalarObject()) = *reinterpret_cast<bool*>(property._Value->GetScalarObject());
                break;
            case SHADER_PROPERTY_TYPE_Integer:
                *reinterpret_cast<int32*>(_Value->GetScalarObject()) = *reinterpret_cast<int32*>(property._Value->GetScalarObject());
                break;
            case SHADER_PROPERTY_TYPE_Vector2:
                *static_cast<basic::Vector2*>(_Value->GetObject()) = *static_cast<basic::Vector2*>(property._Value->GetObject());
                break;
            case SHADER_PROPERTY_TYPE_Vector3:
                *static_cast<basic::Vector3*>(_Value->GetObject()) = *static_cast<basic::Vector3*>(property._Value->GetObject());
                break;
            case SHADER_PROPERTY_TYPE_Color:
                *static_cast<basic::Color*>(_Value->GetObject()) = *static_cast<basic::Color*>(property._Value->GetObject());
                break;
            case SHADER_PROPERTY_TYPE_Matrix4x4:
                *static_cast<basic::Matrix*>(_Value->GetObject()) = *static_cast<basic::Matrix*>(property._Value->GetObject());
                break;
        }

        return *this;
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const basic::String& ShaderProperty::GetName() const
    {
        return _Value->GetName();
    }

    //--------------------------------------------------------------------------------------------//

    const SHADER_PROPERTY_TYPE& ShaderProperty::GetType() const
    {
        return _Type;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::PropertyBase& ShaderProperty::GetValue() const
    {
        if ((uint32)_Evaluator>=(uint32)SHADER_EVALUATOR_FrameBufferInputSize)
        {
            return ShaderEvaluators::Get().GetEvaluator(_Evaluator).GetValue();
        }

        return *_Value;
    }

    //--------------------------------------------------------------------------------------------//

    basic::PropertyBase& ShaderProperty::GetValue()
    {
        if ((uint32)_Evaluator>=(uint32)SHADER_EVALUATOR_FrameBufferInputSize
            && (uint32)_Evaluator<(uint32)SHADER_EVALUATOR_Count)
        {
            return ShaderEvaluators::Get().GetEvaluator(_Evaluator).GetValue();
        }
        return *_Value;
    }

    //--------------------------------------------------------------------------------------------//

    void ShaderProperty::SetEvaluator(const SHADER_EVALUATOR& evaluator)
    {
        _Evaluator = evaluator;
    }

    //--------------------------------------------------------------------------------------------//

    const SHADER_EVALUATOR& ShaderProperty::GetEvaluator() const
    {
        return _Evaluator;
    }

    //--------------------------------------------------------------------------------------------//

    void ShaderProperty::SetIdentifier(uint32 identifier)
    {
        _Identifier = identifier;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 ShaderProperty::GetIdentifier() const
    {
        return _Identifier;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool ShaderProperty::IsEnabled() const
    {
        return _Evaluator!=SHADER_EVALUATOR_Disabled;
    }

    //--------------------------------------------------------------------------------------------//

    bool ShaderProperty::HasToBindTexture() const
    {
        return _Type==SHADER_PROPERTY_TYPE_Texture
            && static_cast<Texture*>(_Value->GetObject())->GetFilePath()!=COFFEE_NULL_TEXTURE;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ShaderProperty::Create()
    {
        basic::String name;

        if (_Value!=NULL)
        {
            name = _Value->GetName();
            COFFEE_Delete(_Value);
        }

        _Value = COFFEE_New(basic::PropertyBase, 
            name, COFFEE_FindType(SHADER_PROPERTY_TYPE_GetTypeName(GetType())));

        if (GetType()==SHADER_PROPERTY_TYPE_Texture)
        {
            *static_cast<Texture*>(_Value->GetObject()) = resource::Manager::Get().Load(
                storage::Path(COFFEE_NULL_TEXTURE));
        }
    }

}
}

#undef COFFEE_NULL_TEXTURE
