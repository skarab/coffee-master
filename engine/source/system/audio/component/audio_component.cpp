#include "system/audio/component/audio_component.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(audio::Component);
        COFFEE_Ancestor(scene::Component);
    COFFEE_EndType();

namespace audio
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Component::Component()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Component::~Component()
    {
    }

}
}
