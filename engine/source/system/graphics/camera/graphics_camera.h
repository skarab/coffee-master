#ifndef _COFFEE_GRAPHICS_CAMERA_H_
#define _COFFEE_GRAPHICS_CAMERA_H_

#include "coffee_includes.h"
#include "system/scene/scene.h"
#include "system/graphics/component/camera/graphics_component_camera.h"

namespace coffee
{
namespace graphics
{
    //-FORWARDS-----------------------------------------------------------------------------------//
    class Viewport;

    //--------------------------------------------------------------------------------------------//
    /// Camera linking a component to a viewport
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Camera : public meta::Object
    {
        COFFEE_Type(Camera);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Camera();
        Camera(Viewport* viewport, const resource::Handler<scene::Resource>& scene, ComponentCamera* component);
        ~Camera();
        
        //-ACCESSORS------------------------------------------------------------------------------//

        const resource::Handler<scene::Resource>& GetScene() const { return _Scene; }
        resource::Handler<scene::Resource>& GetScene() { return _Scene; }
        const ComponentCamera& GetComponent() const { return *_Component; }
        ComponentCamera& GetComponent() { return *_Component; }

        //-QUERIES--------------------------------------------------------------------------------//

        basic::Vector3 ComputeScreenToWorldPoint(const basic::Vector2& screen_point) const;
        basic::Vector3 ComputeViewportToWorldPoint(const basic::Vector2& viewport_point) const;
        basic::Vector3 ComputeFrameToWorldPoint(const basic::Vector2& frame_point) const;

        basic::Vector2i ComputeWorldToScreenPoint(const basic::Vector3& world_point) const;
        basic::Vector2i ComputeWorldToViewportPoint(const basic::Vector3& world_point) const;
        basic::Vector2i ComputeWorldToFramePoint(const basic::Vector3& world_point) const;

        basic::Rectangle ComputeFrameProjectedBox(const basic::Box& local_box,
            const basic::Matrix& local_to_world) const;

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Viewport* _Viewport;
        resource::Handler<scene::Resource> _Scene;
        ComponentCamera* _Component;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Camera);
}
}
#endif
