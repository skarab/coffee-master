#ifndef _COFFEE_GRAPHICS_SHADER_EVALUATOR_H_
#define _COFFEE_GRAPHICS_SHADER_EVALUATOR_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_enum.h"
#include "kernel/basic/basic.h"
#include "system/graphics/shader/graphics_shader_property_type.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// @enum SHADER_EVALUATOR
    /// @brief Shader evaluator
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::graphics, SHADER_EVALUATOR, "Evaluator", Single)
        COFFEE_EnumValue(SHADER_EVALUATOR, Disabled, 0)
        COFFEE_EnumValue(SHADER_EVALUATOR, Custom, 1)
        COFFEE_EnumValue(SHADER_EVALUATOR, MultiTexture0, 2)
        COFFEE_EnumValue(SHADER_EVALUATOR, MultiTexture1, 3)
        COFFEE_EnumValue(SHADER_EVALUATOR, MultiTexture2, 4)
        COFFEE_EnumValue(SHADER_EVALUATOR, MultiTexture3, 5)
        COFFEE_EnumValue(SHADER_EVALUATOR, MultiTexture4, 6)
        COFFEE_EnumValue(SHADER_EVALUATOR, MultiTexture5, 7)
        COFFEE_EnumValue(SHADER_EVALUATOR, MultiTexture6, 8)
        COFFEE_EnumValue(SHADER_EVALUATOR, MultiTexture7, 9)
        COFFEE_EnumValue(SHADER_EVALUATOR, FrameBufferInputSize, 10)
        COFFEE_EnumValue(SHADER_EVALUATOR, FrameBufferSize, 11)
        COFFEE_EnumValue(SHADER_EVALUATOR, MatrixWorldToLocal, 12)
        COFFEE_EnumValue(SHADER_EVALUATOR, MatrixWorldToCamera, 13)
        COFFEE_EnumValue(SHADER_EVALUATOR, MatrixWorldToViewport, 14)
        COFFEE_EnumValue(SHADER_EVALUATOR, MatrixWorldToFrame, 15)
        COFFEE_EnumValue(SHADER_EVALUATOR, MatrixCameraToLocal, 16)
        COFFEE_EnumValue(SHADER_EVALUATOR, MatrixCameraToWorld, 17)
        COFFEE_EnumValue(SHADER_EVALUATOR, MatrixCameraToViewport, 18)
        COFFEE_EnumValue(SHADER_EVALUATOR, MatrixCameraToFrame, 19)
        COFFEE_EnumValue(SHADER_EVALUATOR, MatrixViewportToLocal, 20)
        COFFEE_EnumValue(SHADER_EVALUATOR, MatrixViewportToWorld, 21)
        COFFEE_EnumValue(SHADER_EVALUATOR, MatrixViewportToCamera, 22)
        COFFEE_EnumValue(SHADER_EVALUATOR, MatrixViewportToFrame, 23)
        COFFEE_EnumValue(SHADER_EVALUATOR, MatrixFrameToLocal, 24)
        COFFEE_EnumValue(SHADER_EVALUATOR, MatrixFrameToWorld, 25)
        COFFEE_EnumValue(SHADER_EVALUATOR, MatrixFrameToCamera, 26)
        COFFEE_EnumValue(SHADER_EVALUATOR, MatrixFrameToViewport, 27)
        COFFEE_EnumValue(SHADER_EVALUATOR, MatrixLocalToWorld, 28)
        COFFEE_EnumValue(SHADER_EVALUATOR, MatrixLocalToCamera, 29)
        COFFEE_EnumValue(SHADER_EVALUATOR, MatrixLocalToViewport, 30)
        COFFEE_EnumValue(SHADER_EVALUATOR, MatrixLocalToFrame, 31)
        COFFEE_EnumValue(SHADER_EVALUATOR, MatrixCameraToLight, 32)
        COFFEE_EnumValue(SHADER_EVALUATOR, Picker, 33)
        COFFEE_EnumValue(SHADER_EVALUATOR, Time, 34)
        COFFEE_EnumValue(SHADER_EVALUATOR, Brightness, 35)
        COFFEE_EnumValue(SHADER_EVALUATOR, Contrast, 36)
        COFFEE_EnumValue(SHADER_EVALUATOR, Gamma, 37)
        COFFEE_EnumValue(SHADER_EVALUATOR, Exposure, 38)
        COFFEE_EnumValue(SHADER_EVALUATOR, LightPosition, 39)
        COFFEE_EnumValue(SHADER_EVALUATOR, LightIntensity, 40)
        COFFEE_EnumValue(SHADER_EVALUATOR, LightSoftness, 41)
        COFFEE_EnumValue(SHADER_EVALUATOR, LightRadius, 42)
        COFFEE_EnumValue(SHADER_EVALUATOR, LightApex, 43)
        COFFEE_EnumValue(SHADER_EVALUATOR, LightZAxis, 44)
        COFFEE_EnumValue(SHADER_EVALUATOR, LightColor, 45)
        COFFEE_EnumValue(SHADER_EVALUATOR, ShadowDepthPass, 46)
        COFFEE_EnumValue(SHADER_EVALUATOR, EyeAdaptation, 47)
        COFFEE_EnumValue(SHADER_EVALUATOR, EyeBrightAdaptation, 48)
        COFFEE_EnumValue(SHADER_EVALUATOR, EyeDarkAdaptation, 49)
        COFFEE_EnumValue(SHADER_EVALUATOR, EyeAdaptationTime, 50)
        COFFEE_EnumValue(SHADER_EVALUATOR, CameraNearClip, 51)
        COFFEE_EnumValue(SHADER_EVALUATOR, CameraFarClip, 52)
        COFFEE_EnumValue(SHADER_EVALUATOR, SkyIntensity, 53)
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, SHADER_EVALUATOR)

    /// Retrieve property type from evaluator type
    COFFEE_API SHADER_PROPERTY_TYPE SHADER_EVALUATOR_GetType(const SHADER_EVALUATOR& evaluator);
}
}
#endif
