#ifndef _COFFEE_BASIC_MATH_QUATERNION_H_
#define _COFFEE_BASIC_MATH_QUATERNION_H_

#include "coffee_includes.h"
#include "kernel/basic/math/vector/basic_vector3.h"
#include "kernel/basic/math/angle/basic_angle.h"

namespace coffee
{
namespace basic
{
    //-FORWARDS-----------------------------------------------------------------------------------//

    class Euler;
    class Matrix;

    //--------------------------------------------------------------------------------------------//
    /// Quaternion
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Quaternion : public meta::Object
    {
        COFFEE_Type(Quaternion);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        /// Construct defining a zero rotation
        Quaternion();

        /// Construct copying other
        Quaternion(const Quaternion& other);

        /// Construct using quaternion internal values
        Quaternion(real x, real y, real z, real w);

        /// Construct from given euler
        Quaternion(const Euler& euler);

        /// Construct using extracted rotation from matrix
        Quaternion(const Matrix& matrix);

        //-OPERATORS------------------------------------------------------------------------------//

        /// Assign the other value
        Quaternion& operator = (const Quaternion& other);

        /// Assign the euler angles
        Quaternion& operator = (const Euler& euler);

        /// Assign the extracted rotation from matrix
        Quaternion& operator = (const Matrix& matrix);

        /// Transform using other rotation
        Quaternion& operator *= (const Quaternion& other);

        /// Get the inverse rotation
        Quaternion operator ~ () const;
        
        /// Create the transform product of two rotations
        Quaternion operator * (const Quaternion& other) const;

        /// Create the rotated vector
        Vector3 operator * (const Vector3& vector) const;

        /// Check if self is equal to other
        bool operator == (const Quaternion& other) const;

        /// Check if self is not equal to other
        bool operator != (const Quaternion& other) const;

        //-QUERIES--------------------------------------------------------------------------------//

        /// Extract X axis from the rotation
        Vector3 GetXAxis() const;

        /// Extract Y axis from the rotation
        Vector3 GetYAxis() const;

        /// Extract Z axis from the rotation
        Vector3 GetZAxis() const;

        /// Compute the square norm
        real GetSquareNorm() const;

        /// Compute the norm
        real GetNorm() const;

        /// Compute the dot product with other
        real GetDotProduct(const Quaternion& other) const;
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        /// Normalize the quaternion
        void Normalize();
        
        /// Set the rotation from a Z axis, using world Y axis as up vector
        void SetFromZAxis(const Vector3& z_axis);

        /// Set from given rotation angle around an axis
        void SetFromAxisAndAngle(const Vector3& axis, const Angle& angle);

        /// Set from given rotation angle around world X axis
        void SetFromXRotation(const Angle& angle);

        /// Set from given rotation angle around world Y axis
        void SetFromYRotation(const Angle& angle);

        /// Set from given rotation angle around world Z axis
        void SetFromZRotation(const Angle& angle);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        real X;
        real Y;
        real Z;
        real W;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Quaternion);
}
}
#endif
