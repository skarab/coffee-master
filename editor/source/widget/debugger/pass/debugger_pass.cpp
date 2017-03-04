#include "widget/debugger/pass/debugger_pass.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(widget::DebuggerPass);
        COFFEE_Ancestor(graphics::FramePass);
    COFFEE_EndType();

namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    DebuggerPass::DebuggerPass() :
        graphics::FramePass("Debugger"),
        _PassType(DEBUGGER_PASS_TYPE_None)
    {
    }

    //--------------------------------------------------------------------------------------------//

    DebuggerPass::~DebuggerPass()
    {
        SetPassType(DEBUGGER_PASS_TYPE_None);
    }

    //--------------------------------------------------------------------------------------------//

    void DebuggerPass::SetPassType(DEBUGGER_PASS_TYPE type)
    {
        graphics::FramePassSystem& system = graphics::FramePassSystem::Get();
        if (_PassType!=DEBUGGER_PASS_TYPE_None)
        {
            system.GetPasses()[system.GetPasses().GetSize()-1] = NULL;
            system.GetPasses().Remove(system.GetPasses().GetSize()-1);
            Finalize(NULL);
        }

        _PassType = type;

        if (_PassType!=DEBUGGER_PASS_TYPE_None)
        {
            system.GetPasses().AddItem(this);
            Initialize(NULL);
        }
    }
        
    //-OPERATIONS---------------------------------------------------------------------------------//

    void DebuggerPass::Initialize(graphics::FramePass* previous_pass)
    {
        _Layer = COFFEE_New(graphics::FrameLayerBGRA, GetFrameBuffer().GetWidth(), GetFrameBuffer().GetHeight(), false);
        GetFrameBuffer().AttachLayer(*_Layer);

        switch (_PassType)
        {
            case DEBUGGER_PASS_TYPE_Depth:
                _Material = resource::Manager::Get().Load("/coffee/import/editor/debugger/debug_layer_depth.material");
                break;

            case DEBUGGER_PASS_TYPE_LinearDepth:
                _Material = resource::Manager::Get().Load("/coffee/import/editor/debugger/debug_layer_linear_depth.material");
                break;

            case DEBUGGER_PASS_TYPE_Normal:
                _Material = resource::Manager::Get().Load("/coffee/import/editor/debugger/debug_layer_normal.material");
                break;

            case DEBUGGER_PASS_TYPE_Color:
            case DEBUGGER_PASS_TYPE_Material:
                _Material = resource::Manager::Get().Load("/coffee/import/editor/debugger/debug_layer_rgb8.material");
                break;

            case DEBUGGER_PASS_TYPE_Lightning:
                _Material = resource::Manager::Get().Load("/coffee/import/editor/debugger/debug_layer_lightning.material");
                break;

            case DEBUGGER_PASS_TYPE_DetectNAN:
                _Material = resource::Manager::Get().Load("/coffee/import/editor/debugger/debug_detect_nan.material");
                break;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void DebuggerPass::Finalize(graphics::FramePass* previous_pass)
    {
        GetFrameBuffer().DetachLayer(*_Layer);
        COFFEE_Delete(_Layer);
    }

    //--------------------------------------------------------------------------------------------//
    
    void DebuggerPass::Render(graphics::Viewport& viewport, graphics::FramePass* previous_pass)
    {
        if (viewport.HasCamera() && _Material.IsAvailable())
        {
            graphics::FramePassSystem& system = graphics::FramePassSystem::Get();
        
            switch(_PassType)
            {
                case DEBUGGER_PASS_TYPE_Depth: system.GetGBufferPass().GetDepth().Bind(0); break;
                case DEBUGGER_PASS_TYPE_LinearDepth: system.GetGBufferPass().GetLinearDepth().Bind(0); break;
                case DEBUGGER_PASS_TYPE_Normal: system.GetGBufferPass().GetNormal().Bind(0); break;
                case DEBUGGER_PASS_TYPE_Color: system.GetGBufferPass().GetColor().Bind(0); break;
                case DEBUGGER_PASS_TYPE_Material: system.GetGBufferPass().GetMaterial().Bind(0); break;
                case DEBUGGER_PASS_TYPE_Lightning: system.GetLightningPass().GetFrameBuffer().GetLayer(0).Bind(0); break;
                case DEBUGGER_PASS_TYPE_DetectNAN: system.GetSkyPass().GetFrameBuffer().GetLayer(0).Bind(0); break;
            }

            _Material.Bind();
            RenderQuad(viewport);
            _Material.UnBind();

            switch(_PassType)
            {
                case DEBUGGER_PASS_TYPE_Depth: system.GetGBufferPass().GetDepth().UnBind(0); break;
                case DEBUGGER_PASS_TYPE_LinearDepth: system.GetGBufferPass().GetLinearDepth().UnBind(0); break;
                case DEBUGGER_PASS_TYPE_Normal: system.GetGBufferPass().GetNormal().UnBind(0); break;
                case DEBUGGER_PASS_TYPE_Color: system.GetGBufferPass().GetColor().UnBind(0); break;
                case DEBUGGER_PASS_TYPE_Material: system.GetGBufferPass().GetMaterial().UnBind(0); break;
                case DEBUGGER_PASS_TYPE_Lightning: system.GetLightningPass().GetFrameBuffer().GetLayer(0).UnBind(0); break;
                case DEBUGGER_PASS_TYPE_DetectNAN: system.GetSkyPass().GetFrameBuffer().GetLayer(0).UnBind(0); break;
            }
        }
        else
        {
            graphics::Renderer::Get().ClearColor();
        }
     }

}
}
