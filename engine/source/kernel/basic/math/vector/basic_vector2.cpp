#include "kernel/basic/math/vector/basic_vector2.h"
#include "kernel/basic/math/vector/basic_vector2i.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::Vector2);
        COFFEE_Attribute(real, X, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, Y, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Vector2::Vector2(real value) :
        X(value),
        Y(value)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Vector2::Vector2(real x, real y) :
        X(x),
        Y(y)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Vector2::Vector2(const Vector2& other) :
        X(other.X),
        Y(other.Y)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Vector2::Vector2(const Vector2i& other) :
        X((real)other.X),
        Y((real)other.Y)
    {
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    Vector2& Vector2::operator = (real value)
    {
        X = value;
        Y = value;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector2& Vector2::operator = (const Vector2& other)
    {
       X = other.X;
       Y = other.Y;
       return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector2& Vector2::operator += (real value)
    {
        X += value;
        Y += value;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector2& Vector2::operator += (const Vector2& other)
    {
        X += other.X;
        Y += other.Y;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector2& Vector2::operator -= (real value)
    {
        X -= value;
        Y -= value;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector2& Vector2::operator -= (const Vector2& other)
    {
        X -= other.X;
        Y -= other.Y;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector2& Vector2::operator *= (real value)
    {
        X *= value;
        Y *= value;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector2& Vector2::operator *= (const Vector2& other)
    {
        X *= other.X;
        Y *= other.Y;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector2& Vector2::operator /= (real value)
    {
        COFFEE_Assert(!IsEqual(value, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        X /= value;
        Y /= value;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector2& Vector2::operator /= (const Vector2& other)
    {
        COFFEE_Assert(!IsEqual(other.X, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        COFFEE_Assert(!IsEqual(other.Y, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        X /= other.X;
        Y /= other.Y;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector2 Vector2::operator + (real value) const
    {
        return Vector2(X+value, Y+value);
    }

    //--------------------------------------------------------------------------------------------//

    Vector2 Vector2::operator + (const Vector2& other) const
    {
        return Vector2(X+other.X, Y+other.Y);
    }

    //--------------------------------------------------------------------------------------------//

    Vector2 Vector2::operator - () const
    {
        return Vector2(-X, -Y);
    }

    //--------------------------------------------------------------------------------------------//

    Vector2 Vector2::operator - (real value) const
    {
        return Vector2(X-value, Y-value);
    }

    //--------------------------------------------------------------------------------------------//

    Vector2 Vector2::operator - (const Vector2& other) const
    {
        return Vector2(X-other.X, Y-other.Y);
    }

    //--------------------------------------------------------------------------------------------//

    Vector2 Vector2::operator * (real value) const
    {
        return Vector2(X*value, Y*value);
    }

    //--------------------------------------------------------------------------------------------//

    Vector2 Vector2::operator * (const Vector2& other) const
    {
        return Vector2(X*other.X, Y*other.Y);
    }

    //--------------------------------------------------------------------------------------------//

    Vector2 Vector2::operator / (real value) const
    {
        COFFEE_Assert(!IsEqual(value, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        return Vector2(X/value, Y/value);
    }

    //--------------------------------------------------------------------------------------------//

    Vector2 Vector2::operator / (const Vector2& other) const
    {
        COFFEE_Assert(!IsEqual(other.X, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        COFFEE_Assert(!IsEqual(other.Y, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        return Vector2(X/other.X, Y/other.Y);
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector2::operator == (const Vector2& other) const
    {
        return IsEqual(X, other.X) && IsEqual(Y, other.Y);
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector2::operator != (const Vector2& other) const
    {
        return IsNotEqual(X, other.X) || IsNotEqual(Y, other.Y);
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector2::operator > (const Vector2& other) const
    {
        return (X>other.X) && (Y>other.Y);
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector2::operator >= (const Vector2& other) const
    {
        return (X>=other.X) && (Y>=other.Y);
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector2::operator < (const Vector2& other) const
    {
        return (X<other.X) && (Y<other.Y);
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector2::operator <= (const Vector2& other) const
    {
        return (X<=other.X) && (Y<=other.Y);
    }

    //--------------------------------------------------------------------------------------------//

    const real& Vector2::operator [](uint32 component_index) const
    {
        COFFEE_Assert(component_index>=0 && component_index<=1, core::ERROR_CODE_IncorrectUsage, "Bad component index");
        return (&X)[component_index];
    }

    //--------------------------------------------------------------------------------------------//

    real& Vector2::operator [](uint32 component_index)
    {
        COFFEE_Assert(component_index>=0 && component_index<=1, core::ERROR_CODE_IncorrectUsage, "Bad component index");
        return (&X)[component_index];
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Vector2::Set(real x, real y)
    {
        X = x;
        Y = y;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    real Vector2::GetSquareNorm() const
    {
        return X*X + Y*Y;
    }

    //--------------------------------------------------------------------------------------------//

    real Vector2::GetNorm() const
    {
        return Sqrt(GetSquareNorm());
    }

    //--------------------------------------------------------------------------------------------//

    real Vector2::GetDotProduct(const Vector2& other) const
    {
        return X*other.X + Y*other.Y;
    }

    //--------------------------------------------------------------------------------------------//

    real Vector2::GetCrossProduct(const Vector2& other) const
    {
        return X*other.Y - Y*other.X;
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector2::IsZero() const
    {
        return IsEqual(X, 0.0f) && IsEqual(Y, 0.0f);
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector2::IsNormalized() const
    {
        return IsEqual(GetSquareNorm(), 1.0f);
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector2::IsColinear(const Vector2& other) const
    {
        return IsEqual(Absolute(GetDotProduct(other)), 1.0f);
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector2::IsOrthogonal(const Vector2& other) const
    {
        return IsEqual(GetDotProduct(other), 0.0f);
    }

    //--------------------------------------------------------------------------------------------//

    Vector2 Vector2::GetOrthogonal(bool it_is_clock_wise) const
    {
        if (it_is_clock_wise)
            return Vector2(Y, -X);
        return Vector2(-Y, X);
    }

    //--------------------------------------------------------------------------------------------//

    Angle Vector2::GetAngle() const
    {
        return ATan2(Y, X);
    }

    //--------------------------------------------------------------------------------------------//

    Angle Vector2::GetAngle(const Vector2& other) const
    {
        return other.GetAngle()-GetAngle();
    }

    //--------------------------------------------------------------------------------------------//

    real Vector2::GetSquareDistance(const Vector2& point) const
    {
        return (*this-point).GetSquareNorm();
    }

    //--------------------------------------------------------------------------------------------//

    real Vector2::GetDistance(const Vector2& point) const
    {
        return (*this-point).GetNorm();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Vector2::Normalize()
    {
        real norm = GetNorm();
        COFFEE_Assert(!IsEqual(norm, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        *this /= norm;
    }

}
}
//------------------------------------------------------------------------------------------------//
