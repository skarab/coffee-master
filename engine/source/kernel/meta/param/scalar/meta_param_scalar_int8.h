#ifndef _COFFEE_META_PARAM_SCALAR_INT8_H_
#define _COFFEE_META_PARAM_SCALAR_INT8_H_

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
    class COFFEE_API ParamScalarInt8 : public ParamScalar< int8 >
    {
        COFFEE_Type(ParamScalarInt8);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ParamScalarInt8();
        ParamScalarInt8(uint32 mode, int8 minimum_value, int8 maximum_value);
        ~ParamScalarInt8();
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ParamScalarInt8);
}
}
#endif
