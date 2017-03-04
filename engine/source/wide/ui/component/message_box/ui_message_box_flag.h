#ifndef _COFFEE_UI_MESSAGE_BOX_FLAG_H_
#define _COFFEE_UI_MESSAGE_BOX_FLAG_H_

#include "coffee_includes.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Message box flags
    //--------------------------------------------------------------------------------------------//
    enum MESSAGE_BOX_FLAG
    {
        MESSAGE_BOX_FLAG_None = 0,      ///< no buttons
        MESSAGE_BOX_FLAG_Ok = 1,        ///< single button named "Ok"
        MESSAGE_BOX_FLAG_YesNo = 2,     ///< two buttons named "Yes" and "No"
        MESSAGE_BOX_FLAG_OkCancel = 3   ///< two buttons named "Ok" and "Cancel"
    };
}
}
#endif
