#include "system/graphics/component/sky/graphics_component_sky.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::ComponentSky);
        COFFEE_Ancestor(graphics::Component);
        COFFEE_Attribute(graphics::Sky, _Sky, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ComponentSky::ComponentSky()
    {
    }

    //--------------------------------------------------------------------------------------------//

    ComponentSky::~ComponentSky()
    {
    }

    //-HANDLERS-------------------------------------------------------------------------------//

    void ComponentSky::OnStart()
    {
        if (_Sky.GetFilePath().IsEmpty())
        {
            SetSky(resource::Manager::Get().Load(
                storage::Path("/coffee/import/lightprobes/default.sky")));
        }
    }

}
}
