#ifndef _COFFEE_BASIC_GEOMETRIC_SPHERE_H_
#define _COFFEE_BASIC_GEOMETRIC_SPHERE_H_

#include "coffee_includes.h"
#include "kernel/basic/math/basic_math.h"

namespace coffee
{
namespace basic
{
    //-FORWARDS-----------------------------------------------------------------------------------//

    class Box;

    //--------------------------------------------------------------------------------------------//
    /// Sphere defined by position and radius
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Sphere : public meta::Object
    {
        COFFEE_Type(Sphere);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        /// Construct an empty sphere
        Sphere();

        /// Construct a sphere from given center and radius
        Sphere(const Vector3& center, real radius);

        /// Construct copying existing sphere
        Sphere(const Sphere& other);

        //-OPERATORS------------------------------------------------------------------------------//

        /// Assign other sphere values
        Sphere& operator = (const Sphere& other);

        /// Assign the transformed sphere
        Sphere& operator *= (const Matrix& transform);

        /// Compute the transformed sphere
        Sphere operator * (const Matrix& transform) const;
        
        /// Check if the two spheres are equal
        bool operator == (const Sphere& other) const;

        /// Check if the two spheres are different
        bool operator != (const Sphere& other) const;

        //-QUERIES--------------------------------------------------------------------------------//

        /// Check if the sphere is empty
        bool IsEmpty() const;

        /// Check if the sphere contains the point
        bool IsPointInside(const Vector3& point) const;

        /// Check if two spheres overlap
        bool IsOverlapping(const Sphere& other) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

         /// Set sphere to specified values
        void Set(const Vector3& center, real radius);
        
        /// Set sphere as empty
        void SetEmpty();
        
        /// Enlarge the sphere by adding a point, require to empty it the first time to set the start position
        void AddPoint(const Vector3& point, bool it_has_to_empty=false);
        
        /// Enlarge the sphere by adding a sphere, require to empty it the first time to set the start position
        void AddSphere(const Sphere& other, bool it_has_to_empty=false);
        
        /// Enlarge the sphere by adding a box, require to empty it the first time to set the start position
        void AddBox(const Box& box, bool it_has_to_empty=false);
       
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Vector3 Center;
        real Radius;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Sphere);
}
}
#endif
