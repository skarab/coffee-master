//------------------------------------------------------------------------------------------------//
/// @file kernel/meta/type/scalar/meta_scalar.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "kernel/meta/type/scalar/meta_scalar.h"
#include "kernel/core/core.h"
#include "kernel/meta/meta_types.h"
#include "kernel/basic/alpha/basic_alpha.h"
#include "kernel/storage/storage.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
namespace meta
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Scalar::Scalar(basic::String name) :
        Type(TYPE_INFO_Scalar)
    {
        // parse namespace
        basic::String type_name(name);
        if(type_name.GetLength()>8 && type_name.GetLeft(8)=="coffee::")
        {
            type_name.CutLeft(8);
        }
        SetName(type_name);

        _Format = SCALAR_FORMAT_GetFormat(name);
        SetSize(SCALAR_FORMAT_GetFormatSize(_Format));

        COFFEE_Assert(_Format != SCALAR_FORMAT_None, core::ERROR_CODE_MetaSystem,
            "Failed to register scalar object");
    }

    //--------------------------------------------------------------------------------------------//

    Scalar::~Scalar()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const SCALAR_FORMAT & Scalar::GetFormat() const
    {
        return _Format;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    Object * Scalar::CreateObject() const
    {
        return (Object *) COFFEE_Allocate(GetSize());
    }

    //--------------------------------------------------------------------------------------------//

    void Scalar::Serialize(Stream& stream)
    {
        if (stream.GetMode()==storage::MODE_Output)
        {
            storage::Data data;
            data.Resize(_Size);
            COFFEE_Copy(data.GetBuffer(), stream.GetObject(), _Size);
            stream.GetStream().Push(data);
        }
        else
        {
            COFFEE_Copy(stream.GetObject(), stream.GetStream().Pop(_Size), _Size);
        }
    }

}
}
//------------------------------------------------------------------------------------------------//
