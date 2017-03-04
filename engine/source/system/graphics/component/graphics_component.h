#ifndef _COFFEE_GRAPHICS_COMPONENT_H_
#define _COFFEE_GRAPHICS_COMPONENT_H_

#include "coffee_includes.h"
#include "system/scene/component/scene_component.h"
#include "system/graphics/material/graphics_material.h"
#include "system/graphics/component/graphics_component_flag.h"

namespace coffee
{
namespace graphics
{
    class Viewport;

    //--------------------------------------------------------------------------------------------//
    /// Graphics component interface
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Component : public scene::Component
    {
        COFFEE_Type(Component);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Component();
        virtual ~Component();

        //-ACCESSORS------------------------------------------------------------------------------//

        void EnableFlag(COMPONENT_FLAG flag, bool it_has_to_enable) { COFFEE_EnableFlag(_Flags, flag, it_has_to_enable); }
        bool IsFlagEnabled(COMPONENT_FLAG flag) const { return COFFEE_IsFlagEnabled(_Flags, flag); }

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        uint32 _Flags;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Component);
}
}
#endif
