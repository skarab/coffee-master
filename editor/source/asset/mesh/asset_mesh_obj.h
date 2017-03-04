#ifndef _EDITOR_ASSET_MESH_OBJ_H_
#define _EDITOR_ASSET_MESH_OBJ_H_

#include "coffee_editor_includes.h"
#include "asset/asset_importer.h"
#include "asset/asset_manager.h"
#include "asset/mesh/asset_mesh_obj_file.h"
#include "asset/mesh/asset_mesh_mapping.h"

namespace coffee_editor
{
namespace asset
{
    //--------------------------------------------------------------------------------------------//
    /// OBJ mesh asset
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API MeshOBJ : public Importer
    {
        COFFEE_Type(MeshOBJ);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        MeshOBJ();
        ~MeshOBJ();

        //-QUERIES--------------------------------------------------------------------------------//

        static bool IsSupporting(const basic::String& file_extension);

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Import();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        real _Scale;
        MESH_MAP_MODE _TexCoords;
        MESH_MAP_MODE _Normals;
        bool _GenerateAdjacency;
        bool _FlipPolygons;
        MESH_MAP_COMPONENT _X;
        MESH_MAP_COMPONENT _Y;
        MESH_MAP_COMPONENT _Z;
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, MeshOBJ);
}
}
#endif
