#ifndef _EDITOR_ASSET_POINT_CLOUD_PLY_H_
#define _EDITOR_ASSET_POINT_CLOUD_PLY_H_

#include "coffee_editor_includes.h"
#include "asset/asset_importer.h"
#include "asset/asset_manager.h"

namespace coffee_editor
{
namespace asset
{
    //--------------------------------------------------------------------------------------------//
    /// PLY point cloud importer - testing purpose
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API PointCloudPLY : public Importer
    {
        COFFEE_Type(PointCloudPLY);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PointCloudPLY();
        virtual ~PointCloudPLY();

        //-QUERIES--------------------------------------------------------------------------------//

        static bool IsSupporting(const basic::String& file_extension);

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual bool Import();

    protected:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        uint32 _Parameters;
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, PointCloudPLY);
}
}
#endif
