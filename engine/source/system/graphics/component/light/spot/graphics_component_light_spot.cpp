#include "system/graphics/component/light/spot/graphics_component_light_spot.h"
#include "system/graphics/graphics.h"
#include "system/scene/scene.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::ComponentLightSpot);
        COFFEE_Ancestor(graphics::ComponentLightPoint);
        COFFEE_Attribute(real, _Apex, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ComponentLightSpot::ComponentLightSpot() :
        _Apex(40.0f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ComponentLightSpot::~ComponentLightSpot()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void ComponentLightSpot::SetApex(real apex)
    {
        _Apex = apex;
        _ItIsUpToDate = false;
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void ComponentLightSpot::OnStart()
    {
        if (GetMaterial().GetFilePath().IsEmpty())
        {
            SetMaterial(resource::Manager::Get().Load(
                storage::Path("/coffee/import/shaders/lights/spot.material")));
        }
    }

    //--------------------------------------------------------------------------------------------//

    void ComponentLightSpot::OnPropertyModified(const void* prop)
    {
        //if (prop==&_Apex)
        //    _ItIsUpToDate = false;

        ComponentLight::OnPropertyModified(prop);
    }

}
}
