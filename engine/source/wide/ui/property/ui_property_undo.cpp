#include "wide/ui/property/ui_property_undo.h"

namespace coffee
{
namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PropertyUndo::PropertyUndo(meta::Object* object, void* property, const meta::Type& type) :
        _Object(object),
        _Property(property),
        _Type(type),
        _Value(NULL)
    {
        _Value = _Type.CreateObject();
           
        if (_Type.GetInfo()==meta::TYPE_INFO_Class)
        {
            _Value->Copy(*_Value->CastObject(_Property));
        }
        else
        {
            COFFEE_Copy(_Value, _Property,
                meta::SCALAR_FORMAT_GetFormatSize(static_cast<const meta::Scalar&>(_Type).GetFormat()));
        }
    }

    //--------------------------------------------------------------------------------------------//

    PropertyUndo::~PropertyUndo()
    {
        if (_Type.GetInfo()==meta::TYPE_INFO_Class)
        {
            COFFEE_Delete(_Value);
        }
        else
        {
            COFFEE_Free(_Value);
        }
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    bool PropertyUndo::operator==(const PropertyUndo& undo) const
    {
        return _Object==undo._Object
            && _Property==undo._Property;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyUndo::Undo()
    {
        _UpdateValue();
    }

    //--------------------------------------------------------------------------------------------//

    void PropertyUndo::Redo()
    {
        _UpdateValue();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyUndo::_UpdateValue()
    {
        meta::Object* value = _Type.CreateObject();
        if (_Type.GetInfo()==meta::TYPE_INFO_Class)
        {
            value->Copy(*_Value->CastObject(_Property));
            _Value->CastObject(_Property)->Copy(*_Value);
        }
        else
        {
            COFFEE_Copy(value, _Property,
                meta::SCALAR_FORMAT_GetFormatSize(static_cast<const meta::Scalar&>(_Type).GetFormat()));
            COFFEE_Copy(_Property, _Value,
                meta::SCALAR_FORMAT_GetFormatSize(static_cast<const meta::Scalar&>(_Type).GetFormat()));
        }
        if (_Type.GetInfo()==meta::TYPE_INFO_Class)
        {
            COFFEE_Delete(_Value);
        }
        else
        {
            COFFEE_Free(_Value);
        }
        _Value = value;
        _Object->OnPropertyModified(_Property);
    }

}
}
