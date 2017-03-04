#include "kernel/basic/property/basic_property_base.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::PropertyBase);
        COFFEE_Attribute(meta::Object *, _Object, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PropertyBase::PropertyBase() :
        _Type(NULL),
        _Object(NULL),
        _Flags(0)
    {
    }

    //--------------------------------------------------------------------------------------------//

    PropertyBase::PropertyBase(String name, const meta::Type * type) :
        _Name(name),
        _Type(type),
        _Object(NULL),
        _Flags(0)
    {
        _Create();
    }

    //--------------------------------------------------------------------------------------------//

    PropertyBase::~PropertyBase()
    {
        SetNull();
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void PropertyBase::SetName(const String& name)
    {
        _Name = name;
    }

    //--------------------------------------------------------------------------------------------//

    const String& PropertyBase::GetName() const
    {
        return _Name;
    }

    //--------------------------------------------------------------------------------------------//

    const meta::Type * PropertyBase::GetType() const
    {
        return _Type;
    }

    //--------------------------------------------------------------------------------------------//

    const meta::Object * PropertyBase::GetObject() const
    {
        return _Object;
    }

    //--------------------------------------------------------------------------------------------//

    meta::Object * PropertyBase::GetObject()
    {
        return _Object;
    }

    //--------------------------------------------------------------------------------------------//

    const char * PropertyBase::GetScalarObject() const
    {
        COFFEE_Assert(!IsNull(), core::ERROR_CODE_IncorrectUsage,
            "Trying to get scalar value from NULL property");

        return ((PropertyScalar *) _Object)->GetObject();
    }

    //--------------------------------------------------------------------------------------------//

    char * PropertyBase::GetScalarObject()
    {
        COFFEE_Assert(!IsNull(), core::ERROR_CODE_IncorrectUsage,
            "Trying to get scalar value from NULL property");

        return ((PropertyScalar *) _Object)->GetObject();
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool PropertyBase::IsScalar() const
    {
        return (_Type->GetInfo() == meta::TYPE_INFO_Scalar);
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyBase::IsMetaObject() const
    {
        return (_Type->GetInfo() == meta::TYPE_INFO_Class);
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyBase::IsNull() const
    {
        return (_Object == NULL);
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyBase::HasFlag(const PROPERTY_FLAG & flag) const
    {
        return ((_Flags & (uint32) flag) > 0);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyBase::SetScalarValue(char * scalar_object)
    {
        COFFEE_Assert(IsScalar(), core::ERROR_CODE_IncorrectUsage,
            "Trying to set scalar value on non-scalar property");

        if(IsNull())
            _Create();

        ((PropertyScalar *) _Object)->SetValue(scalar_object);
    }

    //--------------------------------------------------------------------------------------------//

    void PropertyBase::SetMetaObjectValue(const meta::Object & meta_object)
    {
        COFFEE_Assert(IsMetaObject(), core::ERROR_CODE_IncorrectUsage,
            "Trying to set object value on non-object property");

        if(IsNull())
            _Create();

        *_Object = meta_object;
    }

    //--------------------------------------------------------------------------------------------//

    void PropertyBase::SetNull()
    {
        if (_Object!=NULL)
        {
            COFFEE_Delete(_Object);
            _Object = NULL;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void PropertyBase::Serialize(coffee::meta::Stream& stream)
    {
        String meta_type_name;
        bool it_is_null(false);

        _Name.Serialize(stream);

        if (stream.GetMode()==storage::MODE_Output)
        {
            meta_type_name = _Type->GetName();
            it_is_null = IsNull();
        }

        meta_type_name.Serialize(stream);
        _Type = COFFEE_FindType(meta_type_name);

        // This kind of set the stream as corrupted, meaning class types of serialized properties
        // shouldn't be removed!
        if (_Type==NULL)
            return;

        COFFEE_SerializeScalar(&it_is_null, bool);

        if (!it_is_null)
        {
            if (stream.GetMode()==storage::MODE_Input)
                _Create();

            COFFEE_SerializeObject(*_Object);
        }

        COFFEE_SerializeScalar(&_Flags, uint32);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyBase::_Create()
    {
        SetNull();

        if(IsScalar())
        {
            _Object = COFFEE_New(PropertyScalar, ((const meta::Scalar *) _Type)->GetFormat());
        }
        else
        {
            _Object = _Type->CreateObject();
        }
    }

}
}
