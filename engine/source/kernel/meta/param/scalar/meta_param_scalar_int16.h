#ifndef _COFFEE_META_PARAM_SCALAR_INT16_H_
#define _COFFEE_META_PARAM_SCALAR_INT16_H_

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
    class COFFEE_API ParamScalarInt16 : public ParamScalar< int16 >
    {
        COFFEE_Type(ParamScalarInt16);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ParamScalarInt16();
        ParamScalarInt16(uint32 mode, int16 minimum_value, int16 maximum_value);
        ~ParamScalarInt16();
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ParamScalarInt16);
}
}
#endif
