#include "kernel/basic/property/basic_property_scalar.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::PropertyScalar);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PropertyScalar::PropertyScalar() :
        _Format(meta::SCALAR_FORMAT_None),
        _Object(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    PropertyScalar::PropertyScalar(const meta::SCALAR_FORMAT & format) :
        _Format(format),
        _Object(NULL)
    {
        Create();
    }

    //--------------------------------------------------------------------------------------------//

    PropertyScalar::~PropertyScalar()
    {
        Destroy();
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const meta::SCALAR_FORMAT & PropertyScalar::GetFormat() const
    {
        return _Format;
    }

    //--------------------------------------------------------------------------------------------//

    const char * PropertyScalar::GetObject() const
    {
        return _Object;
    }

    //--------------------------------------------------------------------------------------------//

    char * PropertyScalar::GetObject()
    {
        return _Object;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyScalar::SetValue(char * scalar_object)
    {
        COFFEE_Assert(_Object != NULL, core::ERROR_CODE_IncorrectUsage,
            "Failed to set value on NULL property");
        COFFEE_Copy(_Object, scalar_object, meta::SCALAR_FORMAT_GetFormatSize(_Format));
    }

    //--------------------------------------------------------------------------------------------//

    void PropertyScalar::Create()
    {
        COFFEE_Assert(_Format != meta::SCALAR_FORMAT_None, core::ERROR_CODE_IncorrectUsage,
            "Property creation failed");
        Destroy();
        _Object = (char *) COFFEE_Allocate(meta::SCALAR_FORMAT_GetFormatSize(_Format));
    }

    //--------------------------------------------------------------------------------------------//

    void PropertyScalar::Destroy()
    {
        if(_Object != NULL)
        {
            COFFEE_Free(_Object);
            _Object = NULL;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void PropertyScalar::Serialize(coffee::meta::Stream& stream)
    {
        COFFEE_SerializeScalar(&_Format, int32);

        if (stream.GetMode()==storage::MODE_Input)
            Create();

        COFFEE_SerializeScalarFormat(_Object, _Format);
    }

}
}
