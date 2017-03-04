//------------------------------------------------------------------------------------------------//
/// @file kernel/resource/property/resource_property.hpp
//------------------------------------------------------------------------------------------------//

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    Property< type >::Property()
    {
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    Property< type >::Property(const type & value) :
        _Value(value)
    {
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    Property< type >::~Property()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    template< typename type >
    void Property< type >::Set(const type& value)
    {
        Grab() = value;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    const type& Property< type >::Get() const
    {
        return ((Property< type > *) &GetProperty())->_Value;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    type& Property< type >::Grab()
    {
        return ((Property< type > *) &GrabProperty())->_Value;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void Property< type >::SetValue(const type& value)
    {
        _Value = value;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    const type& Property< type >::GetValue() const
    {
        return _Value;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    type& Property< type >::GrabValue()
    {
        return _Value;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    type& Property< type >::_metaValue()
    {
        return _Value;
    }

//------------------------------------------------------------------------------------------------//
