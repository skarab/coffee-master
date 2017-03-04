#ifndef _COFFEE_BASIC_MATH_VECTOR_INT2_H_
#define _COFFEE_BASIC_MATH_VECTOR_INT2_H_

#include "coffee_includes.h"
#include "kernel/meta/meta.h"
#include "kernel/basic/math/vector/basic_vector2.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Vector with two integer components X,Y
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Vector2i : public meta::Object
    {
        COFFEE_Type(Vector2i);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        /// Construct assigning value to each components
        Vector2i(int32 value=0);

        /// Construct with specific component values
        Vector2i(int32 x, int32 y);

        /// Construct copying other
        Vector2i(const Vector2i& other);

        /// Construct copying and casting Vector2 values
        Vector2i(const Vector2& other);

        //-OPERATORS------------------------------------------------------------------------------//

        /// Assign the value to each components
        Vector2i& operator = (int32 value);

        /// Assign values from other to each components
        Vector2i& operator = (const Vector2i& other);

        /// Add value to each components
        Vector2i& operator += (int32 value);

        /// Add values from other to each components
        Vector2i& operator += (const Vector2i& other);

        /// Substract value to each components
        Vector2i& operator -= (int32 value);

        /// Substract value from other to each components
        Vector2i& operator -= (const Vector2i& other);

        /// Multiply each components by value
        Vector2i& operator *= (int32 value);
        
        /// Multiply each components by other values
        Vector2i& operator *= (const Vector2i& other);

        /// Divide each components by value        
        Vector2i& operator /= (int32 value);

        /// Divide each components by other values        
        Vector2i& operator /= (const Vector2i& other);

        /// Create a vector which is the sum of self and value        
        Vector2i operator + (int32 value) const;

        /// Create a vector which is the sum of self and other
        Vector2i operator + (const Vector2i& other) const;

        /// Get the opposite vector
        Vector2i operator - () const;
        
        /// Create a vector which is the difference of self and value
        Vector2i operator - (int32 value) const;
        
        /// Create a vector which is the difference of self and other
        Vector2i operator - (const Vector2i& other) const;
        
        /// Create a vector which is the product of self and value
        Vector2i operator * (int32 value) const;
        
        /// Create a vector which is the product of self and other
        Vector2i operator * (const Vector2i& other) const;

        /// Create a vector which is the div of self and value
        Vector2i operator / (int32 value) const;
        
        /// Create a vector which is the div of self and other
        Vector2i operator / (const Vector2i& other) const;

        /// Check if the vectors are equal        
        bool operator == (const Vector2i& other) const;

        /// Check if the vectors are not equal
        bool operator != (const Vector2i& other) const;

        /// Check if both components are greater than the other vector components
        bool operator > (const Vector2i& other) const;

        /// Check if both components are less than the other vector components
        bool operator < (const Vector2i& other) const;

        /// Check if both components are greater than, or equal to the other vector components
        bool operator >= (const Vector2i& vector) const;
        
        /// Check if both components are less than, or equal to the other vector components
        bool operator <= (const Vector2i& vector) const;

        /// Get a specific component by index
        const int32& operator[](uint32 component_index) const;

        /// Get a specific component by index
        int32& operator[](uint32 component_index);

        //-ACCESSORS------------------------------------------------------------------------------//

        /// Assign component values
        void Set(int32 x, int32 y);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        int32 X;
        int32 Y;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Vector2i);
}
}
#endif
