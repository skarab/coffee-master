#include "kernel/basic/math/euler/basic_euler.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::Euler);
        COFFEE_Attribute(basic::Angle, X, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Angle, Y, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Angle, Z, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Euler::Euler()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Euler::Euler(const Euler& other) :
        X(other.X),
        Y(other.Y),
        Z(other.Z)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Euler::Euler(const Angle& x, const Angle& y, const Angle& z) :
        X(x),
        Y(y),
        Z(z)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Euler::Euler(const Quaternion& quaternion)
    {
        *this = quaternion;
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    Euler& Euler::operator = (const Euler& other)
    {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Euler& Euler::operator = (const Quaternion& quaternion)
    {
        // Coming from http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/
        // Note it's the version working on non-normalized quaternions

        real sqw = quaternion.W*quaternion.W;
        real sqx = quaternion.X*quaternion.X;
        real sqy = quaternion.Y*quaternion.Y;
        real sqz = quaternion.Z*quaternion.Z;

        // if normalised is one, otherwise is correction factor
	    real unit = sqx+sqy+sqz+sqw;
	    real test = quaternion.X*quaternion.Y+quaternion.Z*quaternion.W;

	    if (test>=0.499f*unit)
        {
            // singularity at north pole
		    Y = 2.0f*ATan2(quaternion.X, quaternion.W);
		    Z = Pi/2.0f;
		    X = 0.0f;
		}
        else if (test<=-0.499f*unit)
        {
            // singularity at south pole
		    Y = -2.0f*ATan2(quaternion.X, quaternion.W);
		    Z = -Pi/2.0f;
		    X = 0.0f;
	    }
        else
        {
            Y = ATan2(2.0f*quaternion.Y*quaternion.W-2.0f*quaternion.X*quaternion.Z, sqx-sqy-sqz+sqw);
	        Z = ASin(2.0f*test/unit);
	        X = ATan2(2.0f*quaternion.X*quaternion.W-2.0f*quaternion.Y*quaternion.Z, -sqx+sqy-sqz+sqw);
        }
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Euler& Euler::operator += (const Euler& other)
    {
        X += other.X;
        Y += other.Y;
        Z += other.Z;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Euler& Euler::operator -= (const Euler& other)
    {
        X -= other.X;
        Y -= other.Y;
        Z -= other.Z;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Euler Euler::operator + (const Euler& other)
    {
        return Euler(X+other.X, Y+other.Y, Z+other.Z);
    }

    //--------------------------------------------------------------------------------------------//

    Euler Euler::operator - (const Euler& other)
    {
        return Euler(X-other.X, Y-other.Y, Z-other.Z);
    }

    //--------------------------------------------------------------------------------------------//

    bool Euler::operator == (const Euler& other) const
    {
        return (X==other.X) && (Y==other.Y) && (Z==other.Z);
    }

    //--------------------------------------------------------------------------------------------//

    bool Euler::operator != (const Euler& other) const
    {
        return (X!=other.X) || (Y!=other.Y) || (Z!=other.Z);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Euler::Set(real x, real y, real z)
    {
        X = x;
        Y = y;
        Z = z;
    }

    //--------------------------------------------------------------------------------------------//

    void Euler::SetDegrees(real x, real y, real z)
    {
        X.SetDegrees(x);
        Y.SetDegrees(y);
        Z.SetDegrees(z);
    }

}
}
