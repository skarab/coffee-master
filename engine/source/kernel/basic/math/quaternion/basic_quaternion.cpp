#include "kernel/basic/math/quaternion/basic_quaternion.h"
#include "kernel/basic/math/euler/basic_euler.h"
#include "kernel/basic/math/matrix/basic_matrix.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::Quaternion);
        COFFEE_Attribute(real, X, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, Y, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, Z, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, W, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Quaternion::Quaternion() :
        X(0.0f),
        Y(0.0f),
        Z(0.0f),
        W(1.0f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Quaternion::Quaternion(const Quaternion& other) :
        X(other.X),
        Y(other.Y),
        Z(other.Z),
        W(other.W)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Quaternion::Quaternion(real x, real y, real z, real w) :
        X(x),
        Y(y),
        Z(z),
        W(w)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Quaternion::Quaternion(const Euler& euler)
    {
        *this = euler;
    }

    //--------------------------------------------------------------------------------------------//

    Quaternion::Quaternion(const Matrix& matrix)
    {
        *this = matrix;
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    Quaternion& Quaternion::operator = (const Quaternion& other)
    {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        W = other.W;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Quaternion& Quaternion::operator = (const Euler& euler)
    {
        // Coming from http://www.euclideanspace.com/maths/geometry/rotations/conversions/eulerToQuaternion/
        // First method.
        real c1 = (euler.Y/2.0f).GetCosinus();
        real s1 = (euler.Y/2.0f).GetSinus();
        real c2 = (euler.Z/2.0f).GetCosinus();
        real s2 = (euler.Z/2.0f).GetSinus();
        real c3 = (euler.X/2.0f).GetCosinus();
        real s3 = (euler.X/2.0f).GetSinus();
        real c1c2 = c1*c2;
        real s1s2 = s1*s2;
        W = c1c2*c3-s1s2*s3;
  	    X = c1c2*s3+s1s2*c3;
	    Y = s1*c2*c3+c1*s2*s3;
	    Z = c1*s2*c3-s1*c2*s3;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Quaternion& Quaternion::operator = (const Matrix& matrix)
    {
        // Coming from http://renderfeather.googlecode.com/hg-history/034a1900d6e8b6c92440382658d2b01fc732c5de/Doc/optimized%20Matrix%20quaternion%20conversion.pdf
        // With added matrix unscaling
        float s0, s1, s2;
        int k0, k1, k2, k3;
        const float *m = matrix.GetData();
        float sc0 = 1.0f/Vector3(m[0], m[1], m[2]).GetNorm();
        float sc1 = 1.0f/Vector3(m[4], m[5], m[6]).GetNorm();
        float sc2 = 1.0f/Vector3(m[8], m[9], m[10]).GetNorm();
        float m0 = m[0*4+0]*sc0;
        float m1 = m[1*4+1]*sc1;
        float m2 = m[2*4+2]*sc2;
        
        if (m0+m1+m2>0.0f)
        {
            k0 = 3;
            k1 = 2;
            k2 = 1;
            k3 = 0;
            s0 = 1.0f;
            s1 = 1.0f;
            s2 = 1.0f;
        }
        else if (m0>m1 && m0>m2)
        {
            k0 = 0;
            k1 = 1;
            k2 = 2;
            k3 = 3;
            s0 = 1.0f;
            s1 = -1.0f;
            s2 = -1.0f;
        }
        else if (m1>m2)
        {
            k0 = 1;
            k1 = 0;
            k2 = 3;
            k3 = 2;
            s0 = -1.0f;
            s1 = 1.0f;
            s2 = -1.0f;
        }
        else
        {
            k0 = 2;
            k1 = 3;
            k2 = 0;
            k3 = 1;
            s0 = -1.0f;
            s1 = -1.0f;
            s2 = 1.0f;
        }
        float t = s0*m0+s1*m1+s2*m2+1.0f;
        float s = ReciprocalSqrt(t)*0.5f;
        (&X)[k0] = s*t;
        (&X)[k1] = (m[0*4+1]*sc0-s2*sc1*m[1*4+0])*s;
        (&X)[k2] = (m[2*4+0]*sc2-s1*sc0*m[0*4+2])*s;
        (&X)[k3] = (m[1*4+2]*sc1-s0*sc2*m[2*4+1])*s;

        // Make sure its normalized, ReciprocalSqrt precision seams doubtfull...
        Normalize();
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Quaternion& Quaternion::operator *= (const Quaternion& other)
    {
        real x, y, z, w;
        x = W * other.X+X*other.W+Y*other.Z-Z*other.Y;
        y = W * other.Y+Y*other.W+Z*other.X-X*other.Z;
        z = W * other.Z+Z*other.W+X*other.Y-Y*other.X;
        w = W * other.W-X*other.X-Y*other.Y-Z*other.Z;
        X = x;
        Y = y;
        Z = z;
        W = w;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Quaternion Quaternion::operator ~ () const
    {
        return Quaternion(-X, -Y, -Z, W);
    }

    //--------------------------------------------------------------------------------------------//

    Quaternion Quaternion::operator * (const Quaternion& other) const
    {
        return Quaternion(
            W*other.X+X*other.W+Y*other.Z-Z*other.Y,
            W*other.Y+Y*other.W+Z*other.X-X*other.Z,
            W*other.Z+Z*other.W+X*other.Y-Y*other.X,
            W*other.W-X*other.X-Y*other.Y-Z*other.Z);
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Quaternion::operator * (const Vector3& vector) const
    {
        Vector3 temp(Y*vector.Z-Z*vector.Y, Z*vector.X-X*vector.Z, X*vector.Y-Y*vector.X);
        return Vector3(
            vector.X+2.0f*(W*temp.X+Y*temp.Z-Z*temp.Y),
            vector.Y+2.0f*(W*temp.Y+Z*temp.X-X*temp.Z),
            vector.Z+2.0f*(W*temp.Z+X*temp.Y-Y*temp.X));
    }

    //--------------------------------------------------------------------------------------------//

    bool Quaternion::operator == (const Quaternion& other) const
    {
        return IsEqual(X, other.X) && IsEqual(Y, other.Y)
            && IsEqual(Z, other.Z) && IsEqual(W, other.W);
    }

    //--------------------------------------------------------------------------------------------//

    bool Quaternion::operator != (const Quaternion& other) const
    {
        return IsNotEqual(X, other.X) || IsNotEqual(Y, other.Y)
            || IsNotEqual(Z, other.Z) || IsNotEqual(W, other.W);
    }

    //-QUERIES------------------------------------------------------------------------------------//

    Vector3 Quaternion::GetXAxis() const
    {
        return Vector3(1.0f-2.0f*Y*Y-2.0f*Z*Z, 2.0f*(X*Y+W*Z), 2.0f*(X*Z-W*Y));
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Quaternion::GetYAxis() const
    {
        return Vector3(2.0f*(X*Y-W*Z), 1.0f-2.0f*X*X-2.0f*Z*Z, 2.0f*(Y*Z+W*X));
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Quaternion::GetZAxis() const
    {
        return Vector3(2.0f*(X*Z+W*Y), 2.0f*(Y*Z-W*X), 1.0f-2.0f*X*X-2.0f*Y*Y);
    }

    //--------------------------------------------------------------------------------------------//

    real Quaternion::GetSquareNorm() const
    {
        return X*X+Y*Y+Z*Z+W*W;
    }

    //--------------------------------------------------------------------------------------------//

    real Quaternion::GetNorm() const
    {
        return Sqrt(GetSquareNorm());
    }

    //--------------------------------------------------------------------------------------------//

    real Quaternion::GetDotProduct(const Quaternion& other) const
    {
        return X*other.X+Y*other.Y+Z*other.Z+W*other.W;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Quaternion::Normalize()
    {
        real length = GetNorm();
        COFFEE_Assert(length>RealPrecision, core::ERROR_CODE_IncorrectUsage, "Zero division");
        X /= length;
        Y /= length;
        Z /= length;
        W /= length;
    }

    //--------------------------------------------------------------------------------------------//

    void Quaternion::SetFromZAxis(const Vector3& z_axis)
    {
        COFFEE_Assert(z_axis.IsNormalized(), core::ERROR_CODE_IncorrectUsage, "Axis is not normalized");

        if (z_axis==Vector3(0.0f, 1.0f, 0.0f))
        {
            SetFromXRotation(Angle(-Pi/2.0f));
        }
        else if (z_axis==Vector3(0.0f, -1.0f, 0.0f))
        {
            SetFromXRotation(Angle(Pi/2.0f));
        }
        else
        {
            Matrix matrix;
            matrix.SetFromLookAt(Vector3(), z_axis, Vector3(0.0f, 1.0f, 0.0f));
            *this = matrix;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Quaternion::SetFromAxisAndAngle(const Vector3& axis, const Angle& angle)
    {
        if (angle==0.0f)
        {
            X = Y = Z = 0.0f;
            W = 1.0f;
        }
        else
        {
            real scale = Sin(angle.Get()*0.5f);
            X = axis.X*scale;
            Y = axis.Y*scale;
            Z = axis.Z*scale;
            W = Cos(angle.Get()*0.5f);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Quaternion::SetFromXRotation(const Angle& angle)
    {
        if (angle==0.0f)
        {
            X = Y = Z = 0.0f;
            W = 1.0f;
        }
        else
        {
            X = Sin(angle.Get()*0.5f);
            Y = 0.0f;
            Z = 0.0f;
            W = Cos(angle.Get()*0.5f);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Quaternion::SetFromYRotation(const Angle& angle)
    {
        if (angle==0.0f)
        {
            X = Y = Z = 0.0f;
            W = 1.0f;
        }
        else
        {
            X = 0.0f;
            Y = Sin(angle.Get()*0.5f);
            Z = 0.0f;
            W = Cos(angle.Get()*0.5f);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Quaternion::SetFromZRotation(const Angle& angle)
    {
        if (angle==0.0f)
        {
            X = Y = Z = 0.0f;
            W = 1.0f;
        }
        else
        {
            X = 0.0f;
            Y = 0.0f;
            Z = Sin(angle.Get() * 0.5f);
            W = Cos(angle.Get() * 0.5f);
        }
    }

}
}
