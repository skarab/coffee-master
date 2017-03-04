#include "kernel/basic/math/vector/basic_vector3.h"
#include "kernel/basic/math/matrix/basic_matrix.h"
#include "kernel/basic/math/quaternion/basic_quaternion.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::Vector3);
        COFFEE_Attribute(real, X, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, Y, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, Z, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Vector3::Vector3(real value) :
        X(value),
        Y(value),
        Z(value)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Vector3::Vector3(real x, real y, real z) :
        X(x),
        Y(y),
        Z(z)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Vector3::Vector3(const Vector3& other) :
        X(other.X),
        Y(other.Y),
        Z(other.Z)
    {
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    Vector3& Vector3::operator = (real value)
    {
        X = value;
        Y = value;
        Z = value;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector3& Vector3::operator = (const Vector3& other)
    {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector3& Vector3::operator += (real value)
    {
        X += value;
        Y += value;
        Z += value;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector3& Vector3::operator += (const Vector3& other)
    {
        X += other.X;
        Y += other.Y;
        Z += other.Z;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector3& Vector3::operator -= (real value)
    {
        X -= value;
        Y -= value;
        Z -= value;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector3& Vector3::operator -= (const Vector3& other)
    {
        X -= other.X;
        Y -= other.Y;
        Z -= other.Z;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector3& Vector3::operator *= (real value)
    {
        X *= value;
        Y *= value;
        Z *= value;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector3& Vector3::operator *= (const Vector3& other)
    {
        X *= other.X;
        Y *= other.Y;
        Z *= other.Z;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector3& Vector3::operator *= (const Matrix & matrix)
    {
        this->operator =(matrix**this);
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector3& Vector3::operator *= (const Quaternion & quaternion)
    {
        this->operator =(quaternion**this);
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector3& Vector3::operator /= (real value)
    {
        COFFEE_Assert(!IsEqual(value, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        X /= value;
        Y /= value;
        Z /= value;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector3& Vector3::operator /= (const Vector3& other)
    {
        COFFEE_Assert(!IsEqual(other.X, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        COFFEE_Assert(!IsEqual(other.Y, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        COFFEE_Assert(!IsEqual(other.Z, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        X /= other.X;
        Y /= other.Y;
        Z /= other.Z;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Vector3::operator + (real value) const
    {
        return Vector3(X+value, Y+value, Z+value);
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Vector3::operator + (const Vector3& other) const
    {
        return Vector3(X+other.X, Y+other.Y, Z+other.Z);
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Vector3::operator - () const
    {
        return Vector3(-X, -Y, -Z);
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Vector3::operator - (real value) const
    {
        return Vector3(X-value, Y-value, Z-value);
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Vector3::operator - (const Vector3& other) const
    {
        return Vector3(X-other.X, Y-other.Y, Z-other.Z);
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Vector3::operator * (real value) const
    {
        return Vector3(X*value, Y*value, Z*value);
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Vector3::operator * (const Vector3& other) const
    {
        return Vector3(X*other.X, Y*other.Y, Z*other.Z);
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Vector3::operator * (const Matrix& matrix) const
    {
        return matrix * *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Vector3::operator * (const Quaternion& quaternion) const
    {
        return quaternion * *this;
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Vector3::operator / (real value) const
    {
        COFFEE_Assert(!IsEqual(value, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        return Vector3(X/value, Y/value, Z/value);
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Vector3::operator / (const Vector3& other) const
    {
        COFFEE_Assert(!IsEqual(other.X, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        COFFEE_Assert(!IsEqual(other.Y, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        COFFEE_Assert(!IsEqual(other.Z, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        return Vector3(X/other.X, Y/other.Y, Z/other.Z);
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector3::operator == (const Vector3& other) const
    {
        return IsEqual(X, other.X) && IsEqual(Y, other.Y) && IsEqual(Z, other.Z);
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector3::operator != (const Vector3& other) const
    {
        return IsNotEqual(X, other.X) || IsNotEqual(Y, other.Y) || IsNotEqual(Z, other.Z);
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector3::operator > (const Vector3& other) const
    {
        return (X>other.X) && (Y>other.Y) && (Z>other.Z);
    }
    
    //--------------------------------------------------------------------------------------------//

    bool Vector3::operator >= (const Vector3& other) const
    {
        return (X>=other.X) && (Y>=other.Y) && (Z>=other.Z);
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector3::operator < (const Vector3& other) const
    {
        return (X<other.X) && (Y<other.Y) && (Z<other.Z);
    }
    
    //--------------------------------------------------------------------------------------------//

    bool Vector3::operator <= (const Vector3& other) const
    {
        return (X<=other.X) && (Y<=other.Y) && (Z<=other.Z);
    }

    //--------------------------------------------------------------------------------------------//

    const real& Vector3::operator[](uint32 component_index) const
    {
        COFFEE_Assert(component_index>=0 && component_index<=2, core::ERROR_CODE_IncorrectUsage, "Bad component index");
        return (&X)[component_index];
    }

    //--------------------------------------------------------------------------------------------//

    real& Vector3::operator[](uint32 component_index)
    {
        COFFEE_Assert(component_index>=0 && component_index<=2, core::ERROR_CODE_IncorrectUsage, "Bad component index");
        return (&X)[component_index];
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Vector3::Set(real x, real y, real z)
    {
        X = x;
        Y = y;
        Z = z;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    real Vector3::GetSquareNorm() const
    {
        return X*X + Y*Y + Z*Z;
    }

    //--------------------------------------------------------------------------------------------//

    real Vector3::GetNorm() const
    {
        return Sqrt(GetSquareNorm());
    }

    //--------------------------------------------------------------------------------------------//

    real Vector3::GetDotProduct(const Vector3& other) const
    {
        return (X*other.X)+(Y*other.Y)+(Z*other.Z);
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Vector3::GetCrossProduct(const Vector3& other) const
    {
        return Vector3(
            Y*other.Z - Z*other.Y,
            Z*other.X - X*other.Z,
            X*other.Y - Y*other.X);
    }

    //--------------------------------------------------------------------------------------------//

    Angle Vector3::GetAngle(const Vector3& other) const
    {
        Vector3 v1(*this);
        Vector3 v2(other);
        v1.Normalize();
        v2.Normalize();
        return Angle(ACos(v1.GetDotProduct(v2)));
    }

    //--------------------------------------------------------------------------------------------//

    real Vector3::GetSquareDistance(const Vector3& point) const
    {
        return (*this - point).GetSquareNorm();
    }

    //--------------------------------------------------------------------------------------------//

    real Vector3::GetDistance(const Vector3& point) const
    {
        return (*this - point).GetNorm();
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector3::IsZero() const
    {
        return IsEqual(X, 0.0f) && IsEqual(Y, 0.0f) && IsEqual(Z, 0.0f);
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector3::IsNormalized() const
    {
        return IsEqual(GetSquareNorm(), 1.0f);
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector3::IsColinear(const Vector3& other) const
    {
        return IsEqual(Absolute(GetDotProduct(other)), 1.0f);
    }

    //--------------------------------------------------------------------------------------------//

    bool Vector3::IsOrthogonal(const Vector3& other) const
    {
        return IsEqual(GetDotProduct(other), 0.0f);
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Vector3::GetOrthogonal(const Vector3& other) const
    {
        return GetCrossProduct(other);
    }

    //--------------------------------------------------------------------------------------------//

    real Vector3::GetMaximum() const
    {
        if (X>Y)
        {
            if (X>Z) return X;
            return Z;
        }
        if (Y>Z) return Y;
        return Z;
    }

    //--------------------------------------------------------------------------------------------//

    real Vector3::GetMinimum() const
    {
        if (X<Y)
        {
            if (X<Z) return X;
            return Z;
        }
        if (Y<Z) return Y;
        return Z;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Vector3::Normalize()
    {
        real norm = GetNorm();
        COFFEE_Assert(!IsEqual(norm, 0.0f), core::ERROR_CODE_IncorrectUsage, "Zero division");
        *this /= norm;
    }

    //-VARIABLES----------------------------------------------------------------------------------//

    const Vector3 Vector3::Zero = Vector3();
    const Vector3 Vector3::XAxis = Vector3(1.0f, 0.0f, 0.0f);
    const Vector3 Vector3::YAxis = Vector3(0.0f, 1.0f, 0.0f);
    const Vector3 Vector3::ZAxis = Vector3(0.0f, 0.0f, 1.0f);
    const Vector3 Vector3::One = Vector3(1.0f, 1.0f, 1.0f);
}
}
//------------------------------------------------------------------------------------------------//
