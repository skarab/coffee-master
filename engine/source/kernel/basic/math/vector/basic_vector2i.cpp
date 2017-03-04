#include "kernel/basic/math/vector/basic_vector2i.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::Vector2i);
        COFFEE_Attribute(int32, X, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(int32, Y, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//
    
    Vector2i::Vector2i(int32 value) :
        X(value),
        Y(value)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Vector2i::Vector2i(int32 x, int32 y) :
        X(x),
        Y(y)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Vector2i::Vector2i(const Vector2i& vector) :
        X(vector.X),
        Y(vector.Y)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Vector2i::Vector2i(const Vector2& vector) :
        X((int32)vector.X),
        Y((int32)vector.Y)
    {
    }

    //-OPERATORS----------------------------------------------------------------------------------//
    
    Vector2i& Vector2i::operator = (int32 value)
    {
        X = value;
        Y = value;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector2i& Vector2i::operator = (const Vector2i& vector)
    {
        X = vector.X;
        Y = vector.Y;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector2i& Vector2i::operator += (int32 value)
    {
        X += value;
        Y += value;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector2i& Vector2i::operator += (const Vector2i& vector)
    {
        X += vector.X;
        Y += vector.Y;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector2i& Vector2i::operator -= (int32 value)
    {
        X -= value;
        Y -= value;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector2i& Vector2i::operator -= (const Vector2i& vector)
    {
        X -= vector.X;
        Y -= vector.Y;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector2i& Vector2i::operator *= (int32 value)
    {
        X *= value;
        Y *= value;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector2i& Vector2i::operator *= (const Vector2i& vector)
    {
        X *= vector.X;
        Y *= vector.Y;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector2i& Vector2i::operator /= (int32 value)
    {
        COFFEE_Assert(value!=0, core::ERROR_CODE_IncorrectUsage, "Zero division");
        X /= value;
        Y /= value;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector2i& Vector2i::operator /= (const Vector2i& vector)
    {
        COFFEE_Assert(vector.X!=0 && vector.Y!=0, core::ERROR_CODE_IncorrectUsage, "Zero division");
        X /= vector.X;
        Y /= vector.Y;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector2i Vector2i::operator + (int32 value) const
    {
        return Vector2i(X+value, Y+value);
    }

    //--------------------------------------------------------------------------------------------//

    Vector2i Vector2i::operator + (const Vector2i& vector) const
    {
        return Vector2i(X+vector.X, Y+vector.Y);
    }

    //--------------------------------------------------------------------------------------------//

    Vector2i Vector2i::operator - () const
    {
        return Vector2i(-X, -Y);
    }

    //--------------------------------------------------------------------------------------------//

    Vector2i Vector2i::operator - (int32 value) const
    {
        return Vector2i(X-value, Y-value);
    }

    //--------------------------------------------------------------------------------------------//

    Vector2i Vector2i::operator - (const Vector2i& vector) const
    {
        return Vector2i(X-vector.X, Y-vector.Y);
    }

    //--------------------------------------------------------------------------------------------//

    Vector2i Vector2i::operator * (int32 value) const
    {
        return Vector2i(X*value, Y*value);
    }

    //--------------------------------------------------------------------------------------------//

    Vector2i Vector2i::operator * (const Vector2i& vector) const
    {
        return Vector2i(X*vector.X, Y*vector.Y);
    }

    //--------------------------------------------------------------------------------------------//

    Vector2i Vector2i::operator / (int32 value) const
    {
        COFFEE_Assert(value!=0, core::ERROR_CODE_IncorrectUsage, "Zero division");
        return Vector2i(X/value, Y/value);
    }

    //--------------------------------------------------------------------------------------------//

    Vector2i Vector2i::operator / (const Vector2i& vector) const
    {
        COFFEE_Assert(vector.X!=0 && vector.Y!=0, core::ERROR_CODE_IncorrectUsage, "Zero division");
        return Vector2i(X/vector.X, Y/vector.Y);
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector2i::operator == (const Vector2i& vector) const
    {
        return (X==vector.X) && (Y==vector.Y);
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector2i::operator != (const Vector2i& vector) const
    {
        return (X!=vector.X) || (Y!=vector.Y);
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector2i::operator > (const Vector2i& vector) const
    {
        return (X>vector.X) && (Y>vector.Y);
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector2i::operator < (const Vector2i& vector) const
    {
        return (X<vector.X) && (Y<vector.Y);
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector2i::operator >= (const Vector2i& vector) const
    {
        return (X>=vector.X) && (Y>=vector.Y);
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector2i::operator <= (const Vector2i& vector) const
    {
        return (X<=vector.X) && (Y<=vector.Y);
    }

    //--------------------------------------------------------------------------------------------//

    const int32& Vector2i::operator [](uint32 component_index) const
    {
        COFFEE_Assert(component_index>=0 && component_index<=1, core::ERROR_CODE_IncorrectUsage, "Bad component index");
        return (&X)[component_index];
    }

    //--------------------------------------------------------------------------------------------//

    int32& Vector2i::operator [](uint32 component_index)
    {
        COFFEE_Assert(component_index>=0 && component_index<=1, core::ERROR_CODE_IncorrectUsage, "Bad component index");
        return (&X)[component_index];
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Vector2i::Set(int32 x, int32 y)
    {
        X = x;
        Y = y;
    }

}
}
