#ifndef _COFFEE_DEBUG_H_
#define _COFFEE_DEBUG_H_

namespace coffee
{
    //--------------------------------------------------------------------------------------------//
    /// Run modes of Coffee
    ///
    /// Set with COFFEE_RegisterApplication
    /// Those modes are supported either in debug and in release build.
    //--------------------------------------------------------------------------------------------//
    enum RUN_MODE
    {
        RUN_MODE_None             = 0,        ///< no mode
        RUN_MODE_MemoryReport     = 1 << 0,   ///< generate memory statistics and check for leaks
        RUN_MODE_MemoryTrack      = 1 << 1,   ///< full tracking, require RUN_MODE_MemoryReport
        RUN_MODE_MetaType         = 1 << 2,   ///< logging of types registration
        RUN_MODE_Events           = 1 << 3,   ///< check for events mess (loops/high counts)
        RUN_MODE_Editor           = 1 << 4,   ///< editor application
        RUN_MODE_UnitTest         = 1 << 5    ///< unittest application
    };
}
#endif
