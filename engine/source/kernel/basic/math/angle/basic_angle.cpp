#include "kernel/basic/math/angle/basic_angle.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::Angle);
        COFFEE_Attribute(real, _Value, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Angle::Angle() :
        _Value(0.0f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Angle::Angle(real value) :
        _Value(value)
    {
        _Normalize();
    }

    //--------------------------------------------------------------------------------------------//

    Angle::Angle(const Angle& other) :
        _Value(other._Value)
    {
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    Angle& Angle::operator = (real value)
    {
        _Value = value;
        _Normalize();
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Angle& Angle::operator = (const Angle& other)
    {
        _Value = other._Value;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Angle& Angle::operator += (const Angle& other)
    {
        _Value += other._Value;
        _Normalize();
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Angle& Angle::operator -= (const Angle& other)
    {
        _Value -= other._Value;
        _Normalize();
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Angle& Angle::operator *= (const Angle& other)
    {
        _Value *= other._Value;
        _Normalize();
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Angle& Angle::operator /= (const Angle& other)
    {
        COFFEE_Assert(!IsEqual(other._Value, 0.0f), core::ERROR_CODE_IncorrectUsage, "Divide per zero");
        _Value /= other._Value;
        _Normalize();
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Angle Angle::operator + (const Angle& other) const
    {
        return Angle(_Value + other._Value);
    }

    //--------------------------------------------------------------------------------------------//

    Angle Angle::operator - (const Angle& other) const
    {
        return Angle(_Value - other._Value);
    }

    //--------------------------------------------------------------------------------------------//

    Angle Angle::operator - () const
    {
        return Angle(-_Value);
    }

    //--------------------------------------------------------------------------------------------//

    Angle Angle::operator * (const Angle& other) const
    {
        return Angle(_Value * other._Value);
    }

    //--------------------------------------------------------------------------------------------//

    Angle Angle::operator / (const Angle& other) const
    {
        COFFEE_Assert(!IsEqual(other._Value, 0.0f), core::ERROR_CODE_IncorrectUsage, "Divide per zero");
        return Angle(_Value / other._Value);
    }

    //--------------------------------------------------------------------------------------------//

    bool Angle::operator == (const Angle& other) const
    {
        return IsEqual(_Value, other._Value);
    }

    //--------------------------------------------------------------------------------------------//

    bool Angle::operator != (const Angle& other) const
    {
        return !(*this==other);
    }

    //--------------------------------------------------------------------------------------------//

    bool Angle::operator < (const Angle& other) const
    {
        return _Value<other._Value;
    }

    //--------------------------------------------------------------------------------------------//

    bool Angle::operator > (const Angle& other) const
    {
        return _Value>other._Value;
    }

    //--------------------------------------------------------------------------------------------//

    bool Angle::operator <= (const Angle& other) const
    {
        return _Value<=other._Value;
    }

    //--------------------------------------------------------------------------------------------//

    bool Angle::operator >= (const Angle& other) const
    {
        return _Value>=other._Value;
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    real Angle::Get() const
    {
        return _Value;
    }

    //--------------------------------------------------------------------------------------------//

    void Angle::SetDegrees(real value)
    {
        _Value = value * Pi / 180.0f;
        _Normalize();
    }

    //--------------------------------------------------------------------------------------------//

    real Angle::GetDegrees() const
    {
        return _Value * 180.0f / Pi;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    real Angle::GetCosinus() const
    {
        return Cos(_Value);
    }

    //--------------------------------------------------------------------------------------------//

    real Angle::GetSinus() const
    {
        return Sin(_Value);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Angle::_Normalize()
    {
        if (_Value>=Pi*2.0f)
        {
            // Adjust if upper
            _Value = _Value - Floor(_Value/(Pi*2.0f))*Pi*2.0f;
        }
        else if (_Value<0.0f)
        {
            // Adjust if under
            _Value = _Value + Ceil(_Value/(-Pi*2.0f))*Pi*2.0f;
        }

        // Adjust to the real precision
        if (_Value<RealPrecision || _Value>=Pi*2.0f-RealPrecision)
            _Value = 0.0f;
    }

}
}
