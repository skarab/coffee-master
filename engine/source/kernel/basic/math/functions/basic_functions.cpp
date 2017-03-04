#include "coffee_includes.h"
#include "kernel/basic/math/functions/basic_functions.h"

namespace coffee
{
    //-FUNCTIONS----------------------------------------------------------------------------------//

    bool IsEqual(real value1, real value2)
    {
        return (value1>=value2-RealPrecision) && (value1<=value2+RealPrecision);
    }

    //----------------------------------------------------------------------------------------//

    bool IsRoughlyEqual(real value1, real value2, real precision)
    {
        return (value1>=value2-precision) && (value1<=value2+precision);
    }

    //----------------------------------------------------------------------------------------//

    bool IsNotEqual(real value1, real value2)
    {
        return (value1<value2-RealPrecision) || (value1>value2+RealPrecision);
    }

    //----------------------------------------------------------------------------------------//

    real Pow(real value, real power)
    {
        return powf(value, power);
    }

    //----------------------------------------------------------------------------------------//

    bool IsPowerOfTwo(int32 value)
    {
        return (value>0) && ((value&(value-1))==0);
    }

    //----------------------------------------------------------------------------------------//

    int32 GetPowerOfTwo(int32 value)
    {
        return (int32)pow(2.0f, ceil(log((float)value)/log(2.0f)));
    }

    //----------------------------------------------------------------------------------------//

    real Sqrt(real value)
    {
        return sqrtf(value);
    }

    //----------------------------------------------------------------------------------------//

    real ReciprocalSqrt(real value)
    {
        // Coming from http://renderfeather.googlecode.com/hg-history/034a1900d6e8b6c92440382658d2b01fc732c5de/Doc/optimized%20Matrix%20quaternion%20conversion.pdf
        long i;
        real y, r;
        y = value*0.5f;
        i = *(long*)&value;
        i = 0x5f3759df-(i>>1);
        r = *(real*)&i;
        r = r*(1.5f-r*r*y);
        return r;
    }

    //----------------------------------------------------------------------------------------//

    real Sin(real value)
    {
        return sinf(value);
    }

    //----------------------------------------------------------------------------------------//

    real ASin(real value)
    {
        return asinf(value);
    }

    //----------------------------------------------------------------------------------------//

    real Cos(real value)
    {
        return cosf(value);
    }

    //----------------------------------------------------------------------------------------//

    real ACos(real value)
    {
        return acosf(value);
    }

    //----------------------------------------------------------------------------------------//

    real ATan2(real y, real x)
    {
        return atan2f(y, x);
    }

    //----------------------------------------------------------------------------------------//

    real Ceil(real value)
    {
        return ceilf(value);
    }

    //----------------------------------------------------------------------------------------//

    real Floor(real value)
    {
        return floorf(value);
    }

}
