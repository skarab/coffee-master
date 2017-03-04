#include "wide/plugins/component/plugins_component_library.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(plugins::ComponentLibrary);
        COFFEE_Ancestor(plugins::Library);
    COFFEE_EndType();

namespace plugins
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ComponentLibrary::ComponentLibrary()
    {
    }

    //--------------------------------------------------------------------------------------------//

    ComponentLibrary::~ComponentLibrary()
    {
    }

}
}
