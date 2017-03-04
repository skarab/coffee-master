#ifndef _COFFEE_META_PARAM_SCALAR_INT32_H_
#define _COFFEE_META_PARAM_SCALAR_INT32_H_

#include "coffee_includes.h"
#include "kernel/meta/param/scalar/meta_param_scalar.h"

namespace coffee
{
namespace meta
{
    //--------------------------------------------------------------------------------------------//
    /// real meta param
    ///
    /// @see coffee::meta::ParamScalar
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ParamScalarInt32 : public ParamScalar< int32 >
    {
        COFFEE_Type(ParamScalarInt32);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ParamScalarInt32();
        ParamScalarInt32(uint32 mode, int32 minimum_value, int32 maximum_value);
        ~ParamScalarInt32();
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ParamScalarInt32);
}
}
#endif
