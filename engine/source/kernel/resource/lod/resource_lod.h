#ifndef _COFFEE_RESOURCE_LOD_H_
#define _COFFEE_RESOURCE_LOD_H_

#include "coffee_includes.h"
#include "kernel/resource/lod/resource_lod_parameters.h"
#include "kernel/resource/lod/resource_lod_state.h"

namespace coffee
{
namespace resource
{
    class Object;

    //--------------------------------------------------------------------------------------------//
    /// Resource LOD - contains LOD resource and parameters
    ///
    /// This class shouldn't be accessed directly, it's for internal purpose only.
    ///
    /// The resource LOD contains the LOD resource itself, and the custom LOD parameters.
    /// Management of these LOD is done by the resource chunk.
    ///
    /// @see coffee::resource::Chunk
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API LOD : public meta::Object
    {
        COFFEE_Type(LOD);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        LOD();
        ~LOD();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetState(const LOD_STATE & state);
        const LOD_STATE & GetState() const;
        void SetData(resource::Object & data);
        const resource::Object & GetData() const;
        resource::Object & GetData();
        void SetParameters(LODParameters & parameters);
        const LODParameters & GetParameters() const;
        LODParameters & GetParameters();

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsLoaded() const;
        bool HasData() const;
        bool HasParameters() const;

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        LOD_STATE _State;
        resource::Object * _Data;
        LODParameters * _Parameters;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, LOD);
}
}
#endif
