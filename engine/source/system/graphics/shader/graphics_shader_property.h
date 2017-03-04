#ifndef _COFFEE_GRAPHICS_SHADER_PROPERTY_H_
#define _COFFEE_GRAPHICS_SHADER_PROPERTY_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "kernel/resource/resources.h"
#include "system/graphics/shader/graphics_shader_property_type.h"
#include "system/graphics/shader/graphics_shader_evaluator.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Material property
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ShaderProperty : public meta::Object
    {
        COFFEE_Type(ShaderProperty);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ShaderProperty();
        ShaderProperty(const ShaderProperty& property);
        ShaderProperty(basic::String name, const SHADER_PROPERTY_TYPE& type);
        virtual ~ShaderProperty();

        //-OPERATORS------------------------------------------------------------------------------//

        ShaderProperty& operator=(const ShaderProperty& property);

        //-ACCESSORS------------------------------------------------------------------------------//

        const basic::String& GetName() const;
        const SHADER_PROPERTY_TYPE& GetType() const;
        const basic::PropertyBase& GetValue() const;
        basic::PropertyBase& GetValue();
        void SetEvaluator(const SHADER_EVALUATOR& evaluator);
        const SHADER_EVALUATOR& GetEvaluator() const;
        void SetIdentifier(uint32 identifier);
        uint32 GetIdentifier() const;

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsEnabled() const;
        bool HasToBindTexture() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create();
       
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        SHADER_PROPERTY_TYPE _Type;
        basic::PropertyBase* _Value;
        SHADER_EVALUATOR _Evaluator;
        uint32 _Identifier;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ShaderProperty);
}
}
#endif
