#ifndef _COFFEE_BASIC_GEOMETRIC_LINE3_H_
#define _COFFEE_BASIC_GEOMETRIC_LINE3_H_

#include "coffee_includes.h"
#include "kernel/basic/math/basic_math.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Simple line in 3D
    ///
    /// Line is defined by a point an an axis.
    /// The axis must be normalized.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Line3 : public meta::Object
    {
        COFFEE_Type(Line3);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        /// Construct a line from the X axis
        Line3();

        /// Construct copying existing line
        Line3(const Line3& other);

        /// Construct the line from point and normalized axis
        Line3(const Vector3& point, const Vector3& axis);

        //-OPERATORS------------------------------------------------------------------------------//

        /// Assign values from other line
        Line3& operator = (const Line3& other);

        //-QUERIES--------------------------------------------------------------------------------//

        /// Compute the smallest distance of a point to the line
        real ComputeDistanceFromPoint(const Vector3& point) const;

        /// Compute the projected point on the line
        Vector3 ComputeProjectedPoint(const Vector3& point) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        /// Set from point and normalized axis
        void Set(const Vector3& point, const Vector3& axis);

        /// Set from the line defined by (point_a, point_b)
        void SetFromPoints(const Vector3& point_a, const Vector3& point_b);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Vector3 Point;
        Vector3 Axis;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Line3);
}
}
#endif
