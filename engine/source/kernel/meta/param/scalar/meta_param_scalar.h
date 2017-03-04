#ifndef _COFFEE_META_PARAM_SCALAR_H_
#define _COFFEE_META_PARAM_SCALAR_H_

#include "coffee_includes.h"
#include "kernel/meta/param/meta_param.h"

namespace coffee
{
namespace meta
{
    //--------------------------------------------------------------------------------------------//
    /// Scalar meta param
    ///
    /// Passing it to COFFEE_AttributeCustom, it allows to set edition parameters, like minimum and
    /// maximum values.
    ///
    /// @see COFFEE_AttributeCustom, coffee::meta::Param
    //--------------------------------------------------------------------------------------------//
    template< typename type > \
    class COFFEE_TEMPLATE_API ParamScalar : public Param
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ParamScalar();
        ParamScalar(uint32 mode, type minimum_value, type maximum_value);
        virtual ~ParamScalar();

        //-ACCESSORS------------------------------------------------------------------------------//

        type GetMinimumValue() const;
        type GetMaximumValue() const;

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        type _MinimumValue;
        type _MaximumValue;
    };
}
}

#include "kernel/meta/param/scalar/meta_param_scalar.hpp"

#endif
