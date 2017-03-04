#ifndef _COFFEE_META_PARAM_SCALAR_UINT32_H_
#define _COFFEE_META_PARAM_SCALAR_UINT32_H_

#include "coffee_includes.h"
#include "kernel/meta/param/scalar/meta_param_scalar.h"

namespace coffee
{
namespace meta
{
    //--------------------------------------------------------------------------------------------//
    /// uint32 meta param
    ///
    /// @see coffee::meta::ParamScalar
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ParamScalarUInt32 : public ParamScalar< uint32 >
    {
        COFFEE_Type(ParamScalarUInt32);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ParamScalarUInt32();
        ParamScalarUInt32(uint32 mode, uint32 minimum_value, uint32 maximum_value);
        ~ParamScalarUInt32();
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ParamScalarUInt32);
}
}
#endif
