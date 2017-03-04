//------------------------------------------------------------------------------------------------//
/// @file kernel/meta/param/scalar/meta_param_scalar.hpp
//------------------------------------------------------------------------------------------------//

namespace coffee
{
namespace meta
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    template< typename type >
    ParamScalar< type >::ParamScalar()
    {
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    ParamScalar< type >::ParamScalar(uint32 mode, type minimum_value, type maximum_value) :
        Param(mode),
        _MinimumValue(minimum_value),
        _MaximumValue(maximum_value)
    {
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    ParamScalar< type >::~ParamScalar()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    template< typename type >
    type ParamScalar< type >::GetMinimumValue() const
    {
        return _MinimumValue;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    type ParamScalar< type >::GetMaximumValue() const
    {
        return _MaximumValue;
    }
}
}
//------------------------------------------------------------------------------------------------//
