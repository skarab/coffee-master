#ifndef _COFFEE_BASIC_GEOMETRIC_PLANE_H_
#define _COFFEE_BASIC_GEOMETRIC_PLANE_H_

#include "coffee_includes.h"
#include "kernel/basic/math/basic_math.h"
#include "kernel/basic/geometric/line/basic_line3.h"
#include "kernel/basic/geometric/ray/basic_ray3.h"
#include "kernel/basic/geometric/segment/basic_segment3.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Plane in 3D
    ///
    /// Plane is defined by a Vector4.
    /// X, Y, Z components are the plane normal, and W the distance from origin.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Plane : public meta::Object
    {
        COFFEE_Type(Plane);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        /// Construct a plane facing the Y axis at origin
        Plane();

        /// Construct a plane copying other
        Plane(const Plane& other);

        /// Construct a plane from given vect
        Plane(const Vector4& vect);

        /// Construct a plane from position and normalized normal
        Plane(const Vector3& position, const Vector3& normal);

        //-OPERATORS------------------------------------------------------------------------------//

        /// Assign values from other plane
        Plane& operator =(const Plane& other);

        /// Assign values from vect
        Plane& operator =(const Vector4& vect);

        /// Transform plane
        Plane& operator *=(const Matrix& transform);

        /// Get transformed plane
        Plane operator *(const Matrix& transform) const;
        
        //-QUERIES--------------------------------------------------------------------------------//

        /// Get the plane normal
        Vector3 GetNormal() const;

        /// Get a point on the plane
        Vector3 GetPoint() const;

        /// Compute the plane intersection with a line
        bool FindLineIntersection(Vector3& point, const Line3& line) const;

        /// Compute the plane intersection with a ray, using normal culling or not
        bool FindRayIntersection(Vector3& point, const Ray3& ray, bool it_has_to_cull=true) const;

        /// Compute the plane intersection with a segment, using normal culling or not
        bool FindSegmentIntersection(Vector3& point, const Segment3& segment, bool it_has_to_cull=true) const;
        
        /// Compute the smallest distance of a point to the plane, may be negative depending of side
        real ComputeDistanceFromPoint(const Vector3& point) const;

        /// Compute the projected point on the plane
        Vector3 ComputeProjectedPoint(const Vector3& point) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        /// Set the plane from position and normalized normal
        void Set(const Vector3& position, const Vector3& normal);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Vector4 Vect;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Plane);
}
}
#endif
