#ifndef _EDITOR_ASSET_SYNC_FLAG_H_
#define _EDITOR_ASSET_SYNC_FLAG_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
namespace asset
{
    //--------------------------------------------------------------------------------------------//
    /// Synchronization flag
    //--------------------------------------------------------------------------------------------//
    enum SYNC_FLAG
    {
        SYNC_FLAG_None = 0,
        SYNC_FLAG_ForceAll = 1 << 0,        ///< Force reimport all
        SYNC_FLAG_CheckScripts = 1 << 1,    ///< Rebuild scripts if required
        SYNC_FLAG_Immediate = 1 << 2        ///< Dont use asynchronous mode
    };
}
}
#endif
