#ifndef _COFFEE_BASIC_GEOMETRIC_SEGMENT3_H_
#define _COFFEE_BASIC_GEOMETRIC_SEGMENT3_H_

#include "coffee_includes.h"
#include "kernel/basic/math/basic_math.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Simple segment in 3D
    ///
    /// Segment is defined by two points aka Vector3.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Segment3 : public meta::Object
    {
        COFFEE_Type(Segment3);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        /// Construct a zero segment
        Segment3();

        /// Construct copying existing segment
        Segment3(const Segment3& other);

        /// Construct the segment defined by [a, b]
        Segment3(const Vector3& a, const Vector3& b);

        //-OPERATORS------------------------------------------------------------------------------//

        /// Assign values from other segment
        Segment3& operator = (const Segment3& other);

        //-QUERIES--------------------------------------------------------------------------------//

        /// Get the normalized segment direction, from a to b
        Vector3 GetDirection() const;

        /// Get the fast square length of the segment
        real GetSquareLength() const;

        /// Get the length of the segment
        real GetLength() const;

        /// Check if the segment is zero
        bool IsZero() const;

        /// Compute the smallest distance of a point to the line
        real ComputeDistanceFromPoint(const Vector3& point) const;

        /// Compute the projected point on the line
        Vector3 ComputeProjectedPoint(const Vector3& point) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        /// Set from [a, b]
        void Set(const Vector3& a, const Vector3& b);

        /// Set from origin, normalized direction and length
        void SetFromDirection(const Vector3& origin, const Vector3& direction, real length);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Vector3 A;
        Vector3 B;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Segment3);
}
}
#endif
