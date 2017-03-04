#include "kernel/basic/geometric/segment/basic_segment3.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::Segment3);
        COFFEE_Attribute(basic::Vector3, A, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Vector3, B, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Segment3::Segment3()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Segment3::Segment3(const Segment3& other) :
        A(other.A),
        B(other.B)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Segment3::Segment3(const Vector3& a, const Vector3& b) :
        A(a),
        B(b)
    {
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    Segment3& Segment3::operator = (const Segment3& other)
    {
        A = other.A;
        B = other.B;
        return *this;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    Vector3 Segment3::GetDirection() const
    {
        if (IsZero())
            return Vector3::Zero;

        Vector3 direction(B-A);
        direction.Normalize();
        return direction;
    }

    //--------------------------------------------------------------------------------------------//

    real Segment3::GetSquareLength() const
    {
        return (B-A).GetSquareNorm();
    }

    //--------------------------------------------------------------------------------------------//

    real Segment3::GetLength() const
    {
        return (B-A).GetNorm();
    }

    //--------------------------------------------------------------------------------------------//

    bool Segment3::IsZero() const
    {
        return IsEqual(GetSquareLength(), 0.0f);
    }

    //--------------------------------------------------------------------------------------------//

    real Segment3::ComputeDistanceFromPoint(const Vector3& point) const
    {
        return point.GetDistance(ComputeProjectedPoint(point));
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Segment3::ComputeProjectedPoint(const Vector3& point) const
    {
        real l2 = GetSquareLength();
        if (IsEqual(l2, 0.0f))
            return A;
        real t = (point-A).GetDotProduct(B-A)/l2;
        if (t<0.0f) return A;
        if (t>1.0f) return B;
        return A+(B-A)*t;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Segment3::Set(const Vector3& a, const Vector3& b)
    {
        A = a;
        B = b;
    }

    //--------------------------------------------------------------------------------------------//

    void Segment3::SetFromDirection(const Vector3& origin, const Vector3& direction, real length)
    {
        COFFEE_Assert(direction.IsNormalized(), core::ERROR_CODE_IncorrectUsage, "Axis is not normalized");
        A = origin;
        B = origin+direction*length;
    }

}
}
