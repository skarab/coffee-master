#ifndef _COFFEE_BASIC_MATH_VECTOR4_H_
#define _COFFEE_BASIC_MATH_VECTOR4_H_

#include "coffee_includes.h"
#include "kernel/basic/math/vector/basic_vector3.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Vector with four real components
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Vector4 : public meta::Object
    {
        COFFEE_Type(Vector4);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        /// Construct assigning value to each components
        Vector4(real value=0.0f);
        
        /// Construct with specific component values
        Vector4(real x, real y, real z, real w);
        
        /// Construct copying other
        Vector4(const Vector4& other);
        
        /// Construct copying other and setting W to default (1.0f)
        Vector4(const Vector3& other);

        //-OPERATORS------------------------------------------------------------------------------//

        /// Assign the value to each components
        Vector4& operator = (real value);
        
        /// Assign values from other to each components
        Vector4& operator = (const Vector4& other);
        
        /// Assign values from other to each components, and set W to default (1.0f)
        Vector4& operator = (const Vector3& other);

        /// Add value to each components
        Vector4& operator += (real value);
        
        /// Add values from other to each components
        Vector4& operator += (const Vector4& other);
        
        /// Substract value to each components
        Vector4& operator -= (real value);
        
        /// Substract value from other to each components
        Vector4& operator -= (const Vector4& other);
        
        /// Multiply each components by value
        Vector4& operator *= (real value);
        
        /// Multiply each components by other values
        Vector4& operator *= (const Vector4& other);
        
        /// Transform by the matrix
        Vector4& operator *= (const Matrix& matrix);
        
        /// Divide each components by value        
        Vector4& operator /= (real value);
        
        /// Divide each components by other values        
        Vector4& operator /= (const Vector4& other);
        
        /// Create a vector which is the sum of self and value        
        Vector4 operator + (real value) const;
        
        /// Create a vector which is the sum of self and other
        Vector4 operator + (const Vector4& other) const;
        
        /// Get the opposite vector
        Vector4 operator - () const;
        
        /// Create a vector which is the difference of self and value
        Vector4 operator - (real value) const;
        
        /// Create a vector which is the difference of self and other
        Vector4 operator - (const Vector4& other) const;
        
        /// Create a vector which is the product of self and value
        Vector4 operator * (real value) const;
        
        /// Create a vector which is the product of self and other
        Vector4 operator * (const Vector4& other) const;
        
        /// Create a vector which is the transformed vector by matrix
        Vector4 operator * (const Matrix& matrix) const;
        
        /// Create a vector which is the div of self and value
        Vector4 operator / (real value) const;
        
        /// Create a vector which is the div of self and other
        Vector4 operator / (const Vector4& other) const;
        
        /// Get a specific component by index
        const real& operator[](uint32 component_index) const;
        
        /// Get a specific component access by index
        real& operator[](uint32 component_index);

        //-ACCESSORS------------------------------------------------------------------------------//

        /// Assign component values
        void Set(real x, real y, real z, real w);
        
        /// Assign component values from Vector3
        void Set(const Vector3& other, float w=1.0f);

        //-QUERIES--------------------------------------------------------------------------------//

        /// Compute fast square norm of the vector
        real GetSquareNorm() const;
        
        /// Compute norm of the vector
        real GetNorm() const;

        /// Check if the norm is zero
        bool IsZero() const;
        
        /// Check if the norm is one
        bool IsNormalized() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        /// Normalize the vector
        void Normalize();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        real X;
        real Y;
        real Z;
        real W;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Vector4);
}
}
#endif
