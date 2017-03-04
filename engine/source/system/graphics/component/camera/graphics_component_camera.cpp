#include "system/graphics/component/camera/graphics_component_camera.h"
#include "system/scene/node/scene_node.h"
#include "system/graphics/viewport/graphics_viewport.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::ComponentCamera);
        COFFEE_Ancestor(graphics::Component);
        COFFEE_Attribute(real, _NearClip, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, _FarClip, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(graphics::Material, _ToneMapper, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, _Exposure, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, _EyeAdaptation, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, _BrightAdaptationTime, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, _DarkAdaptationTime, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ComponentCamera::ComponentCamera() :
        _Viewport(NULL),
        _NearClip(0.01f),
        _FarClip(2000.0f),
        _Exposure(1.0f),        
        _EyeAdaptation(1.0f),
        _BrightAdaptationTime(1.0f),
        _DarkAdaptationTime(2.0f)
    {
        EnableFlag(COMPONENT_FLAG_CastShadows, true);
    }

    //--------------------------------------------------------------------------------------------//

    ComponentCamera::~ComponentCamera()
    {
        COFFEE_Assert(_Viewport==NULL, core::ERROR_CODE_Unexpected, "Unexpected error");
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    basic::Matrix ComponentCamera::GetViewportToLocalMatrix() const
    {
        basic::Matrix viewport_to_local(_LocalToViewportMatrix);
        viewport_to_local.Invert();
        return viewport_to_local;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//
    
    void ComponentCamera::OnStart()
    {
        if (GetToneMapper().GetFilePath().IsEmpty())
        {
            SetToneMapper(resource::Manager::Get().Load(
                storage::Path("/coffee/import/shaders/tonemap/linear.material")));
        }
    }

    //--------------------------------------------------------------------------------------------//

    void ComponentCamera::OnStop()
    {
        if (_Viewport!=NULL)
            _Viewport->DetachCamera();
    }

}
}
