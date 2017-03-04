#include "kernel/basic/property/basic_property.h"

namespace coffee
{
namespace basic
{
    //-OPERATIONS---------------------------------------------------------------------------------//

    template<>
    void Property< bool >::SetValue(const bool & object)
    {
        PropertyBase::SetScalarValue((char *) &object);
    }

    //--------------------------------------------------------------------------------------------//

    template<>
    void Property< int8 >::SetValue(const int8 & object)
    {
        PropertyBase::SetScalarValue((char *) &object);
    }

    //--------------------------------------------------------------------------------------------//

    template<>
    void Property< uint8 >::SetValue(const uint8 & object)
    {
        PropertyBase::SetScalarValue((char *) &object);
    }

    //--------------------------------------------------------------------------------------------//

    template<>
    void Property< int16 >::SetValue(const int16 & object)
    {
        PropertyBase::SetScalarValue((char *) &object);
    }

    //--------------------------------------------------------------------------------------------//

    template<>
    void Property< uint16 >::SetValue(const uint16 & object)
    {
        PropertyBase::SetScalarValue((char *) &object);
    }

    //--------------------------------------------------------------------------------------------//

    template<>
    void Property< int32 >::SetValue(const int32 & object)
    {
        PropertyBase::SetScalarValue((char *) &object);
    }

    //--------------------------------------------------------------------------------------------//

    template<>
    void Property< uint32 >::SetValue(const uint32 & object)
    {
        PropertyBase::SetScalarValue((char *) &object);
    }

    //--------------------------------------------------------------------------------------------//

    template<>
    void Property< real >::SetValue(const real & object)
    {
        PropertyBase::SetScalarValue((char *) &object);
    }

    //--------------------------------------------------------------------------------------------//

    template<>
    const bool & Property< bool >::GetValue() const
    {
        return *((bool *) PropertyBase::GetScalarObject());
    }

    //--------------------------------------------------------------------------------------------//

    template<>
    const int8 & Property< int8 >::GetValue() const
    {
        return *((int8 *) PropertyBase::GetScalarObject());
    }

    //--------------------------------------------------------------------------------------------//

    template<>
    const uint8 & Property< uint8 >::GetValue() const
    {
        return *((uint8 *) PropertyBase::GetScalarObject());
    }

    //--------------------------------------------------------------------------------------------//

    template<>
    const int16 & Property< int16 >::GetValue() const
    {
        return *((int16 *) PropertyBase::GetScalarObject());
    }

    //--------------------------------------------------------------------------------------------//

    template<>
    const uint16 & Property< uint16 >::GetValue() const
    {
        return *((uint16 *) PropertyBase::GetScalarObject());
    }

    //--------------------------------------------------------------------------------------------//

    template<>
    const int32 & Property< int32 >::GetValue() const
    {
        return *((int32 *) PropertyBase::GetScalarObject());
    }

    //--------------------------------------------------------------------------------------------//

    template<>
    const uint32 & Property< uint32 >::GetValue() const
    {
        return *((uint32 *) PropertyBase::GetScalarObject());
    }

    //--------------------------------------------------------------------------------------------//

    template<>
    const real & Property< real >::GetValue() const
    {
        return *((real *) PropertyBase::GetScalarObject());
    }

}
}
