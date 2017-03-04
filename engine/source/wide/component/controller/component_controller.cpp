#include "wide/component/controller/component_controller.h"
#include "system/input/input.h"
#include "system/scene/scene.h"
#include "wide/ui/window/ui_window_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(component::Controller);
        COFFEE_Ancestor(scene::Component);
    COFFEE_EndType();

namespace component
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Controller::Controller()
    {
        SetIsAutomatic(false);
    }

    //--------------------------------------------------------------------------------------------//

    Controller::~Controller()
    {
    }

}
}
