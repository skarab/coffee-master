#include "editor.h"

COFFEE_RegisterApplication(
    coffee_editor::Application,
    RUN_MODE_Editor
    | RUN_MODE_MemoryReport
    //| RUN_MODE_MemoryTrack
    //| RUN_MODE_Events
    //| RUN_MODE_MetaType
    );

