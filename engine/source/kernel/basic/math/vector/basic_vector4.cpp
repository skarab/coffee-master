#include "kernel/basic/math/vector/basic_vector4.h"
#include "kernel/basic/math/matrix/basic_matrix.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::Vector4);
        COFFEE_Attribute(real, X, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, Y, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, Z, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, W, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Vector4::Vector4(real value) :
        X(value),
        Y(value),
        Z(value),
        W(value)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Vector4::Vector4(real x, real y, real z, real w) :
        X(x),
        Y(y),
        Z(z),
        W(w)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Vector4::Vector4(const Vector4& other) :
        X(other.X),
        Y(other.Y),
        Z(other.Z),
        W(other.W)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Vector4::Vector4(const Vector3& other) :
        X(other.X),
        Y(other.Y),
        Z(other.Z),
        W(1.0f)
    {
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    Vector4& Vector4::operator = (real value)
    {
        X = value;
        Y = value;
        Z = value;
        W = value;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector4& Vector4::operator = (const Vector4& other)
    {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        W = other.W;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector4& Vector4::operator = (const Vector3& other)
    {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        W = 1.0f;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector4& Vector4::operator += (real value)
    {
        X += value;
        Y += value;
        Z += value;
        W += value;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector4& Vector4::operator += (const Vector4& other)
    {
        X += other.X;
        Y += other.Y;
        Z += other.Z;
        W += other.W;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector4& Vector4::operator -= (real value)
    {
        X -= value;
        Y -= value;
        Z -= value;
        W -= value;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector4& Vector4::operator -= (const Vector4& other)
    {
        X -= other.X;
        Y -= other.Y;
        Z -= other.Z;
        W -= other.W;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector4& Vector4::operator *= (real value)
    {
        X *= value;
        Y *= value;
        Z *= value;
        W *= value;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector4& Vector4::operator *= (const Vector4& other)
    {
        X *= other.X;
        Y *= other.Y;
        Z *= other.Z;
        W *= other.W;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector4& Vector4::operator *= (const Matrix& matrix)
    {
        this->operator =(matrix**this);
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector4& Vector4::operator /= (real value)
    {
        COFFEE_Assert(!IsEqual(value, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        X /= value;
        Y /= value;
        Z /= value;
        W /= value;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector4& Vector4::operator /= (const Vector4& other)
    {
        COFFEE_Assert(!IsEqual(other.X, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        COFFEE_Assert(!IsEqual(other.Y, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        COFFEE_Assert(!IsEqual(other.Z, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        COFFEE_Assert(!IsEqual(other.W, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        X /= other.X;
        Y /= other.Y;
        Z /= other.Z;
        W /= other.W;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector4 Vector4::operator + (real value) const
    {
        return Vector4(X+value, Y+value, Z+value, W+value);
    }

    //--------------------------------------------------------------------------------------------//

    Vector4 Vector4::operator + (const Vector4& other) const
    {
        return Vector4(X+other.X, Y+other.Y, Z+other.Z, W+other.W);
    }

    //--------------------------------------------------------------------------------------------//

    Vector4 Vector4::operator - () const
    {
        return Vector4(-X, -Y, -Z, -W);
    }

    //--------------------------------------------------------------------------------------------//

    Vector4 Vector4::operator - (real value) const
    {
        return Vector4(X-value, Y-value, Z-value, W-value);
    }

    //--------------------------------------------------------------------------------------------//

    Vector4 Vector4::operator - (const Vector4& other) const
    {
        return Vector4(X-other.X, Y-other.Y, Z-other.Z, W-other.W);
    }

    //--------------------------------------------------------------------------------------------//

    Vector4 Vector4::operator * (real value) const
    {
        return Vector4(X*value, Y*value, Z*value, W*value);
    }

    //--------------------------------------------------------------------------------------------//

    Vector4 Vector4::operator * (const Vector4& other) const
    {
        return Vector4(X*other.X, Y*other.Y, Z*other.Z, W*other.W);
    }

    //--------------------------------------------------------------------------------------------//

    Vector4 Vector4::operator * (const Matrix& matrix) const
    {
        return matrix**this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector4 Vector4::operator / (real value) const
    {
        COFFEE_Assert(!IsEqual(value, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        return Vector4(X/value, Y/value, Z/value, W/value);
    }

    //--------------------------------------------------------------------------------------------//

    Vector4 Vector4::operator / (const Vector4& other) const
    {
        COFFEE_Assert(!IsEqual(other.X, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        COFFEE_Assert(!IsEqual(other.Y, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        COFFEE_Assert(!IsEqual(other.Z, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        COFFEE_Assert(!IsEqual(other.W, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        return Vector4(X/other.X, Y/other.Y, Z/other.Z, W/other.W);
    }

    //--------------------------------------------------------------------------------------------//

    const real& Vector4::operator[](uint32 component_index) const
    {
        return (&X)[component_index];
    }

    //--------------------------------------------------------------------------------------------//

    real& Vector4::operator[](uint32 component_index)
    {
        return (&X)[component_index];
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Vector4::Set(real x, real y, real z, real w)
    {
        X = x;
        Y = y;
        Z = z;
        W = w;
    }

    //--------------------------------------------------------------------------------------------//

    void Vector4::Set(const Vector3& other, float w)
    {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        W = w;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    real Vector4::GetSquareNorm() const
    {
        return X*X + Y*Y + Z*Z;
    }

    //--------------------------------------------------------------------------------------------//

    real Vector4::GetNorm() const
    {
        return Sqrt(GetSquareNorm());
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector4::IsZero() const
    {
        return IsEqual(X, 0.0f) && IsEqual(Y, 0.0f) && IsEqual(Z, 0.0f);
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector4::IsNormalized() const
    {
        return IsEqual(GetSquareNorm(), 1.0f);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Vector4::Normalize()
    {
        real norm = GetNorm();
        COFFEE_Assert(!IsEqual(norm, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        *this /= norm;
    }

}
}
//------------------------------------------------------------------------------------------------//
