#ifndef _COFFEE_AUDIO_COMPONENT_H_
#define _COFFEE_AUDIO_COMPONENT_H_

#include "coffee_includes.h"
#include "system/scene/component/scene_component.h"

namespace coffee
{
namespace audio
{
    //--------------------------------------------------------------------------------------------//
    /// Audio component interface
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Component : public scene::Component
    {
        COFFEE_Type(Component);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Component();
        virtual ~Component();
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Component);
}
}
#endif
