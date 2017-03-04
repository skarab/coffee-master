#include "system/graphics/shader/graphics_shader_evaluator.h"
#undef _COFFEE_GRAPHICS_SHADER_EVALUATOR_H_
#include "kernel/meta/macros/meta_macros_enum_cpp.h"
#include "system/graphics/shader/graphics_shader_evaluator.h"
#include "kernel/meta/macros/meta_macros_enum_h.h"

namespace coffee
{
namespace graphics
{
    //-FUNCTIONS----------------------------------------------------------------------------------//

    SHADER_PROPERTY_TYPE SHADER_EVALUATOR_GetType(const SHADER_EVALUATOR& evaluator)
    {
        switch (evaluator)
        {
            case SHADER_EVALUATOR_MultiTexture0:
            case SHADER_EVALUATOR_MultiTexture1:
            case SHADER_EVALUATOR_MultiTexture2:
            case SHADER_EVALUATOR_MultiTexture3:
            case SHADER_EVALUATOR_MultiTexture4:
            case SHADER_EVALUATOR_MultiTexture5:
            case SHADER_EVALUATOR_MultiTexture6:
            case SHADER_EVALUATOR_MultiTexture7:
                 return SHADER_PROPERTY_TYPE_Texture;

            case SHADER_EVALUATOR_FrameBufferInputSize:
            case SHADER_EVALUATOR_FrameBufferSize:
                return SHADER_PROPERTY_TYPE_Vector2;

            case SHADER_EVALUATOR_MatrixWorldToLocal:
            case SHADER_EVALUATOR_MatrixWorldToCamera:
            case SHADER_EVALUATOR_MatrixWorldToViewport:
            case SHADER_EVALUATOR_MatrixWorldToFrame:
            case SHADER_EVALUATOR_MatrixCameraToLocal:
            case SHADER_EVALUATOR_MatrixCameraToWorld:
            case SHADER_EVALUATOR_MatrixCameraToViewport:
            case SHADER_EVALUATOR_MatrixCameraToFrame:
            case SHADER_EVALUATOR_MatrixViewportToLocal:
            case SHADER_EVALUATOR_MatrixViewportToWorld:
            case SHADER_EVALUATOR_MatrixViewportToCamera:
            case SHADER_EVALUATOR_MatrixViewportToFrame:
            case SHADER_EVALUATOR_MatrixFrameToLocal:
            case SHADER_EVALUATOR_MatrixFrameToWorld:
            case SHADER_EVALUATOR_MatrixFrameToCamera:
            case SHADER_EVALUATOR_MatrixFrameToViewport:
            case SHADER_EVALUATOR_MatrixLocalToWorld:
            case SHADER_EVALUATOR_MatrixLocalToCamera:
            case SHADER_EVALUATOR_MatrixLocalToViewport:
            case SHADER_EVALUATOR_MatrixLocalToFrame:
            case SHADER_EVALUATOR_MatrixCameraToLight:
                return SHADER_PROPERTY_TYPE_Matrix4x4;

            case SHADER_EVALUATOR_Picker:
                return SHADER_PROPERTY_TYPE_Color;
            case SHADER_EVALUATOR_Time:
                return SHADER_PROPERTY_TYPE_Real;
            case SHADER_EVALUATOR_Brightness:
            case SHADER_EVALUATOR_Contrast:
            case SHADER_EVALUATOR_Gamma:
            case SHADER_EVALUATOR_Exposure:
                return SHADER_PROPERTY_TYPE_Real;

            case SHADER_EVALUATOR_LightPosition:
                return SHADER_PROPERTY_TYPE_Color;                
            case SHADER_EVALUATOR_LightIntensity:
            case SHADER_EVALUATOR_LightSoftness:
            case SHADER_EVALUATOR_LightRadius:
            case SHADER_EVALUATOR_LightApex:
                return SHADER_PROPERTY_TYPE_Real;
            case SHADER_EVALUATOR_LightZAxis:
                return SHADER_PROPERTY_TYPE_Vector3;
            case SHADER_EVALUATOR_LightColor:
                return SHADER_PROPERTY_TYPE_Color;                
            
            case SHADER_EVALUATOR_ShadowDepthPass:
                return SHADER_PROPERTY_TYPE_Integer;

            case SHADER_EVALUATOR_EyeAdaptation:
            case SHADER_EVALUATOR_EyeBrightAdaptation:
            case SHADER_EVALUATOR_EyeDarkAdaptation:
                return SHADER_PROPERTY_TYPE_Real;
        
            case SHADER_EVALUATOR_EyeAdaptationTime:
                return SHADER_PROPERTY_TYPE_Real;

            case SHADER_EVALUATOR_CameraNearClip:
            case SHADER_EVALUATOR_CameraFarClip:
                return SHADER_PROPERTY_TYPE_Real;

            case SHADER_EVALUATOR_SkyIntensity:
                return SHADER_PROPERTY_TYPE_Real;
        }
        return SHADER_PROPERTY_TYPE_None;
    }

}
}
