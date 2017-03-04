#include "kernel/basic/geometric/line/basic_line3.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::Line3);
        COFFEE_Attribute(basic::Vector3, Point, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Vector3, Axis, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Line3::Line3() :
        Point(),
        Axis(Vector3::XAxis)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Line3::Line3(const Line3& other) :
        Point(other.Point),
        Axis(other.Axis)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Line3::Line3(const Vector3& point, const Vector3& axis) :
        Point(point),
        Axis(axis)
    {
        COFFEE_Assert(Axis.IsNormalized(), core::ERROR_CODE_IncorrectUsage, "Axis is not normalized");
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    Line3& Line3::operator = (const Line3& other)
    {
        Point = other.Point;
        Axis = other.Axis;
        return *this;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    real Line3::ComputeDistanceFromPoint(const Vector3& point) const
    {
        return point.GetDistance(ComputeProjectedPoint(point));
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Line3::ComputeProjectedPoint(const Vector3& point) const
    {
        Vector3 a = Point;
        Vector3 b = Point+Axis;
        real l2 = a.GetSquareDistance(b);
        if (IsEqual(l2, 0.0f))
            return a;
        real t = (point-a).GetDotProduct(b-a)/l2;
        return a+(b-a)*t;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//
    
    void Line3::Set(const Vector3& point, const Vector3& axis)
    {
        COFFEE_Assert(axis.IsNormalized(), core::ERROR_CODE_IncorrectUsage, "Axis is not normalized");
        Point = point;
        Axis = axis;
    }

    //--------------------------------------------------------------------------------------------//

    void Line3::SetFromPoints(const Vector3& point_a, const Vector3& point_b)
    {
        COFFEE_Assert(point_a!=point_b, core::ERROR_CODE_IncorrectUsage, "Cant set the line with two identical points");
        Point = point_a;
        Axis = point_b - point_a;
        Axis.Normalize();
    }

}
}
