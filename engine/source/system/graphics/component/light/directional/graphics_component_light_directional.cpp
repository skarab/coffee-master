#include "system/graphics/component/light/directional/graphics_component_light_directional.h"
#include "system/graphics/graphics.h"
#include "system/scene/scene.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::ComponentLightDirectional);
        COFFEE_Ancestor(graphics::ComponentLight);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ComponentLightDirectional::ComponentLightDirectional()
    {
        // Default to sun intensity
        SetIntensity(100000.0f);
    }

    //--------------------------------------------------------------------------------------------//

    ComponentLightDirectional::~ComponentLightDirectional()
    {
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void ComponentLightDirectional::OnStart()
    {
        if (GetMaterial().GetFilePath().IsEmpty())
        {
            SetMaterial(resource::Manager::Get().Load(
                storage::Path("/coffee/import/shaders/lights/directional.material")));
        }
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ComponentLightDirectional::_UpdateBounding()
    {
        // TODO: maybe add some infinite flag somewhere
        basic::Box box(basic::Vector3(), basic::Vector3(100000.0f, 100000.0f, 100000.0f));
        GetNode().GetBounding().SetLocalBox(box);
    }

}
}
