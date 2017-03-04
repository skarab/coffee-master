#ifndef _COFFEE_META_PARAM_SCALAR_UINT8_H_
#define _COFFEE_META_PARAM_SCALAR_UINT8_H_

#include "coffee_includes.h"
#include "kernel/meta/param/scalar/meta_param_scalar.h"

namespace coffee
{
namespace meta
{
    //--------------------------------------------------------------------------------------------//
    /// uint8 meta param
    ///
    /// @see coffee::meta::ParamScalar
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ParamScalarUInt8 : public ParamScalar< uint8 >
    {
        COFFEE_Type(ParamScalarUInt8);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ParamScalarUInt8();
        ParamScalarUInt8(uint32 mode, uint8 minimum_value, uint8 maximum_value);
        ~ParamScalarUInt8();
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ParamScalarUInt8);
}
}
#endif
