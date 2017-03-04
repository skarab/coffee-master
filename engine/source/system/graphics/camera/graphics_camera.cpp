#include "system/graphics/viewport/graphics_viewport.h"

namespace coffee
{
namespace graphics
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::Camera);
    COFFEE_EndType();

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Camera::Camera() :
        _Viewport(NULL),
        _Component(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Camera::Camera(Viewport* viewport, const resource::Handler<scene::Resource>& scene, ComponentCamera* component) :
        _Viewport(viewport),
        _Scene(scene),
        _Component(component)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Camera::~Camera()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    basic::Vector3 Camera::ComputeScreenToWorldPoint(const basic::Vector2& screen_point) const
    {
        return ComputeFrameToWorldPoint(_Viewport->ComputeScreenToFramePoint(screen_point));
    }

    //--------------------------------------------------------------------------------------------//

    basic::Vector3 Camera::ComputeViewportToWorldPoint(const basic::Vector2& viewport_point) const
    {
        return ComputeFrameToWorldPoint(_Viewport->ComputeViewportToFramePoint(viewport_point));
    }
       
    //--------------------------------------------------------------------------------------------//

    basic::Vector3 Camera::ComputeFrameToWorldPoint(const basic::Vector2& frame_point) const
    {
        basic::Vector4 point;
        basic::Vector3 world_point;

        point.Set(frame_point.X, frame_point.Y, 1.0f, 1.0f);
        point *= _Viewport->GetFrameToViewportMatrix();
        point *= _Component->GetViewportToLocalMatrix();

        world_point.Set(point.X, point.Y, point.Z);

        if(point.W == 0.0f)
            point.W=0.00001f;

        world_point *= point.W;
        world_point *= _Component->GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World);
        return world_point;
    }

    //--------------------------------------------------------------------------------------------//

    basic::Vector2i Camera::ComputeWorldToScreenPoint(const basic::Vector3& world_point) const
    {
        return _Viewport->ComputeFrameToScreenPoint(ComputeWorldToFramePoint(world_point));
    }
    
    //--------------------------------------------------------------------------------------------//

    basic::Vector2i Camera::ComputeWorldToViewportPoint(const basic::Vector3& world_point) const
    {
        return _Viewport->ComputeFrameToViewportPoint(ComputeWorldToFramePoint(world_point));
    }

    //--------------------------------------------------------------------------------------------//

    basic::Vector2i Camera::ComputeWorldToFramePoint(const basic::Vector3& world_point) const
    {
        basic::Vector4 point;

        point.Set(world_point.X, world_point.Y, world_point.Z, 1.0f);
        point *= _Component->GetNode().GetTransform().GetMatrix(scene::TRS_World, scene::TRS_Local);

        if (point.Z<_Component->GetNearClip())
            point.Z = _Component->GetNearClip();

        point *= _Component->GetInfiniteProjectionMatrix();
        point /= point.W;
        point *= _Viewport->GetViewportToFrameMatrix();
        return basic::Vector2i((int32)point.X, (int32)point.Y);
    }

    //--------------------------------------------------------------------------------------------//

    basic::Rectangle Camera::ComputeFrameProjectedBox(const basic::Box& local_box,
            const basic::Matrix& local_to_world) const
    {
        basic::Vector3 minimum(local_box.GetMinimum());
        basic::Vector3 maximum(local_box.GetMaximum());
        basic::Vector3 p[8];
        
        p[0] = basic::Vector3(minimum.X, minimum.Y, minimum.Z);
        p[1] = basic::Vector3(maximum.X, minimum.Y, minimum.Z);
        p[2] = basic::Vector3(minimum.X, maximum.Y, minimum.Z);
        p[3] = basic::Vector3(minimum.X, minimum.Y, maximum.Z);
        p[4] = basic::Vector3(maximum.X, maximum.Y, minimum.Z);
        p[5] = basic::Vector3(minimum.X, maximum.Y, maximum.Z);
        p[6] = basic::Vector3(maximum.X, minimum.Y, maximum.Z);
        p[7] = basic::Vector3(maximum.X, maximum.Y, maximum.Z);

        basic::Vector2i rect_minimum;
        basic::Vector2i rect_maximum;
        for (uint32 index=0 ; index<8 ; ++index)
        {
            basic::Vector2i point = ComputeWorldToFramePoint(p[index]*local_to_world);
            if (index==0)
            {
                rect_minimum = point;
                rect_maximum = point;
            }
            else
            {
                if (point.X<rect_minimum.X) rect_minimum.X = point.X;
                if (point.Y<rect_minimum.Y) rect_minimum.Y = point.Y;
                if (point.X>rect_maximum.X) rect_maximum.X = point.X;
                if (point.Y>rect_maximum.Y) rect_maximum.Y = point.Y;
            }
        }        
        
        basic::Rectangle rect;
        rect.SetFromExtent(rect_minimum, rect_maximum);
        return rect;
    }

}
}
