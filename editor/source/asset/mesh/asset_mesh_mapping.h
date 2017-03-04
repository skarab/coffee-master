#ifndef _EDITOR_ASSET_MESH_MAPPING_H_
#define _EDITOR_ASSET_MESH_MAPPING_H_

#include "coffee_editor_includes.h"
#include "kernel/meta/meta_enum.h"

namespace coffee_editor
{
namespace asset
{
    //--------------------------------------------------------------------------------------------//
    /// @enum MESH_MAP_MODE
    /// @brief Map mode
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(asset, MESH_MAP_MODE, "Mode", Single)
        COFFEE_EnumValue(MESH_MAP_MODE, Keep, 0)
        COFFEE_EnumValue(MESH_MAP_MODE, KeepOrGenerate, 1)
        COFFEE_EnumValue(MESH_MAP_MODE, Generate, 2)
        COFFEE_EnumValue(MESH_MAP_MODE, Discard, 3)
    COFFEE_EndEnum(COFFEE_EDITOR_API, COFFEE_EDITOR_EXPORT_STATICS, MESH_MAP_MODE)

    //--------------------------------------------------------------------------------------------//
    /// @enum MESH_MAP_COMPONENT
    /// @brief Map vertex component
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(asset, MESH_MAP_COMPONENT, "Component", Single)
        COFFEE_EnumValue(MESH_MAP_COMPONENT, X, 0)
        COFFEE_EnumValue(MESH_MAP_COMPONENT, Y, 1)
        COFFEE_EnumValue(MESH_MAP_COMPONENT, Z, 2)
        COFFEE_EnumValue(MESH_MAP_COMPONENT, InverseX, 3)
        COFFEE_EnumValue(MESH_MAP_COMPONENT, InverseY, 4)
        COFFEE_EnumValue(MESH_MAP_COMPONENT, InverseZ, 5)
    COFFEE_EndEnum(COFFEE_EDITOR_API, COFFEE_EDITOR_EXPORT_STATICS, MESH_MAP_COMPONENT)
}
}
#endif
