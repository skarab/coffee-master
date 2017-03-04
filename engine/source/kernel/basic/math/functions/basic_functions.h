#ifndef _COFFEE_BASIC_MATH_FUNCTIONS_H_
#define _COFFEE_BASIC_MATH_FUNCTIONS_H_

namespace coffee
{
    //-VARIABLES----------------------------------------------------------------------------------//

    const real Pi = 3.1415926535897932f;
    const real RealPrecision = 0.000001f;
    const real RealMinimumValue = -999999.0f;
    const real RealMaximumValue = 999999.0f;
    const uint32 CurvePrecision = 40;

    //-FUNCTIONS----------------------------------------------------------------------------------//

    /// Get absolute value
    template<typename T> T COFFEE_TEMPLATE_API Absolute(T value)
    {
        return value >= (T)0 ? value : -value;
    }

    /// Clamp the value between [minimum, maximum]
    template<typename T> void COFFEE_TEMPLATE_API Clamp(T& value, T minimum, T maximum)
    {
        if (value<minimum)
            value = minimum;
        else if (value>maximum)
            value = maximum;
    }

    /// Clamp the value between [minimum, ...[
    template<typename T> void COFFEE_TEMPLATE_API ClampMinimum(T& value, T minimum)
    {
        if (value<minimum)
            value = minimum;
    }

    /// Clamp the value between ]..., maximum]
    template<typename T> void COFFEE_TEMPLATE_API ClampMaximum(T& value, T maximum)
    {
        if (value>maximum)
            value = maximum;
    }

    /// Get minimum value
    template<typename T> T COFFEE_TEMPLATE_API Minimum(T value1, T value2)
    {
        if (value1<value2)
            return value1;
        return value2;
    }

    /// Get maximum value
    template<typename T> T COFFEE_TEMPLATE_API Maximum(T value1, T value2)
    {
        if (value1>value2)
            return value1;
        return value2;
    }

    /// Check real equality using default precision
    bool COFFEE_API IsEqual(real value1, real value2);

    /// Check real equality using custom precision
    bool COFFEE_API IsRoughlyEqual(real value1, real value2, real precision);

    /// Check real non-equality using default precision
    bool COFFEE_API IsNotEqual(real value1, real value2);

    /// Compute value^power
    real COFFEE_API Pow(real value, real power);

    /// Check if value is power of two
    bool COFFEE_API IsPowerOfTwo(int32 value);

    /// Get the nearest high power of two value
    int32 COFFEE_API GetPowerOfTwo(int32 value);

    /// Compute square root
    real COFFEE_API Sqrt(real value);

    /// Compute reciprocal square root
    real COFFEE_API ReciprocalSqrt(real value);

    /// Compute sinus in radian
    real COFFEE_API Sin(real value);

    /// Compute inverse sinus in radian
    real COFFEE_API ASin(real value);

    /// Compute cosinus in radian
    real COFFEE_API Cos(real value);

    /// Compute inverse cosinus in radian
    real COFFEE_API ACos(real value);

    /// Compute inverse tangent in radian
    real COFFEE_API ATan2(real y, real x);

    //----------------------------------------------------------------------------------------//
    /// Returns the smallest integral real that is not less than value.
    ///
    /// ex:
    ///     ceil of 2.3 is 3.0
    ///     ceil of 3.8 is 4.0
    ///     ceil of -2.3 is -2.0
    ///     ceil of -3.8 is -3.0
    //----------------------------------------------------------------------------------------//
    real COFFEE_API Ceil(real value);

    //----------------------------------------------------------------------------------------//
    /// Returns the largest integral real that is not greater than value.
    ///
    /// ex:
    ///     floor of 2.3 is 2.0
    ///     floor of 3.8 is 3.0
    ///     floor of -2.3 is -3.0
    ///     floor of -3.8 is -4.0
    //----------------------------------------------------------------------------------------//
    real COFFEE_API Floor(real value);

}
#endif
