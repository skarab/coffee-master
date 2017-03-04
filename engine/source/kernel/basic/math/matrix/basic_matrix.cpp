#include "kernel/basic/math/matrix/basic_matrix.h"
#include "kernel/basic/math/quaternion/basic_quaternion.h"
#include "kernel/basic/math/euler/basic_euler.h"
#include "kernel/core/error/core_error.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::Matrix);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Matrix::Matrix()
    {
        COFFEE_Copy(_Data, _IdentityData, sizeof(real)*16);
    }

    //--------------------------------------------------------------------------------------------//

    Matrix::Matrix(const Matrix& other)
    {
        *this = other;
    }

    //--------------------------------------------------------------------------------------------//

    Matrix::Matrix(const Quaternion& quaternion)
    {
        *this = quaternion;
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    Matrix& Matrix::operator = (const Matrix& other)
    {
        COFFEE_Copy(_Data, other._Data, sizeof(real)*16);
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Matrix& Matrix::operator = (const Quaternion& quaternion)
    {
        // Coming from http://renderfeather.googlecode.com/hg-history/034a1900d6e8b6c92440382658d2b01fc732c5de/Doc/optimized%20Matrix%20quaternion%20conversion.pdf

        real x2 = quaternion.X+quaternion.X;
        real y2 = quaternion.Y+quaternion.Y;
        real z2 = quaternion.Z+quaternion.Z;
        real w2 = quaternion.W+quaternion.W;
        real yy2 = quaternion.Y*y2;
        real xy2 = quaternion.X*y2;
        real xz2 = quaternion.X*z2;
        real yz2 = quaternion.Y*z2;
        real zz2 = quaternion.Z*z2;
        real wz2 = quaternion.W*z2;
        real wy2 = quaternion.W*y2;
        real wx2 = quaternion.W*x2;
        real xx2 = quaternion.X*x2;

        _Data[0*4+0] = -yy2-zz2+1.0f;
        _Data[0*4+1] = xy2+wz2;
        _Data[0*4+2] = xz2-wy2;
        _Data[0*4+3] = 0.0f;
        
        _Data[1*4+0] = xy2-wz2;
        _Data[1*4+1] = -xx2-zz2+1.0f;
        _Data[1*4+2] = yz2+wx2;
        _Data[1*4+3] = 0.0f;

        _Data[2*4+0] = xz2+wy2;
        _Data[2*4+1] = yz2-wx2;
        _Data[2*4+2] = -xx2-yy2+1.0f;
        _Data[2*4+3] = 0.0f; 

        _Data[12] = 0.0f;
        _Data[13] = 0.0f;
        _Data[14] = 0.0f;
        _Data[15] = 1.0f;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Matrix& Matrix::operator *= (const Matrix& other)
    {
        operator =(*this*other);
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Matrix Matrix::operator* (const Matrix& other) const
    {
        Matrix mat;
        const real* a = other._Data;
        const real* b = _Data;
        real* m = mat._Data;
        for (uint32 i=0 ; i<4 ; ++i)
        {
            m[i] = a[i]*b[0] + a[i+4]*b[1] + a[i+8]*b[2] + a[i+12]*b[3];
            m[i+4] = a[i]*b[4] + a[i+4]*b[5] + a[i+8]*b[6] + a[i+12]*b[7];
            m[i+8] =  a[i]*b[8] + a[i+4]*b[9] + a[i+8]*b[10] + a[i+12]*b[11];
            m[i+12] = a[i]*b[12] + a[i+4]*b[13] + a[i+8]*b[14] + a[i+12]*b[15];
        }
        return mat;
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Matrix::operator* (const Vector3& vector) const
    {
        return Vector3(
            _Data[0]*vector.X + _Data[4]*vector.Y + _Data[8]*vector.Z + _Data[12],
            _Data[1]*vector.X + _Data[5]*vector.Y + _Data[9]*vector.Z + _Data[13],
            _Data[2]*vector.X + _Data[6]*vector.Y + _Data[10]*vector.Z + _Data[14]);
    }

    //--------------------------------------------------------------------------------------------//

    Vector4 Matrix::operator* (const Vector4& vector) const
    {
        return Vector4(
            _Data[0]*vector.X + _Data[4]*vector.Y + _Data[8]*vector.Z + _Data[12],
            _Data[1]*vector.X + _Data[5]*vector.Y + _Data[9]*vector.Z + _Data[13],
            _Data[2]*vector.X + _Data[6]*vector.Y + _Data[10]*vector.Z + _Data[14],
            _Data[3]*vector.X + _Data[7]*vector.Y + _Data[11]*vector.Z + _Data[15]);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const real* Matrix::GetData() const
    {
        return _Data;
    }

    //--------------------------------------------------------------------------------------------//

    real* Matrix::GetData()
    {
        return _Data;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    Vector3 Matrix::GetTranslation() const
    {
        return Vector3(_Data[12], _Data[13], _Data[14]);
    }

    //--------------------------------------------------------------------------------------------//

    Quaternion Matrix::GetRotation() const
    {
        return Quaternion(*this);
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Matrix::GetScale() const
    {
        Vector3 scale(
            Vector3(_Data[0], _Data[1], _Data[2]).GetNorm(),
            Vector3(_Data[4], _Data[5], _Data[6]).GetNorm(),
            Vector3(_Data[8], _Data[9], _Data[10]).GetNorm());
        COFFEE_Assert(!IsEqual(scale.X, 0.0f) && !IsEqual(scale.Y, 0.0f) && !IsEqual(scale.Z, 0.0f),
            core::ERROR_CODE_IncorrectUsage, "Scale of 0 detected");
        return scale;
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Matrix::GetXAxis() const
    {
        Vector3 vec(_Data[0], _Data[1], _Data[2]);
        vec.Normalize();
        return vec;
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Matrix::GetYAxis() const
    {
        Vector3 vec(_Data[4], _Data[5], _Data[6]);
        vec.Normalize();
        return vec;
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Matrix::GetZAxis() const
    {
        Vector3 vec(_Data[8], _Data[9], _Data[10]);
        vec.Normalize();
        return vec;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Matrix::Translate(const Vector3& translation)
    {
        real* data = GetData();

        if (!IsEqual(translation.X, 0.0f))
        {
            data[0] += data[3]*translation.X;
            data[4] += data[7]*translation.X;
            data[8] += data[11]*translation.X;
            data[12] += data[15]*translation.X;
        }

        if (!IsEqual(translation.Y, 0.0f))
        {
            data[1] += data[3]*translation.Y;
            data[5] += data[7]*translation.Y;
            data[9] += data[11]*translation.Y;
            data[13] += data[15]*translation.Y;
        }

        if (!IsEqual(translation.Z, 0.0f))
        {
            data[2] += data[3]*translation.Z;
            data[6] += data[7]*translation.Z;
            data[10] += data[11]*translation.Z;
            data[14] += data[15]*translation.Z;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Matrix::Scale(const Vector3& scale)
    {
        COFFEE_Assert(!IsEqual(scale.X, 0.0f) && !IsEqual(scale.Y, 0.0f) && !IsEqual(scale.Z, 0.0f),
            core::ERROR_CODE_IncorrectUsage, "Scale of 0 is forbidden");
        
        real* data = GetData();

        if (!IsEqual(scale.X, 0.0f) && !IsEqual(scale.X, 1.0f))
        {
            data[0] *= scale.X;
            data[1] *= scale.X;
            data[2] *= scale.X;
        }

        if (!IsEqual(scale.Y, 0.0f) && !IsEqual(scale.Y, 1.0f))
        {
            data[4] *= scale.Y;
            data[5] *= scale.Y;
            data[6] *= scale.Y;
        }

        if (!IsEqual(scale.Z, 0.0f) && !IsEqual(scale.Z, 1.0f))
        {
            data[8] *= scale.Z;
            data[9] *= scale.Z;
            data[10] *= scale.Z;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Matrix::UnScale()
    {
        Vector3 scale(GetScale());
        Scale(Vector3(1.0f/scale.X, 1.0f/scale.Y, 1.0f/scale.Z));
    }

    //--------------------------------------------------------------------------------------------//

    void Matrix::Invert()
    {
        Matrix inversed_matrix;
        inversed_matrix.SetInversed(*this);
        operator =(inversed_matrix);
    }

    //--------------------------------------------------------------------------------------------//

    void Matrix::Transpose()
    {
        Matrix transposed_matrix;
        transposed_matrix.SetTransposed(*this);
        operator =(transposed_matrix);
    }

    //--------------------------------------------------------------------------------------------//

    void Matrix::SetIdentity()
    {
        COFFEE_Copy(_Data, _IdentityData, sizeof(real)*16);
    }

    //--------------------------------------------------------------------------------------------//

    void Matrix::Set(const Vector3& translation, const Quaternion& rotation, const Vector3& scale)
    {
        *this = rotation;
        Scale(scale);
        Translate(translation);
    }

    //--------------------------------------------------------------------------------------------//

    void Matrix::SetInversed(const Matrix& other)
    {
        // Coming from ftp://download.intel.com/design/PentiumIII/sml/24504301.pdf

        const real* mat = other._Data;
        real tmp[12];   // temp array for pairs
        real src[16];   // array of transpose source matrix
        real det;       // determinant

        // transpose matrix
        for (uint32 i=0 ; i<4 ; ++i)
        {
            src[i] = mat[i*4];
            src[i+4] = mat[i*4+1];
            src[i+8] = mat[i*4+2];
            src[i+12] = mat[i*4+3];
        }

        // calculate pairs for first 8 elements (cofactors)
        tmp[0] = src[10]*src[15];
        tmp[1] = src[11]*src[14];
        tmp[2] = src[9]*src[15];
        tmp[3] = src[11]*src[13];
        tmp[4] = src[9]*src[14];
        tmp[5] = src[10]*src[13];
        tmp[6] = src[8]*src[15];
        tmp[7] = src[11]*src[12];
        tmp[8] = src[8]*src[14];
        tmp[9] = src[10]*src[12];
        tmp[10] = src[8]*src[13];
        tmp[11] = src[9]*src[12];

        // calculate first 8 elements (cofactors)
        _Data[0] = tmp[0]*src[5]+tmp[3]*src[6]+tmp[4]*src[7];
        _Data[0] -= tmp[1]*src[5]+tmp[2]*src[6]+tmp[5]*src[7];
        _Data[1] = tmp[1]*src[4]+tmp[6]*src[6]+tmp[9]*src[7];
        _Data[1] -= tmp[0]*src[4]+tmp[7]*src[6]+tmp[8]*src[7];
        _Data[2] = tmp[2]*src[4]+tmp[7]*src[5]+tmp[10]*src[7];
        _Data[2] -= tmp[3]*src[4]+tmp[6]*src[5]+tmp[11]*src[7];
        _Data[3] = tmp[5]*src[4]+tmp[8]*src[5]+tmp[11]*src[6];
        _Data[3] -= tmp[4]*src[4]+tmp[9]*src[5]+tmp[10]*src[6];
        _Data[4] = tmp[1]*src[1]+tmp[2]*src[2]+tmp[5]*src[3];
        _Data[4] -= tmp[0]*src[1]+tmp[3]*src[2]+tmp[4]*src[3];
        _Data[5] = tmp[0]*src[0]+tmp[7]*src[2]+tmp[8]*src[3];
        _Data[5] -= tmp[1]*src[0]+tmp[6]*src[2]+tmp[9]*src[3];
        _Data[6] = tmp[3]*src[0]+tmp[6]*src[1]+tmp[11]*src[3];
        _Data[6] -= tmp[2]*src[0]+tmp[7]*src[1]+tmp[10]*src[3];
        _Data[7] = tmp[4]*src[0]+tmp[9]*src[1]+tmp[10]*src[2];
        _Data[7] -= tmp[5]*src[0]+tmp[8]*src[1]+tmp[11]*src[2];

        // calculate pairs for second 8 elements (cofactors)
        tmp[0] = src[2]*src[7];
        tmp[1] = src[3]*src[6];
        tmp[2] = src[1]*src[7];
        tmp[3] = src[3]*src[5];
        tmp[4] = src[1]*src[6];
        tmp[5] = src[2]*src[5];
        tmp[6] = src[0]*src[7];
        tmp[7] = src[3]*src[4];
        tmp[8] = src[0]*src[6];
        tmp[9] = src[2]*src[4];
        tmp[10] = src[0]*src[5];
        tmp[11] = src[1]*src[4];

        // calculate second 8 elements (cofactors)
        _Data[8] = tmp[0]*src[13]+tmp[3]*src[14]+tmp[4]*src[15];
        _Data[8] -= tmp[1]*src[13]+tmp[2]*src[14]+tmp[5]*src[15];
        _Data[9] = tmp[1]*src[12]+tmp[6]*src[14]+tmp[9]*src[15];
        _Data[9] -= tmp[0]*src[12]+tmp[7]*src[14]+tmp[8]*src[15];
        _Data[10] = tmp[2]*src[12]+tmp[7]*src[13]+tmp[10]*src[15];
        _Data[10] -= tmp[3]*src[12]+tmp[6]*src[13]+tmp[11]*src[15];
        _Data[11] = tmp[5]*src[12]+tmp[8]*src[13]+tmp[11]*src[14];
        _Data[11] -= tmp[4]*src[12]+tmp[9]*src[13]+tmp[10]*src[14];
        _Data[12] = tmp[2]*src[10]+tmp[5]*src[11]+tmp[1]*src[9];
        _Data[12] -= tmp[4]*src[11]+tmp[0]*src[9]+tmp[3]*src[10];
        _Data[13] = tmp[8]*src[11]+tmp[0]*src[8]+tmp[7]*src[10];
        _Data[13] -= tmp[6]*src[10]+tmp[9]*src[11]+tmp[1]*src[8];
        _Data[14] = tmp[6]*src[9]+tmp[11]*src[11]+tmp[3]*src[8];
        _Data[14] -= tmp[10]*src[11]+tmp[2]*src[8]+tmp[7]*src[9];
        _Data[15] = tmp[10]*src[10]+tmp[4]*src[8]+tmp[9]*src[9];
        _Data[15] -= tmp[8]*src[9]+tmp[11]*src[10]+tmp[5]*src[8];

        // calculate determinant
        det = src[0]*_Data[0]+src[1]*_Data[1]+src[2]*_Data[2]+src[3]*_Data[3];

        COFFEE_Assert(!IsEqual(det, 0.0f), core::ERROR_CODE_IncorrectUsage,
            "basic::Matrix::SetInversed failed");

        // calculate matrix inverse
        det = 1.0f/det;
        
        for (uint32 j=0 ; j<16 ; ++j)
            _Data[j] *= det;
    }

    //--------------------------------------------------------------------------------------------//

    void Matrix::SetTransposed(const Matrix& other)
    {
        const real* mat = other._Data;
        for (uint32 i=0 ; i<4 ; ++i)
        {
            _Data[i] = mat[i*4];
            _Data[i+4] = mat[i*4+1];
            _Data[i+8] = mat[i*4+2];
            _Data[i+12] = mat[i*4+3];
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Matrix::SetFromLookAt(const Vector3& position, const Vector3& target, const Vector3& up_vector)
    {
        // Improve perf maybe, but it works at least
        Matrix matrix;
        Vector3 view, axis;
        Quaternion quat_roll, quat_yaw;
        Angle roll, yaw;

        view = position-target;
        view.Normalize();

        if (view==Vector3::YAxis || view==-Vector3::YAxis)
        {
            view.X = 0.001f;
            view.Z = 0.001f;
            view.Normalize();
        }

        axis = view.GetCrossProduct(up_vector);
        axis.Normalize();

        roll = view.GetAngle(Vector3(0.0f, -1.0f, 0.0f))-Pi/2.0f;
        yaw = -axis.GetAngle(Vector3(-1.0f, 0.0f, 0.0f))-Pi;

        if (target.X<position.X)
            yaw = -yaw;

        quat_roll.SetFromAxisAndAngle(Vector3(1.0f, 0.0f, 0.0f), roll);
        quat_yaw.SetFromAxisAndAngle(up_vector, yaw);
        Set(position, quat_yaw*quat_roll);
    }

    //--------------------------------------------------------------------------------------------//

    void Matrix::SetFromXRotation(const Angle& angle)
    {
        real cosinus = angle.GetCosinus();
        real sinus = angle.GetSinus();
        SetIdentity();
        _Data[5] = cosinus;
        _Data[6] = sinus;
        _Data[9] = -sinus;
        _Data[10] = cosinus;
    }

    //--------------------------------------------------------------------------------------------//

    void Matrix::SetFromYRotation(const Angle& angle)
    {
        real cosinus = angle.GetCosinus();
        real sinus = angle.GetSinus();
        SetIdentity();
        _Data[0] = cosinus;
        _Data[2] = -sinus;
        _Data[8] = sinus;
        _Data[10] = cosinus;
    }

    //--------------------------------------------------------------------------------------------//

    void Matrix::SetFromZRotation(const Angle& angle)
    {
        real cosinus = angle.GetCosinus();
        real sinus = angle.GetSinus();
        SetIdentity();
        _Data[0] = cosinus;
        _Data[1] = sinus;
        _Data[4] = -sinus;
        _Data[5] = cosinus;
    }

    //--------------------------------------------------------------------------------------------//

    void Matrix::Serialize(coffee::meta::Stream& stream)
    {
        for (int32 index=0;index<16;++index)
            COFFEE_SerializeScalar(&_Data[index], real);
    }

    //-VARIABLES----------------------------------------------------------------------------------//

    const real Matrix::_IdentityData[] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    const Matrix Matrix::Identity;
}
}
