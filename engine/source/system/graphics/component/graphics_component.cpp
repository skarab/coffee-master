#include "system/graphics/component/graphics_component.h"
#include "system/graphics/component/graphics_components.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/scene/node/scene_node.h"
#include "system/scene/scene_world.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::Component);
        COFFEE_Ancestor(scene::Component);
        COFFEE_AttributeCustom(uint32, _Flags, COFFEE_New(meta::ParamEnumMulti, meta::MODE_Serializeable | meta::MODE_Editable,
            basic::String("graphics::COMPONENT_FLAG")));
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Component::Component() :
        _Flags(0)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Component::~Component()
    {
    }

}
}
