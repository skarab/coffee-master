//------------------------------------------------------------------------------------------------//
/// @file kernel/meta/type/meta_type_templates.hpp
//------------------------------------------------------------------------------------------------//

    //-OPERATIONS---------------------------------------------------------------------------------//

    template<> COFFEE_TEMPLATE_API Type& TYPE< bool >::Get();
    template<> COFFEE_TEMPLATE_API Type& TYPE< int8 >::Get();
    template<> COFFEE_TEMPLATE_API Type& TYPE< uint8 >::Get();
    template<> COFFEE_TEMPLATE_API Type& TYPE< int16 >::Get();
    template<> COFFEE_TEMPLATE_API Type& TYPE< uint16 >::Get();
    template<> COFFEE_TEMPLATE_API Type& TYPE< int32 >::Get();
    template<> COFFEE_TEMPLATE_API Type& TYPE< uint32 >::Get();
    template<> COFFEE_TEMPLATE_API Type& TYPE< real >::Get();
    
    //--------------------------------------------------------------------------------------------//

    template< typename type >
    Type& TYPE< type >::Get()
    {
        return type::GetClassMetaType();
    }

//------------------------------------------------------------------------------------------------//
