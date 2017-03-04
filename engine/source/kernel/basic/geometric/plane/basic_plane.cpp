#include "kernel/basic/geometric/plane/basic_plane.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::Plane);
        COFFEE_Attribute(basic::Vector4, Vect, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Plane::Plane() :
        Vect(0.0f, 1.0f, 0.0f, 0.0f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Plane::Plane(const Plane& other) :
        Vect(other.Vect)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Plane::Plane(const Vector4& vect) :
        Vect(vect)
    {
        COFFEE_Assert(GetNormal().IsNormalized(), core::ERROR_CODE_IncorrectUsage, "normal is not normalized");
    }

    //--------------------------------------------------------------------------------------------//

    Plane::Plane(const Vector3& position, const Vector3& normal)
    {
        COFFEE_Assert(normal.IsNormalized(), core::ERROR_CODE_IncorrectUsage, "normal is not normalized");
        Vect.Set(normal, normal.GetDotProduct(position));
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    Plane& Plane::operator = (const Plane& other)
    {
        Vect = other.Vect;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Plane& Plane::operator = (const Vector4& vect)
    {
        Vect = vect;
        COFFEE_Assert(GetNormal().IsNormalized(), core::ERROR_CODE_IncorrectUsage, "normal is not normalized");
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Plane& Plane::operator *=(const Matrix& transform)
    {
        Vector3 normal = GetNormal()*transform;
        normal.Normalize();
        Vect.Set(normal, Vect.W);
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Plane Plane::operator *(const Matrix& transform) const
    {
        Plane plane(*this);
        plane *= transform;
        return plane;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    Vector3 Plane::GetNormal() const
    {
        return Vector3(Vect.X, Vect.Y, Vect.Z);
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Plane::GetPoint() const
    {
        return GetNormal()*Vect.W;
    }

    //--------------------------------------------------------------------------------------------//

    bool Plane::FindLineIntersection(Vector3& point, const Line3& line) const
    {
        Vector3 plane_normal(GetNormal());
        Vector3 ray_position(line.Point);
        Vector3 ray_direction(line.Axis);
        real dot, t;

        dot = plane_normal.GetDotProduct(ray_direction);
        if (IsEqual(dot, 0.0f))
            return false;

        t = plane_normal.GetDotProduct(plane_normal*Vect.W - ray_position) / dot;
        point = ray_position + ray_direction*t;
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Plane::FindRayIntersection(Vector3& point, const Ray3& ray, bool it_has_to_cull) const
    {
        Vector3 plane_normal(GetNormal());
        Vector3 ray_position(ray.Origin);
        Vector3 ray_direction(ray.Direction);
        real t, dot;

        dot = plane_normal.GetDotProduct(ray_direction);

        if (it_has_to_cull)
        {
            if (dot >= -RealPrecision)
                return false;
        }
        else
        {
            if (IsEqual(dot, 0.0f))
                return false;
        }

        t = plane_normal.GetDotProduct(plane_normal*Vect.W - ray_position) / dot;
        if (t<0.0f)
            return false;

        point = ray_position + ray_direction*t;
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Plane::FindSegmentIntersection(Vector3& point, const Segment3& segment, bool it_has_to_cull) const
    {
        Vector3 plane_normal(GetNormal());
        Vector3 segment_position(segment.A);
        Vector3 segment_direction(segment.GetDirection());
        real dot, t;

        if (segment_direction.IsZero())
            return false;

        segment_direction.Normalize();
        dot = plane_normal.GetDotProduct(segment_direction);

        if (it_has_to_cull)
        {
            if (dot>=-RealPrecision)
                return false;
        }
        else
        {
            if (IsEqual(dot, 0.0f))
                return false;
        }

        t = plane_normal.GetDotProduct(plane_normal*Vect.W - segment_position) / dot;
        if (t<0.0f || t>=segment.GetLength())
            return false;

        point = segment_position + segment_direction*t;
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    real Plane::ComputeDistanceFromPoint(const Vector3& point) const
    {
        return GetNormal().GetDotProduct(point)-Vect.W;
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Plane::ComputeProjectedPoint(const Vector3& point) const
    {
        real distance_from_point = ComputeDistanceFromPoint(point);
        return point-GetNormal()*distance_from_point;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Plane::Set(const Vector3& position, const Vector3& normal)
    {
        COFFEE_Assert(normal.IsNormalized(), core::ERROR_CODE_IncorrectUsage, "normal is not normalized");
        Vect.Set(normal, normal.GetDotProduct(position));
    }

}
}
