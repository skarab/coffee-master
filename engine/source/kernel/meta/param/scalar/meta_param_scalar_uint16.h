#ifndef _COFFEE_META_PARAM_SCALAR_UINT16_H_
#define _COFFEE_META_PARAM_SCALAR_UINT16_H_

#include "coffee_includes.h"
#include "kernel/meta/param/scalar/meta_param_scalar.h"

namespace coffee
{
namespace meta
{
    //--------------------------------------------------------------------------------------------//
    /// uint16 meta param
    ///
    /// @see coffee::meta::ParamScalar
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ParamScalarUInt16 : public ParamScalar< uint16 >
    {
        COFFEE_Type(ParamScalarUInt16);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ParamScalarUInt16();
        ParamScalarUInt16(uint32 mode, uint16 minimum_value, uint16 maximum_value);
        ~ParamScalarUInt16();
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ParamScalarUInt16);
}
}
#endif
