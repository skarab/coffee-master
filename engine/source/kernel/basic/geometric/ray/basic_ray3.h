#ifndef _COFFEE_BASIC_GEOMETRIC_RAY3_H_
#define _COFFEE_BASIC_GEOMETRIC_RAY3_H_

#include "coffee_includes.h"
#include "kernel/basic/math/basic_math.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Simple ray in 3D
    ///
    /// Ray is defined by an origin and a direction.
    /// The direction must be normalized.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Ray3 : public meta::Object
    {
        COFFEE_Type(Ray3);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        /// Construct a ray at origin zero and using X axis as direction
        Ray3();

        /// Construct copying existing ray
        Ray3(const Ray3& other);

        /// Construct the ray from origin and normalized direction
        Ray3(const Vector3& origin, const Vector3& direction);

        //-OPERATORS------------------------------------------------------------------------------//

        /// Assign values from other ray
        Ray3& operator = (const Ray3& other);

        //-OPERATIONS-----------------------------------------------------------------------------//

        /// Set from origin and normalized direction
        void Set(const Vector3& origin, const Vector3& direction);
        
        /// Set from the ray defined by origin to target
        void SetFromTarget(const Vector3& origin, const Vector3& target);
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Vector3 Origin;
        Vector3 Direction;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Ray3);
}
}
#endif
