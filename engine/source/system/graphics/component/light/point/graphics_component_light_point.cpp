#include "system/graphics/component/light/point/graphics_component_light_point.h"
#include "system/graphics/graphics.h"
#include "system/scene/scene.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::ComponentLightPoint);
        COFFEE_Ancestor(graphics::ComponentLight);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ComponentLightPoint::ComponentLightPoint() :
        _Radius(0.0f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ComponentLightPoint::~ComponentLightPoint()
    {
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void ComponentLightPoint::OnStart()
    {
        if (GetMaterial().GetFilePath().IsEmpty())
        {
            SetMaterial(resource::Manager::Get().Load(
                storage::Path("/coffee/import/shaders/lights/point.material")));
        }
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ComponentLightPoint::_UpdateBounding()
    {
        real minimum_lux = 0.01f;
        _Radius = sqrtf(GetIntensity()/minimum_lux);

        basic::Box box;
        box.AddSphere(basic::Sphere(basic::Vector3(), _Radius*GetRadiusMultiplier()), true);
        GetNode().GetBounding().SetLocalBox(box);
    }

}
}
