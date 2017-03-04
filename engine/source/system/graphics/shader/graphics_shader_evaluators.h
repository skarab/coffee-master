#ifndef _COFFEE_GRAPHICS_SHADER_EVALUATORS_H_
#define _COFFEE_GRAPHICS_SHADER_EVALUATORS_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "system/graphics/shader/graphics_shader_property.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Shader evaluators
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ShaderEvaluators
    {
        COFFEE_DeclareSingleton(ShaderEvaluators);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ShaderEvaluators();
        ~ShaderEvaluators();

        //-ACCESSORS------------------------------------------------------------------------------//

        const ShaderProperty& GetEvaluator(const SHADER_EVALUATOR& evaluator) const;
        ShaderProperty& GetEvaluator(const SHADER_EVALUATOR& evaluator);

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Update();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Prow< ShaderProperty*, true > _EvaluatorArray;
    };
}
}
#endif
