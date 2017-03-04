#ifndef _COFFEE_UI_PROPERTY_MESSAGE_H_
#define _COFFEE_UI_PROPERTY_MESSAGE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Property messages
    //--------------------------------------------------------------------------------------------//
    enum PROPERTY_MESSAGE
    {
        PROPERTY_MESSAGE_Modified,    ///< modified using GUI : event send from GUI
        PROPERTY_MESSAGE_Update       ///< modified from accessors : event send to GUI
    };
}
}
#endif
