#include "wide/plugins/plugins_library.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(plugins::Library);
    COFFEE_EndType();

namespace plugins
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Library::Library()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Library::~Library()
    {
    }    

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Library::_Initialize()
    {
        meta::Types::Get()._RegisterTypes(_RegisteredTypes);
        Initialize();                
    }
    
    //--------------------------------------------------------------------------------------------//

    void Library::_Finalize()
    {
        Finalize();
        meta::Types::Get()._UnregisterTypes(_RegisteredTypes);
    }

}
}
