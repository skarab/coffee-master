#ifndef _COFFEE_GRAPHICS_COMPONENT_CAMERA_PERSPECTIVE_H_
#define _COFFEE_GRAPHICS_COMPONENT_CAMERA_PERSPECTIVE_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/component/camera/graphics_component_camera.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Graphics perspective camera class
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ComponentCameraPerspective : public ComponentCamera
    {
        COFFEE_Component(ComponentCameraPerspective, "Perspective Camera", "Graphics/");

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ComponentCameraPerspective();
        ~ComponentCameraPerspective();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetFieldOfView(real field_of_view) { _FieldOfView = field_of_view; }
        real GetFieldOfView() const { return _FieldOfView; }
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        void Update(Viewport& viewport);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _UpdateProjectionMatrix(Viewport& viewport);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        real _FieldOfView;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ComponentCameraPerspective);
}
}
#endif
