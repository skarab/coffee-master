#include "system/graphics/component/light/ies/graphics_component_light_ies.h"
#include "system/graphics/graphics.h"
#include "system/scene/scene.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::ComponentLightIES);
        COFFEE_Ancestor(graphics::ComponentLightSpot);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ComponentLightIES::ComponentLightIES()
    {
    }

    //--------------------------------------------------------------------------------------------//

    ComponentLightIES::~ComponentLightIES()
    {
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void ComponentLightIES::OnStart()
    {
        if (GetMaterial().GetFilePath().IsEmpty())
        {
            SetMaterial(resource::Manager::Get().Load(
                storage::Path("/coffee/import/shaders/lights/ies.material")));
        }
    }

}
}
