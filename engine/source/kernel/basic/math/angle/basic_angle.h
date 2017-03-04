#ifndef _COFFEE_BASIC_MATH_ANGLE_H_
#define _COFFEE_BASIC_MATH_ANGLE_H_

#include "coffee_includes.h"
#include "kernel/meta/meta.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Simple angle class
    ///
    /// This Angle class works with radians, auto-converted in the [0,2pi[ range
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Angle : public meta::Object
    {
        COFFEE_Type(Angle);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        /// Construct an angle initialized to 0 radians
        Angle();

        /// Construct an angle of 'value' radians
        Angle(real value);

        /// Construct copying other
        Angle(const Angle& other);

        //-OPERATORS------------------------------------------------------------------------------//

        /// Assign the radian 'value' to the angle
        Angle& operator = (real value);

        /// Copy other value
        Angle& operator = (const Angle& other);

        /// Add other to self
        Angle& operator += (const Angle& other);

        /// Substract other to self
        Angle& operator -= (const Angle& other);
        
        /// Multiply self with other
        Angle& operator *= (const Angle& other);

        /// Divide self with other
        Angle& operator /= (const Angle& other);

        /// Create an angle which is the sum of self and other
        Angle operator + (const Angle& other) const;

        /// Create an angle which is the difference of self and other
        Angle operator - (const Angle& other) const;
        
        /// Create an angle which is the negative of self
        Angle operator - () const;

        /// Create an angle which is the mult of self and other
        Angle operator * (const Angle& other) const;

        /// Create an angle which is the div of self and other
        Angle operator / (const Angle& other) const;

        /// Check if self is equal to the other
        bool operator == (const Angle& other) const;

        /// Check if self is not equal to the other
        bool operator != (const Angle& other) const;

        /// Check if self is less than the other
        bool operator < (const Angle& other) const;
        
        /// Check if self is greater than the other
        bool operator > (const Angle& other) const;
        
        /// Check if self is less or equal than the other
        bool operator <= (const Angle& other) const;
        
        /// Check if self is greater or equal than the other
        bool operator >= (const Angle& other) const;

        //-ACCESSORS------------------------------------------------------------------------------//

        /// Get the value in radian
        real Get() const;

        /// Set the value in degree
        void SetDegrees(real value);
        
        /// Get the value in degree
        real GetDegrees() const;

        //-QUERIES--------------------------------------------------------------------------------//

        /// Get the cosinus of the angle
        real GetCosinus() const;
        
        /// Get the sinus of the angle
        real GetSinus() const;

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        /// Convert into the range [0,2pi[
        void _Normalize();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        /// Radian angle into the range [0,2pi[
        real _Value;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Angle);
}
}
#endif
