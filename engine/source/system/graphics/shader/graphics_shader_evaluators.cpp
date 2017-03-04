#include "system/graphics/shader/graphics_shader_evaluators.h"
#include "system/graphics/graphics.h"

#define COFFEE_ScaleCandelaIntensities  100.0f

namespace coffee
{
namespace graphics
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_ImplementSingleton(ShaderEvaluators);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ShaderEvaluators::ShaderEvaluators()
    {
        COFFEE_CreateSingleton(ShaderEvaluators);

        for (int32 index=SHADER_EVALUATOR_FrameBufferInputSize ; index<SHADER_EVALUATOR_Count ; ++index)
        {
            _EvaluatorArray.AddItem(COFFEE_New(ShaderProperty, "evaluator",
                SHADER_EVALUATOR_GetType((SHADER_EVALUATOR)index)));
        }
    }

    //--------------------------------------------------------------------------------------------//

    ShaderEvaluators::~ShaderEvaluators()
    {
        COFFEE_DestroySingleton(ShaderEvaluators);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const ShaderProperty& ShaderEvaluators::GetEvaluator(
        const SHADER_EVALUATOR& evaluator) const
    {
        return *_EvaluatorArray[(int32)evaluator-(int32)SHADER_EVALUATOR_FrameBufferInputSize];
    }
    
    //--------------------------------------------------------------------------------------------//

    ShaderProperty& ShaderEvaluators::GetEvaluator(const SHADER_EVALUATOR& evaluator)
    {
        return *_EvaluatorArray[(int32)evaluator-(int32)SHADER_EVALUATOR_FrameBufferInputSize];
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ShaderEvaluators::Update()
    {
        for (uint32 index=0 ;
            index<SHADER_EVALUATOR_Count-(uint32)SHADER_EVALUATOR_FrameBufferInputSize ;
            ++index)
        {
            ShaderProperty* evaluator = _EvaluatorArray[index];
            real* valueReal = (real*)evaluator->GetValue().GetScalarObject();
            bool* valueBoolean = (bool*)evaluator->GetValue().GetScalarObject();
            int32* valueInteger = (int32*)evaluator->GetValue().GetScalarObject();
            basic::Vector2* valueVector2 = (basic::Vector2*)evaluator->GetValue().GetObject();
            basic::Vector3* valueVector3 = (basic::Vector3*)evaluator->GetValue().GetObject();
            basic::Color* valueColor = (basic::Color*)evaluator->GetValue().GetObject();
            basic::Matrix* valueMatrix = (basic::Matrix*)evaluator->GetValue().GetObject();

            switch((SHADER_EVALUATOR)index+SHADER_EVALUATOR_FrameBufferInputSize)
            {
                case SHADER_EVALUATOR_FrameBufferInputSize:
                {
                    // TODO: 8 input size evaluators...

                    valueVector2->Set(
                        (real) 0.0f,
                        (real) 0.0f);
                } break;

                case SHADER_EVALUATOR_FrameBufferSize:
                {
                    valueVector2->Set(
                        (real) graphics::Viewport::GetCurrent().GetFrameBufferSize().X,
                        (real) graphics::Viewport::GetCurrent().GetFrameBufferSize().Y);
                } break;

                case SHADER_EVALUATOR_MatrixWorldToLocal:
                {
                    *valueMatrix = Renderer::Get().GetWorldToLocalMatrix();
                } break;

                case SHADER_EVALUATOR_MatrixWorldToCamera:
                {
                    if (!graphics::Viewport::GetCurrent().HasCamera()) { valueMatrix->SetIdentity(); break; }
                    *valueMatrix = graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_World, scene::TRS_Local);
                } break;

                case SHADER_EVALUATOR_MatrixWorldToViewport:
                {
                    if (!graphics::Viewport::GetCurrent().HasCamera()) { valueMatrix->SetIdentity(); break; }
                    *valueMatrix = graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_World, scene::TRS_Local)
                        * graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetLocalToViewportMatrix();
                } break;

                case SHADER_EVALUATOR_MatrixWorldToFrame:
                {
                    if (!graphics::Viewport::GetCurrent().HasCamera()) { valueMatrix->SetIdentity(); break; }
                    *valueMatrix = graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_World, scene::TRS_Local)
                        * graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetLocalToViewportMatrix()
                        * graphics::Viewport::GetCurrent().GetViewportToFrameMatrix();
                } break;

                case SHADER_EVALUATOR_MatrixCameraToLocal:
                {   
                    if (!graphics::Viewport::GetCurrent().HasCamera()) { valueMatrix->SetIdentity(); break; }
                    *valueMatrix = graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World)
                        * Renderer::Get().GetWorldToLocalMatrix();
                } break;

                case SHADER_EVALUATOR_MatrixCameraToWorld:
                {
                    if (!graphics::Viewport::GetCurrent().HasCamera()) { valueMatrix->SetIdentity(); break; }
                    *valueMatrix = graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World);
                } break;

                case SHADER_EVALUATOR_MatrixCameraToViewport:
                {
                    if (!graphics::Viewport::GetCurrent().HasCamera()) { valueMatrix->SetIdentity(); break; }
                    *valueMatrix = graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetLocalToViewportMatrix();
                } break;

                case SHADER_EVALUATOR_MatrixCameraToFrame:
                {
                    if (!graphics::Viewport::GetCurrent().HasCamera()) { valueMatrix->SetIdentity(); break; }
                    *valueMatrix = graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetLocalToViewportMatrix()
                        * graphics::Viewport::GetCurrent().GetViewportToFrameMatrix();
                } break;

                case SHADER_EVALUATOR_MatrixViewportToLocal:
                {
                    if (!graphics::Viewport::GetCurrent().HasCamera()) { valueMatrix->SetIdentity(); break; }
                    *valueMatrix = graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetViewportToLocalMatrix()
                        * graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World)
                        * Renderer::Get().GetWorldToLocalMatrix();
                } break;

                case SHADER_EVALUATOR_MatrixViewportToWorld:
                {
                    if (!graphics::Viewport::GetCurrent().HasCamera()) { valueMatrix->SetIdentity(); break; }
                    *valueMatrix = graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetViewportToLocalMatrix()
                        * graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World);
                } break;

                case SHADER_EVALUATOR_MatrixViewportToCamera:
                {
                    if (!graphics::Viewport::GetCurrent().HasCamera()) { valueMatrix->SetIdentity(); break; }
                    *valueMatrix = graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetViewportToLocalMatrix();
                } break;

                case SHADER_EVALUATOR_MatrixViewportToFrame:
                {
                    *valueMatrix = graphics::Viewport::GetCurrent().GetViewportToFrameMatrix();
                } break;

                case SHADER_EVALUATOR_MatrixFrameToLocal:
                {
                    if (!graphics::Viewport::GetCurrent().HasCamera()) { valueMatrix->SetIdentity(); break; }
                    *valueMatrix = graphics::Viewport::GetCurrent().GetFrameToViewportMatrix()
                        * graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetViewportToLocalMatrix()
                        * graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World)
                        * Renderer::Get().GetWorldToLocalMatrix();
                } break;

                case SHADER_EVALUATOR_MatrixFrameToWorld:
                {
                    if (!graphics::Viewport::GetCurrent().HasCamera()) { valueMatrix->SetIdentity(); break; }
                    *valueMatrix = graphics::Viewport::GetCurrent().GetFrameToViewportMatrix()
                        * graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetViewportToLocalMatrix()
                        * graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World);
                } break;

                case SHADER_EVALUATOR_MatrixFrameToCamera:
                {
                    if (!graphics::Viewport::GetCurrent().HasCamera()) { valueMatrix->SetIdentity(); break; }
                    *valueMatrix = graphics::Viewport::GetCurrent().GetFrameToViewportMatrix()
                        * graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetViewportToLocalMatrix();
                } break;

                case SHADER_EVALUATOR_MatrixFrameToViewport:
                {
                    *valueMatrix = graphics::Viewport::GetCurrent().GetFrameToViewportMatrix();
                } break;

                case SHADER_EVALUATOR_MatrixLocalToWorld:
                {
                    *valueMatrix = Renderer::Get().GetLocalToWorldMatrix();
                } break;

                case SHADER_EVALUATOR_MatrixLocalToCamera:
                {
                    if (!graphics::Viewport::GetCurrent().HasCamera()) { valueMatrix->SetIdentity(); break; }
                    *valueMatrix = Renderer::Get().GetLocalToWorldMatrix()
                        * graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_World, scene::TRS_Local);
                } break;

                case SHADER_EVALUATOR_MatrixLocalToViewport:
                {
                    if (!graphics::Viewport::GetCurrent().HasCamera()) { valueMatrix->SetIdentity(); break; }
                    *valueMatrix = Renderer::Get().GetLocalToWorldMatrix()
                        * graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_World, scene::TRS_Local)
                        * graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetLocalToViewportMatrix();
                } break;

                case SHADER_EVALUATOR_MatrixLocalToFrame:
                {
                    if (!graphics::Viewport::GetCurrent().HasCamera()) { valueMatrix->SetIdentity(); break; }
                    *valueMatrix = Renderer::Get().GetLocalToWorldMatrix()
                        * graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_World, scene::TRS_Local)
                        * graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetLocalToViewportMatrix()
                        * graphics::Viewport::GetCurrent().GetViewportToFrameMatrix();
                } break;

                case SHADER_EVALUATOR_MatrixCameraToLight:
                {
                    if (Renderer::Get().HasCurrentLight())
                    {
                        *valueMatrix = graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World)
                            * Renderer::Get().GetCurrentLight().GetNode().GetTransform().GetMatrix(scene::TRS_World, scene::TRS_Local);
                    }
                } break;

                case SHADER_EVALUATOR_Picker:
                    break;

                case SHADER_EVALUATOR_Time:
                {
                    *valueReal = Module::Get().GetTime().GetSecondCount();
                } break;

                case SHADER_EVALUATOR_Brightness:
                {
                    *valueReal = Device::Get().GetConfig().GetBrightness()-1.0f;
                } break;

                case SHADER_EVALUATOR_Contrast:
                {
                    *valueReal = Device::Get().GetConfig().GetContrast();
                } break;

                case SHADER_EVALUATOR_Gamma:
                {
                    if (!IsEqual(Device::Get().GetConfig().GetGamma(), 0.0f))
                        *valueReal = 1.0f/Device::Get().GetConfig().GetGamma();
                } break;

                case SHADER_EVALUATOR_Exposure:
                {
                    if (graphics::Viewport::HasCurrent() && graphics::Viewport::GetCurrent().HasCamera())
                        *valueReal = graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetExposure();
                } break;

                case SHADER_EVALUATOR_LightPosition:
                {
                    if (Renderer::Get().HasCurrentLight())
                    {
                        if (Renderer::Get().GetCurrentLight().IsA<ComponentLightDirectional>())
                        {
                            basic::Vector3 res = -(Renderer::Get().GetCurrentLight().GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World)
                                * graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_World, scene::TRS_Local)).GetZAxis();
                            *valueColor = basic::Color(res.X, res.Y, res.Z, 0.0f);
                        }
                        else
                        {
                            basic::Vector3 res = Renderer::Get().GetCurrentLight().GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetTranslation()
                                * graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_World, scene::TRS_Local);
                            *valueColor = basic::Color(res.X, res.Y, res.Z, 1.0f);
                        }
                    }
                } break;

                case SHADER_EVALUATOR_LightIntensity:
                {
                    if (Renderer::Get().HasCurrentLight())
                        *valueReal = Renderer::Get().GetCurrentLight().GetIntensity()/COFFEE_ScaleCandelaIntensities;
                } break;

                case SHADER_EVALUATOR_LightSoftness:
                {
                    if (Renderer::Get().HasCurrentLight())
                        *valueReal = Renderer::Get().GetCurrentLight().GetSoftness();
                } break;  

                case SHADER_EVALUATOR_LightRadius:
                {
                    if (Renderer::Get().HasCurrentLight())
                        *valueReal = Renderer::Get().GetCurrentLight().GetRadius();
                            //* Renderer::Get().GetCurrentLight().GetRadiusMultiplier();
                } break;

                case SHADER_EVALUATOR_LightApex:
                {
                    if (Renderer::Get().HasCurrentLight())
                        *valueReal = Renderer::Get().GetCurrentLight().GetApex();
                } break;

                case SHADER_EVALUATOR_LightZAxis:
                {
                    if (Renderer::Get().HasCurrentLight())
                    {
                        *valueVector3 = -(Renderer::Get().GetCurrentLight().GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World)
                            * graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_World, scene::TRS_Local)).GetZAxis();
                    }
                } break;

                case SHADER_EVALUATOR_LightColor:
                {
                    if (Renderer::Get().HasCurrentLight())
                        *valueColor = Renderer::Get().GetCurrentLight().GetColor();
                } break;

                case SHADER_EVALUATOR_ShadowDepthPass:
                {
                    *valueInteger = FramePassSystem::Get().GetLightningPass().GetShadowDepthPass();
                } break;

                case SHADER_EVALUATOR_EyeAdaptation:
                {
                    if (graphics::Viewport::HasCurrent() && graphics::Viewport::GetCurrent().HasCamera())
                        *valueReal = graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetEyeAdaptation();
                } break;

                case SHADER_EVALUATOR_EyeBrightAdaptation:
                {
                    if (graphics::Viewport::HasCurrent() && graphics::Viewport::GetCurrent().HasCamera())
                        *valueReal = graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetBrightAdaptationTime();
                } break;

                case SHADER_EVALUATOR_EyeDarkAdaptation:
                {
                    if (graphics::Viewport::HasCurrent() && graphics::Viewport::GetCurrent().HasCamera())
                        *valueReal = graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetDarkAdaptationTime();
                } break;

                case SHADER_EVALUATOR_EyeAdaptationTime:
                {
                    *valueReal = graphics::FramePassSystem::Get().GetToneMappingPass().GetAdaptationTime();
                } break;

                case SHADER_EVALUATOR_CameraNearClip:
                {
                    if (!graphics::Viewport::GetCurrent().HasCamera()) { *valueReal = 0.0f; break; }
                    *valueReal = graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetNearClip();
                } break;

                case SHADER_EVALUATOR_CameraFarClip:
                {
                    if (!graphics::Viewport::GetCurrent().HasCamera()) { *valueReal = 0.0f; break; }
                    *valueReal = graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetFarClip();
                } break;

                case SHADER_EVALUATOR_SkyIntensity:
                {
                    *valueReal = 1.0f;
                    if (graphics::Viewport::GetCurrent().HasCamera())
                    {
                        ComponentSky* sky = graphics::Viewport::GetCurrent().GetCamera().GetScene().Get().GetRoot().FindComponent<ComponentSky>();
                        if (sky!=NULL)
                            *valueReal = sky->GetSky().GetIntensity()/COFFEE_ScaleCandelaIntensities;
                    }
                } break;
            }
        }
    }

}
}

#undef COFFEE_ScaleCandelaIntensities
