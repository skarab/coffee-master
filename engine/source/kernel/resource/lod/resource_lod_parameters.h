#ifndef _COFFEE_RESOURCE_LOD_PARAMETERS_H_
#define _COFFEE_RESOURCE_LOD_PARAMETERS_H_

#include "coffee_includes.h"
#include "kernel/meta/meta.h"
#include "kernel/basic/alpha/string/basic_string.h"

namespace coffee
{
namespace resource
{
    //--------------------------------------------------------------------------------------------//
    /// Interface class for custom LOD parameters
    ///
    /// @see coffee::resource::LOD, coffee::resource::Chunk
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API LODParameters : public meta::Object
    {
        COFFEE_Type(LODParameters);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        LODParameters();
        virtual ~LODParameters();

        //-QUERIES--------------------------------------------------------------------------------//

        virtual uint32 GetMaximumLODCount() const;
        virtual basic::String GetLODName(uint32 lod_index) const;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, LODParameters);
}
}
#endif
