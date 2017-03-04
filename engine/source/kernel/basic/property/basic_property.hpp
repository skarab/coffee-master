
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    template< typename type >
    Property< type >::Property() :
        PropertyBase("", &meta::TYPE<type>().Get())
    {
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    Property< type >::Property(String name) :
        PropertyBase(name, meta::TYPE< type >().Get())
    {
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    Property< type >::~Property()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    template< typename type >
    void Property< type >::SetValue(const type & object)
    {
        PropertyBase::SetMetaObjectValue(object);
    }

    //--------------------------------------------------------------------------------------------//

    template<> COFFEE_TEMPLATE_API void Property< bool >::SetValue(const bool & object);
    template<> COFFEE_TEMPLATE_API void Property< int8 >::SetValue(const int8 & object);
    template<> COFFEE_TEMPLATE_API void Property< uint8 >::SetValue(const uint8 & object);
    template<> COFFEE_TEMPLATE_API void Property< int16 >::SetValue(const int16 & object);
    template<> COFFEE_TEMPLATE_API void Property< uint16 >::SetValue(const uint16 & object);
    template<> COFFEE_TEMPLATE_API void Property< int32 >::SetValue(const int32 & object);
    template<> COFFEE_TEMPLATE_API void Property< uint32 >::SetValue(const uint32 & object);
    template<> COFFEE_TEMPLATE_API void Property< real >::SetValue(const real & object);

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    const type & Property< type >::GetValue() const
    {
        return *((type *) PropertyBase::GetObject());
    }

    //--------------------------------------------------------------------------------------------//

    template<> COFFEE_TEMPLATE_API const bool & Property< bool >::GetValue() const;
    template<> COFFEE_TEMPLATE_API const int8 & Property< int8 >::GetValue() const;
    template<> COFFEE_TEMPLATE_API const uint8 & Property< uint8 >::GetValue() const;
    template<> COFFEE_TEMPLATE_API const int16 & Property< int16 >::GetValue() const;
    template<> COFFEE_TEMPLATE_API const uint16 & Property< uint16 >::GetValue() const;
    template<> COFFEE_TEMPLATE_API const int32 & Property< int32 >::GetValue() const;
    template<> COFFEE_TEMPLATE_API const uint32 & Property< uint32 >::GetValue() const;
    template<> COFFEE_TEMPLATE_API const real & Property< real >::GetValue() const;

