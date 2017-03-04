#include "system/graphics/component/camera/graphics_component_camera_perspective.h"
#include "system/graphics/device/graphics_device.h"
#include "system/graphics/viewport/graphics_viewport.h"
#include "system/scene/node/scene_node.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::ComponentCameraPerspective);
        COFFEE_Ancestor(graphics::ComponentCamera);
        COFFEE_Attribute(real, _FieldOfView, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ComponentCameraPerspective::ComponentCameraPerspective() :
        _FieldOfView(70.0f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ComponentCameraPerspective::~ComponentCameraPerspective()
    {
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void ComponentCameraPerspective::Update(Viewport& viewport)
    {
        _UpdateProjectionMatrix(viewport);

        _Frustum.Set(
            GetNode().GetTransform().GetMatrix(scene::TRS_World, scene::TRS_Local),
            _LocalToViewportMatrix);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ComponentCameraPerspective::_UpdateProjectionMatrix(Viewport& viewport)
    {
        basic::Angle fov;
        fov.SetDegrees(_FieldOfView);
        
        // Balance for the non-uniform resizing which may occurs when blitting framebuffers
        real framebuffer_format = viewport.GetFrameBufferSize().X/(real)viewport.GetFrameBufferSize().Y;
        real window_format = viewport.GetSize().X/(real)viewport.GetSize().Y;
        real resize_ar = window_format/framebuffer_format;

        real viewport_aspect_ratio = (viewport.GetFrameBufferSize().X
            / (real)viewport.GetFrameBufferSize().Y)
            * resize_ar / Device::Get().GetAspectRatio();

        real* data = _LocalToViewportMatrix.GetData();
        real* infinite_data = _InfiniteProjectionMatrix.GetData();
        real thetaY(fov.Get()/2.0f);
        real tanThetaY = tan(thetaY);
        real w = (1.0f/tanThetaY)/viewport_aspect_ratio;
        real h = 1.0f/tanThetaY;
        
        real q = _FarClip/(_FarClip-_NearClip);
        data[0 ] = w;
        data[5 ] = h;
        data[10] = q;
        data[14] = -q*_NearClip;
        data[11] = 1.0f;
        data[15] = 0.0f;

        infinite_data[0 ] = w;
        infinite_data[5 ] = h;
        infinite_data[10] = 1.0f;
        infinite_data[14] = -2.0f*_NearClip;
        infinite_data[11] = 1.0f;
        infinite_data[15] = 0.0f;
    }

}
}
