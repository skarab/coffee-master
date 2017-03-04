#ifndef _COFFEE_BASIC_MATH_VECTOR2_H_
#define _COFFEE_BASIC_MATH_VECTOR2_H_

#include "coffee_includes.h"
#include "kernel/meta/meta.h"
#include "kernel/basic/math/angle/basic_angle.h"

namespace coffee
{
namespace basic
{
    class Vector2i;

    //--------------------------------------------------------------------------------------------//
    /// Vector with two real components
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Vector2 : public meta::Object
    {
        COFFEE_Type(Vector2);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        /// Construct assigning value to each components
        Vector2(real value=0.0f);
        
        /// Construct with specific component values
        Vector2(real x, real y);
        
        /// Construct copying other
        Vector2(const Vector2& other);
        
        /// Construct copying and casting Vector2i values
        Vector2(const Vector2i& other);

        //-OPERATORS------------------------------------------------------------------------------//

        /// Assign the value to each components
        Vector2& operator = (real value);
        
        /// Assign values from other to each components
        Vector2& operator = (const Vector2& other);
        
        /// Add value to each components
        Vector2& operator += (real value);
        
        /// Add values from other to each components
        Vector2& operator += (const Vector2& other);
        
        /// Substract value to each components
        Vector2& operator -= (real value);
        
        /// Substract value from other to each components
        Vector2& operator -= (const Vector2& other);
        
        /// Multiply each components by value
        Vector2& operator *= (real value);
        
        /// Multiply each components by other values
        Vector2& operator *= (const Vector2& other);
        
        /// Divide each components by value        
        Vector2& operator /= (real value);
        
        /// Divide each components by other values        
        Vector2& operator /= (const Vector2& other);
        
        /// Create a vector which is the sum of self and value        
        Vector2 operator + (real value) const;
        
        /// Create a vector which is the sum of self and other
        Vector2 operator + (const Vector2& other) const;
        
        /// Get the opposite vector
        Vector2 operator - () const;
        
        /// Create a vector which is the difference of self and value
        Vector2 operator - (real value) const;
        
        /// Create a vector which is the difference of self and other
        Vector2 operator - (const Vector2& other) const;
        
        /// Create a vector which is the product of self and value
        Vector2 operator * (real value) const;
        
        /// Create a vector which is the product of self and other
        Vector2 operator * (const Vector2& other) const;
        
        /// Create a vector which is the div of self and value
        Vector2 operator / (real value) const;
        
        /// Create a vector which is the div of self and other
        Vector2 operator / (const Vector2& other) const;
        
        /// Check if the vectors are equal        
        bool operator == (const Vector2& other) const;
        
        /// Check if the vectors are not equal      
        bool operator != (const Vector2& other) const;

        /// Check if both components are greater than the other vector components
        bool operator > (const Vector2& other) const;

        /// Check if both components are greater or equal to the other vector components
        bool operator >= (const Vector2& other) const;

        /// Check if both components are less than the other vector components
        bool operator < (const Vector2& other) const;
        
        /// Check if both components are less or equal to the other vector components
        bool operator <= (const Vector2& other) const;

        /// Get a specific component by index
        const real& operator[](uint32 component_index) const;

        /// Get a specific component access by index
        real& operator[](uint32 component_index);

        //-ACCESSORS------------------------------------------------------------------------------//

        /// Assign component values
        void Set(real x, real y);

        //-QUERIES--------------------------------------------------------------------------------//

        /// Compute fast square norm of the vector
        real GetSquareNorm() const;

        /// Compute norm of the vector
        real GetNorm() const;

        /// Get dot product of vector with other
        real GetDotProduct(const Vector2& other) const;

        /// Get cross product of vector with other
        real GetCrossProduct(const Vector2& other) const;

        /// Check if the norm is zero
        bool IsZero() const;

        /// Check if the norm is one
        bool IsNormalized() const;

        /// Check if the vector is colinear to other
        bool IsColinear(const Vector2& other) const;

        /// Check if the vector is orthogonal to other
        bool IsOrthogonal(const Vector2& other) const;

        /// Get the orthogonal vector, in the specified sens
        Vector2 GetOrthogonal(bool it_is_clock_wise = true) const;

        /// Get the angle of vector, based on the default coordinate system
        Angle GetAngle() const;
        
        /// Get the angle from the vector to the other vector
        Angle GetAngle(const Vector2& other) const;

        /// Get the fast square distance between self point and other
        real GetSquareDistance(const Vector2& point) const;

        /// Get the distance between self point and other
        real GetDistance(const Vector2& point) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        /// Normalize the vector
        void Normalize();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        real X;
        real Y;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Vector2);
}
}
#endif
