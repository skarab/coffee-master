#ifndef _EDITOR_ASSET_MESH_MODIFIER_H_
#define _EDITOR_ASSET_MESH_MODIFIER_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
namespace asset
{
    //-FUNCTIONS----------------------------------------------------------------------------------//

    //--------------------------------------------------------------------------------------------//
    /// @brief Compute TBN of the specified mesh
    //--------------------------------------------------------------------------------------------//
    COFFEE_EDITOR_API bool MeshModifierComputeTBN(graphics::Mesh& mesh);

    //--------------------------------------------------------------------------------------------//
    /// @brief Compute edjes adjacency of the specified mesh
    //--------------------------------------------------------------------------------------------//
    COFFEE_EDITOR_API bool MeshModifierComputeAdjacency(graphics::Mesh& mesh);

}
}
#endif
