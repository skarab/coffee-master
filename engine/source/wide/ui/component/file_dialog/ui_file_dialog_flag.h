#ifndef _COFFEE_UI_FILE_DIALOG_FLAG_H_
#define _COFFEE_UI_FILE_DIALOG_FLAG_H_

#include "coffee_includes.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// File dialog flags
    //--------------------------------------------------------------------------------------------//
    enum FILE_DIALOG_FLAG
    {
        FILE_DIALOG_FLAG_Open = 0,
        FILE_DIALOG_FLAG_Save = 1,
        FILE_DIALOG_FLAG_FileMustExist = 2
    };
}
}
#endif
