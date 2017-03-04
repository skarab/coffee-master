#ifndef _COFFEE_META_PARAM_SCALAR_REAL_H_
#define _COFFEE_META_PARAM_SCALAR_REAL_H_

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
    class COFFEE_API ParamScalarReal : public ParamScalar< real >
    {
        COFFEE_Type(ParamScalarReal);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ParamScalarReal();
        ParamScalarReal(uint32 mode, real minimum_value, real maximum_value);
        ~ParamScalarReal();
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ParamScalarReal);
}
}
#endif
