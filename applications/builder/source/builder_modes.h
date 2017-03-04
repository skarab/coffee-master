#ifndef _BUILDER_MODES_H_
#define _BUILDER_MODES_H_

#include "builder_includes.h"
#include "kernel/meta/meta_enum.h"

namespace builder
{

    //--------------------------------------------------------------------------------------------//
    /// Build operations
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(builder, OPERATION, "Operation", Single)
        COFFEE_EnumValue(OPERATION, build, 0)
        COFFEE_EnumValue(OPERATION, clean, 1)
        COFFEE_EnumValue(OPERATION, rebuild, 2)
    COFFEE_EndEnum(BUILDER, BUILDER_EXPORT_STATICS, OPERATION)

    //--------------------------------------------------------------------------------------------//
    /// Build targets
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(builder, TARGET, "Target", Single)
        COFFEE_EnumValue(TARGET, all, 0)
        COFFEE_EnumValue(TARGET, externals, 1)
        COFFEE_EnumValue(TARGET, coffee_engine, 2)
        COFFEE_EnumValue(TARGET, coffee_player, 3)
        COFFEE_EnumValue(TARGET, coffee_editor, 4)
        COFFEE_EnumValue(TARGET, player, 5)
        COFFEE_EnumValue(TARGET, coffee, 6)
        COFFEE_EnumValue(TARGET, builder, 7)
        COFFEE_EnumValue(TARGET, plugins, 8)
        COFFEE_EnumValue(TARGET, unittest, 9)
    COFFEE_EndEnum(BUILDER, BUILDER_EXPORT_STATICS, TARGET)

    //--------------------------------------------------------------------------------------------//
    /// Target platform
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(builder, PLATFORM, "Platform", Single)
        COFFEE_EnumValue(PLATFORM, win32, 0)
    COFFEE_EndEnum(BUILDER, BUILDER_EXPORT_STATICS, PLATFORM)

    //--------------------------------------------------------------------------------------------//
    /// Target compiler
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(builder, COMPILER, "Compiler", Single)
        COFFEE_EnumValue(COMPILER, mingw, 0)
        COFFEE_EnumValue(COMPILER, vs2005, 1)
        COFFEE_EnumValue(COMPILER, vs2008, 2)
        COFFEE_EnumValue(COMPILER, vs2010, 3)
        COFFEE_EnumValue(COMPILER, vs2012, 4)
    COFFEE_EndEnum(BUILDER, BUILDER_EXPORT_STATICS, COMPILER)

    //--------------------------------------------------------------------------------------------//
    /// Build mode
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(builder, MODE, "Mode", Single)
        COFFEE_EnumValue(MODE, release, 0)
        COFFEE_EnumValue(MODE, debug, 1)
    COFFEE_EndEnum(BUILDER, BUILDER_EXPORT_STATICS, MODE)

}
#endif
