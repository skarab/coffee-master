#ifndef _COFFEE_COMPONENT_CONTROLLER_H_
#define _COFFEE_COMPONENT_CONTROLLER_H_

#include "coffee_includes.h"
#include "system/scene/component/scene_component.h"

namespace coffee
{
namespace component
{
    //--------------------------------------------------------------------------------------------//
    /// Controller component interface
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Controller : public scene::Component
    {
        COFFEE_Component(Controller, "Controller", "Controller/");

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Controller();
        ~Controller();

        //-HANDLERS-------------------------------------------------------------------------------//

        bool HandleInputs() { return true; }
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Controller);
}
}
#endif
