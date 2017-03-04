#ifndef _COFFEE_BASIC_GEOMETRIC_FRUSTUM3_H_
#define _COFFEE_BASIC_GEOMETRIC_FRUSTUM3_H_

#include "coffee_includes.h"
#include "kernel/basic/container/basic_containers.h"
#include "kernel/basic/math/basic_math.h"
#include "kernel/basic/geometric/plane/basic_plane.h"
#include "kernel/basic/geometric/frustum/basic_frustum3_plane.h"
#include "kernel/basic/geometric/box/basic_box.h"
#include "kernel/basic/geometric/sphere/basic_sphere.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Frustum3 handling visibility culling based on view matrices
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Frustum3 : public meta::Object
    {
        COFFEE_Type(Frustum3);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        /// Construct an empty frustum
        Frustum3();

        //-ACCESSORS------------------------------------------------------------------------------//

        /// Get one of the planes of the frustum
        const Plane& GetPlane(FRUSTUM3_PLANE plane) const;

        /// Get one of the corners of the frustum
        const Vector3& GetCorner(FRUSTUM3_CORNER corner) const;

        //-QUERIES--------------------------------------------------------------------------------//

        /// Check if the point is inside the frustum
        bool IsPointInside(const Vector3& point) const;
        
        /// Check if the sphere is overlapping the frustum
        bool IsSphereOverlapping(const Sphere& sphere) const;

        /// Check if the box is overlapping the frustum
        bool IsBoxOverlapping(const Box& box) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        /// Set frustum based on view matrices
        void Set(const Matrix& world_to_camera, const Matrix& camera_to_viewport);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Vector<Plane> _Planes;
        basic::Vector<Vector3> _Corners;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Frustum3);
}
}
#endif
