#ifndef _COFFEE_BASIC_MATH_EULER_H_
#define _COFFEE_BASIC_MATH_EULER_H_

#include "coffee_includes.h"
#include "kernel/basic/math/quaternion/basic_quaternion.h"
#include "kernel/basic/math/matrix/basic_matrix.h"
#include "kernel/basic/math/angle/basic_angle.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Euler angles
    ///
    /// Rotation class based on three axis angles, working in radians in the [0,2pi[ range
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Euler : public meta::Object
    {
        COFFEE_Type(Euler);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        /// Construct a zero rotation instance
        Euler();

        /// Construct copying other
        Euler(const Euler& other);

        /// Construct using given rotations
        Euler(const Angle& x, const Angle& y, const Angle& z);

        /// Construct with extracted quaternion angles
        Euler(const Quaternion& quaternion);

        //-OPERATORS------------------------------------------------------------------------------//

        /// Assign the other value
        Euler& operator = (const Euler& other);

        /// Extract euler from quaternion
        Euler& operator = (const Quaternion& quaternion);

        /// Add other to self
        Euler& operator += (const Euler& other);

        /// Substract other to self
        Euler& operator -= (const Euler& other);

        /// Create an instance which is the sum of self and other
        Euler operator + (const Euler& other);
        
        /// Create an instance which is the difference of self and other
        Euler operator - (const Euler& other);
        
        /// Check if self is equal to the other
        bool operator == (const Euler& other) const;
        
        /// Check if self is not equal to the other
        bool operator != (const Euler& other) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        /// Set angles givin three radian values
        void Set(real x, real y, real z);
        
        /// Set angles givin three degrees values
        void SetDegrees(real x, real y, real z);
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Angle X;    ///< 3. Bank / Psi / Roll
        Angle Y;    ///< 1. Heading / Theta / Yaw
        Angle Z;    ///< 2. Attitude / Phi / Pitch
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Euler);
}
}
#endif
