#ifndef _COFFEE_BASIC_MATH_MATRIX_H_
#define _COFFEE_BASIC_MATH_MATRIX_H_

#include "coffee_includes.h"
#include "kernel/basic/math/vector/basic_vector.h"
#include "kernel/basic/math/angle/basic_angle.h"

namespace coffee
{
namespace basic
{
    //-FORWARDS-----------------------------------------------------------------------------------//

    class Quaternion;

    //--------------------------------------------------------------------------------------------//
    /// Matrix 4x4
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Matrix : public meta::Object
    {
        COFFEE_Type(Matrix);
        
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        /// Construct a matrix set to identity
        Matrix();

        /// Construct copying other
        Matrix(const Matrix& other);

        /// Construct a matrix using orientation from 'quaternion'
        Matrix(const Quaternion& quaternion);

        //-OPERATORS------------------------------------------------------------------------------//

        /// Assign the other value
        Matrix& operator= (const Matrix& other);

        /// Set the whole matrix as a rotation matrix from 'quaternion'
        Matrix& operator= (const Quaternion& quaternion);

        /// Transform self using other
        Matrix& operator*= (const Matrix& other);

        /// Construct a matrix which is self transformed by other
        Matrix operator* (const Matrix& other) const;

        /// Transform a vector
        Vector3 operator* (const Vector3& vector) const;

        /// Transform a vector4
        Vector4 operator* (const Vector4& vector) const;

        //-ACCESSORS------------------------------------------------------------------------------//

        /// Read internal matrix data
        const real* GetData() const;
        
        /// Get direct access on internal matrix data
        real* GetData();

        //-QUERIES--------------------------------------------------------------------------------//

        /// Extract the translation from the matrix
        Vector3 GetTranslation() const;
        
        /// Extract the rotation from the matrix
        Quaternion GetRotation() const;
        
        /// Extract the non-uniform scale from the matrix
        Vector3 GetScale() const;
        
        /// Extract the X axis
        Vector3 GetXAxis() const;
        
        /// Extract the Y axis
        Vector3 GetYAxis() const;

        /// Extract the Z axis
        Vector3 GetZAxis() const;
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        /// Translate the matrix
        void Translate(const Vector3& translation);

        /// Scale non-uniformly the matrix
        void Scale(const Vector3& scale);

        /// Unscale the matrix (uses extracted non uniform scale)
        void UnScale();

        /// Invert the matrix
        void Invert();

        /// Transpose the matrix
        void Transpose();

        /// Set matrix to identity
        void SetIdentity();

        /// Set the matrix using translation, rotation, scale parameters
        void Set(const Vector3& translation, const Quaternion& rotation, const Vector3& scale = Vector3::One);
        
        /// Set to the inverse of other
        void SetInversed(const Matrix& other);

        /// Set to the transpose of other
        void SetTransposed(const Matrix& other);

        /// Set from a given position, the target used to compute z-axis orientation, the up-vector defining the z-axis rotation 
        void SetFromLookAt(const Vector3& position, const Vector3& target, const Vector3& up_vector);
        
        /// Set from rotation around X
        void SetFromXRotation(const Angle& angle);

        /// Set from rotation around Y
        void SetFromYRotation(const Angle& angle);

        /// Set from rotation around Z
        void SetFromZRotation(const Angle& angle);
        
        /// Custom serialization
        void Serialize(coffee::meta::Stream& stream);

        //-VARIABLES------------------------------------------------------------------------------//

        /// Pre-defined identity matrix helper
        static COFFEE_STATIC_API const Matrix Identity;

    private:

        //-VARIABLES------------------------------------------------------------------------------//

        static const real _IdentityData[];

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        real _Data[16];
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Matrix);
}
}
#endif
