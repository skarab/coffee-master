#ifndef _COFFEE_BASIC_MATH_CURVE_BEZIER_H_
#define _COFFEE_BASIC_MATH_CURVE_BEZIER_H_

#include "coffee_includes.h"
#include "kernel/basic/math/curve/basic_curve_bezier_template.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Bezier curve template
    ///
    /// Bezier curve handling smooth interpolation between four templated points.
    //--------------------------------------------------------------------------------------------//
    template< typename type > \
    class COFFEE_TEMPLATE_API Bezier
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        /// Construct a zero length curve
        Bezier();

        /// Construct a bezier curve given four points
        Bezier(const type& p0, const type& p1, const type& p2, const type& p3);

        //-QUERIES--------------------------------------------------------------------------------//

        /// Get length of the curve using precision as number of segments
        real GetLength(uint32 precision=CurvePrecision) const;
        
        /// Get point on the curve at time between [0,1]
        type GetPoint(real time) const;

        /// Get tangent on the curve at time between [0,1]
        type GetTangent(real time) const;

        /// Get time of nearest point on the curve between [0,1]
        real GetNearestTime(const type& point, uint32 precision=CurvePrecision) const;

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        type _P0;
        type _P1;
        type _P2;
        type _P3;
    };
}
}

#include "kernel/basic/math/curve/basic_curve_bezier.hpp"

#endif
