#ifndef _COFFEE_BASIC_MATH_VECTOR3_H_
#define _COFFEE_BASIC_MATH_VECTOR3_H_

#include "coffee_includes.h"
#include "kernel/basic/math/angle/basic_angle.h"
#include "kernel/basic/math/vector/basic_vector2.h"

namespace coffee
{
namespace basic
{
    //-FORWARDS-----------------------------------------------------------------------------------//

    class Matrix;
    class Quaternion;

    //--------------------------------------------------------------------------------------------//
    /// Vector with three real components
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Vector3 : public meta::Object
    {
        COFFEE_Type(Vector3);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        /// Construct assigning value to each components
        Vector3(real value=0.0f);
        
        /// Construct with specific component values
        Vector3(real x, real y, real z);
        
        /// Construct copying other
        Vector3(const Vector3& other);

        //-OPERATORS------------------------------------------------------------------------------//

        /// Assign the value to each components
        Vector3& operator = (real value);
        
        /// Assign values from other to each components
        Vector3& operator = (const Vector3& other);
        
        /// Add value to each components
        Vector3& operator += (real value);
        
        /// Add values from other to each components
        Vector3& operator += (const Vector3& other);
        
        /// Substract value to each components
        Vector3& operator -= (real value);
        
        /// Substract value from other to each components
        Vector3& operator -= (const Vector3& other);
        
        /// Multiply each components by value
        Vector3& operator *= (real value);
        
        /// Multiply each components by other values
        Vector3& operator *= (const Vector3& other);
        
        /// Transform by the matrix
        Vector3& operator *= (const Matrix& matrix);

        /// Rotate by the quaternion
        Vector3& operator *= (const Quaternion& quaternion);

        /// Divide each components by value        
        Vector3& operator /= (real value);
        
        /// Divide each components by other values        
        Vector3& operator /= (const Vector3& other);
        
        /// Create a vector which is the sum of self and value        
        Vector3 operator + (real value) const;
        
        /// Create a vector which is the sum of self and other
        Vector3 operator + (const Vector3& other) const;
        
        /// Get the opposite vector
        Vector3 operator - () const;
        
        /// Create a vector which is the difference of self and value
        Vector3 operator - (real value) const;
        
        /// Create a vector which is the difference of self and other
        Vector3 operator - (const Vector3& other) const;
        
        /// Create a vector which is the product of self and value
        Vector3 operator * (real value) const;
        
        /// Create a vector which is the product of self and other
        Vector3 operator * (const Vector3& other) const;
        
        /// Create a vector which is the transformed vector by matrix
        Vector3 operator * (const Matrix& matrix) const;
        
        /// Create a vector which is the rotated vector by quaternion
        Vector3 operator * (const Quaternion& quaternion) const;

        /// Create a vector which is the div of self and value
        Vector3 operator / (real value) const;
        
        /// Create a vector which is the div of self and other
        Vector3 operator / (const Vector3& other) const;
        
        /// Check if the vectors are equal        
        bool operator == (const Vector3& other) const;
        
        /// Check if the vectors are not equal      
        bool operator != (const Vector3& other) const;
        
        /// Check if both components are greater than the other vector components
        bool operator > (const Vector3& other) const;
        
        /// Check if both components are greater or equal to the other vector components
        bool operator >= (const Vector3& other) const;
        
        /// Check if both components are less than the other vector components
        bool operator < (const Vector3& other) const;
        
        /// Check if both components are less or equal to the other vector components
        bool operator <= (const Vector3& other) const;
        
        /// Get a specific component by index
        const real& operator[](uint32 component_index) const;
        
        /// Get a specific component access by index
        real& operator[](uint32 component_index);

        //-ACCESSORS------------------------------------------------------------------------------//

        /// Assign component values
        void Set(real x, real y, real z);
        
        //-QUERIES--------------------------------------------------------------------------------//

        /// Compute fast square norm of the vector
        real GetSquareNorm() const;
        
        /// Compute norm of the vector
        real GetNorm() const;
        
        /// Get dot product of vector with other
        real GetDotProduct(const Vector3& other) const;
        
        /// Get cross product of vector with other
        Vector3 GetCrossProduct(const Vector3& other) const;
        
        /// Get the angle from the vector to the other vector
        Angle GetAngle(const Vector3& other) const;
        
        /// Get the fast square distance between self point and other
        real GetSquareDistance(const Vector3& point) const;
        
        /// Get the distance between self point and other
        real GetDistance(const Vector3& point) const;
        
        /// Check if the norm is zero
        bool IsZero() const;
        
        /// Check if the norm is one
        bool IsNormalized() const;
        
        /// Check if the vector is colinear to other
        bool IsColinear(const Vector3& other) const;
        
        /// Check if the vector is orthogonal to other
        bool IsOrthogonal(const Vector3& other) const;

        /// Get the orthogonal vector to planar self, other
        Vector3 GetOrthogonal(const Vector3& other) const;

        /// Get the maximum component value
        real GetMaximum() const;

        /// Get the minimum component value
        real GetMinimum() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        /// Normalize the vector
        void Normalize();

        //-VARIABLES------------------------------------------------------------------------------//

        /// Zero predefined vector (0, 0, 0)
        static COFFEE_STATIC_API const Vector3 Zero;

        /// X axis predefined vector (1, 0, 0)
        static COFFEE_STATIC_API const Vector3 XAxis;

        /// Y axis predefined vector (0, 1, 0)
        static COFFEE_STATIC_API const Vector3 YAxis;

        /// Z axis predefined vector (0, 0, 1)
        static COFFEE_STATIC_API const Vector3 ZAxis;

        /// One predefined vector (1, 1, 1)
        static COFFEE_STATIC_API const Vector3 One;

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        real X;
        real Y;
        real Z;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Vector3);
}
}
#endif
