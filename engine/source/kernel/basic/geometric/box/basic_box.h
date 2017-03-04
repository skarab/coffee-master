#ifndef _COFFEE_BASIC_GEOMETRIC_BOX_H_
#define _COFFEE_BASIC_GEOMETRIC_BOX_H_

#include "coffee_includes.h"
#include "kernel/basic/math/basic_math.h"
#include "kernel/basic/container/basic_containers.h"

namespace coffee
{
namespace basic
{
    //-FORWARDS-----------------------------------------------------------------------------------//

    class Sphere;
    class Ray3;

    //--------------------------------------------------------------------------------------------//
    /// Axis aligned 3D box
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Box : public meta::Object
    {
        COFFEE_Type(Box);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        /// Construct an empty box
        Box();

        /// Construct a box from given center and size
        Box(const Vector3& center, const Vector3& size);

        /// Construct copying existing box
        Box(const Box& other);

        //-OPERATORS------------------------------------------------------------------------------//

        /// Assign other box values
        Box& operator = (const Box& other);

        /// Assign the transformed axis aligned box
        Box& operator *= (const Matrix& transform);

        /// Compute the axis aligned transformed box
        Box operator * (const Matrix& transform) const;

        /// Check if the two boxes are equal
        bool operator == (const Box& other) const;

        /// Check if the two boxes are different
        bool operator != (const Box& other) const;

        //-QUERIES--------------------------------------------------------------------------------//

        /// Check if the box is empty
        bool IsEmpty() const;

        /// Check if the box contains the point
        bool IsPointInside(const Vector3& point) const;

        /// Compute the intersection with the ray
        bool FindRayIntersection(Vector3& intersection, const Ray3& ray) const;

        /// Get the extent of the box
        void GetExtent(Vector3& minimum, Vector3& maximum) const;

        /// Get the minimum position of the box
        Vector3 GetMinimum() const;

        /// Get the maximum position of the box
        Vector3 GetMaximum() const;
        
        /// Get the box corners
        void GetCorners(Vector<Vector3>& corners) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        /// Set box to specified values
        void Set(const Vector3& center, const Vector3& size);

        /// Set box from the extent values
        void SetExtent(const Vector3& minimum, const Vector3& maximum);

        /// Set box as empty
        void SetEmpty();
        
        /// Enlarge the box by adding a point, require to empty it the first time to set the start position
        void AddPoint(const Vector3& point, bool it_has_to_empty=false);
        
        /// Enlarge the box by adding a sphere, require to empty it the first time to set the start position
        void AddSphere(const Sphere& other, bool it_has_to_empty=false);
        
        /// Enlarge the box by adding a box, require to empty it the first time to set the start position
        void AddBox(const Box& box, bool it_has_to_empty=false);
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Vector3 Center;
        Vector3 Size;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Box);
}
}
#endif
