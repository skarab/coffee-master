#include "kernel/basic/geometric/frustum/basic_frustum3.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::Frustum3);
        COFFEE_Attribute(<basic::Plane>, _Planes, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(<basic::Vector3>, _Corners, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Frustum3::Frustum3()
    {
        _Planes.Resize(FRUSTUM3_PLANE_Count);
        _Corners.Resize(FRUSTUM3_CORNER_Count);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const Plane& Frustum3::GetPlane(FRUSTUM3_PLANE plane) const
    {
        return _Planes[(uint32)plane];
    }

    //--------------------------------------------------------------------------------------------//

    const Vector3& Frustum3::GetCorner(FRUSTUM3_CORNER corner) const
    {
        return _Corners[(uint32)corner];
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Frustum3::IsPointInside(const Vector3& point) const
    {
        for (uint32 plane_index=0 ; plane_index<FRUSTUM3_PLANE_Count ; ++plane_index)
        {
            if (_Planes[plane_index].ComputeDistanceFromPoint(point)<0.0f)
                return false;
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Frustum3::IsSphereOverlapping(const Sphere& sphere) const
    {
        for(uint32 plane_index=0 ; plane_index<FRUSTUM3_PLANE_Count ; ++plane_index)
        {
            if (_Planes[plane_index].ComputeDistanceFromPoint(sphere.Center)<-sphere.Radius)
                return false;
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Frustum3::IsBoxOverlapping(const Box& box) const
    {
        Vector<Vector3> corners;
        box.GetCorners(corners);
        for (uint32 plane=0 ; plane<6 ; ++plane)
        {
            uint32 in_count = 8;
            for (int i=0 ; i<8 ; ++i)
            {
                if (_Planes[plane].ComputeDistanceFromPoint(corners[i])<0.0f)
                    --in_count;
            }
            if (in_count==0)
                return false;
        }
        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Frustum3::Set(const Matrix& world_to_camera_matrix, const Matrix& camera_to_viewport_matrix)
    {
        const real* proj_matrix = camera_to_viewport_matrix.GetData();
        const real* modl_matrix = world_to_camera_matrix.GetData();
        real clip[16];
        uint32 corner_index;

        clip[0] = modl_matrix[0] * proj_matrix[0];
        clip[4] = modl_matrix[4] * proj_matrix[0];
        clip[8] = modl_matrix[8] * proj_matrix[0];
        clip[12] = modl_matrix[12] * proj_matrix[0];
        clip[1] = modl_matrix[1] * proj_matrix[5];
        clip[5] = modl_matrix[5] * proj_matrix[5];
        clip[9] = modl_matrix[9] * proj_matrix[5];
        clip[13] = modl_matrix[13] * proj_matrix[5];
        clip[2] = modl_matrix[2] * proj_matrix[10] + modl_matrix[3] * proj_matrix[14];
        clip[6] = modl_matrix[6] * proj_matrix[10] + modl_matrix[7] * proj_matrix[14];
        clip[10] = modl_matrix[10] * proj_matrix[10] + modl_matrix[11] * proj_matrix[14];
        clip[14] = modl_matrix[14] * proj_matrix[10] + modl_matrix[15] * proj_matrix[14];
        clip[3] = modl_matrix[2] * proj_matrix[11];
        clip[7] = modl_matrix[6] * proj_matrix[11];
        clip[11] = modl_matrix[10] * proj_matrix[11];
        clip[15] = modl_matrix[14] * proj_matrix[11];

        _Planes[FRUSTUM3_PLANE_Right].Vect.Set(clip[3]-clip[0], clip[7]-clip[4], clip[11]-clip[8], clip[12]-clip[15]);
        _Planes[FRUSTUM3_PLANE_Left].Vect.Set(clip[3]+clip[0], clip[7]+clip[4], clip[11]+clip[8], -clip[12]-clip[15]);
        _Planes[FRUSTUM3_PLANE_Top].Vect.Set(clip[3]+clip[1], clip[7]+clip[5], clip[11]+clip[9], -clip[13]-clip[15]);
        _Planes[FRUSTUM3_PLANE_Bottom].Vect.Set(clip[3]-clip[1], clip[7]-clip[5], clip[11]-clip[9], clip[13]-clip[15]);
        _Planes[FRUSTUM3_PLANE_Near].Vect.Set(clip[3]-clip[2], clip[7]-clip[6], clip[11]-clip[10], clip[14]-clip[15]);
        _Planes[FRUSTUM3_PLANE_Far].Vect.Set(clip[3]+clip[2], clip[7]+clip[6], clip[11]+clip[10], -clip[14]-clip[15]);

        if (!IsEqual(_Planes[FRUSTUM3_PLANE_Right].Vect.GetSquareNorm(), 0.0f))
            _Planes[FRUSTUM3_PLANE_Right].Vect.Normalize();
        if (!IsEqual(_Planes[FRUSTUM3_PLANE_Left].Vect.GetSquareNorm(), 0.0f))
            _Planes[FRUSTUM3_PLANE_Left].Vect.Normalize();
        if (!IsEqual(_Planes[FRUSTUM3_PLANE_Top].Vect.GetSquareNorm(), 0.0f))
            _Planes[FRUSTUM3_PLANE_Top].Vect.Normalize();
        if (!IsEqual(_Planes[FRUSTUM3_PLANE_Bottom].Vect.GetSquareNorm(), 0.0f))
            _Planes[FRUSTUM3_PLANE_Bottom].Vect.Normalize();
        if (!IsEqual(_Planes[FRUSTUM3_PLANE_Near].Vect.GetSquareNorm(), 0.0f))
            _Planes[FRUSTUM3_PLANE_Near].Vect.Normalize();
        if (!IsEqual(_Planes[FRUSTUM3_PLANE_Far].Vect.GetSquareNorm(), 0.0f))
            _Planes[FRUSTUM3_PLANE_Far].Vect.Normalize();

        Matrix viewport_to_camera_matrix;
        viewport_to_camera_matrix.SetInversed(camera_to_viewport_matrix);

        _Corners[FRUSTUM3_CORNER_NearTopRight].Set(1.0f, 1.0f, 1.0f);
        _Corners[FRUSTUM3_CORNER_NearTopLeft].Set(- 1.0f, 1.0f, 1.0f);
        _Corners[FRUSTUM3_CORNER_NearBottomRight].Set(1.0f, - 1.0f, 1.0f);
        _Corners[FRUSTUM3_CORNER_NearBottomLeft].Set(- 1.0f, - 1.0f, 1.0f);

        _Corners[FRUSTUM3_CORNER_FarTopRight].Set(1.0f, 1.0f, - 1.0f);
        _Corners[FRUSTUM3_CORNER_FarTopLeft].Set(- 1.0f, 1.0f, - 1.0f);
        _Corners[FRUSTUM3_CORNER_FarBottomRight].Set(1.0f, - 1.0f, - 1.0f);
        _Corners[FRUSTUM3_CORNER_FarBottomLeft].Set(- 1.0f, - 1.0f, - 1.0f);

        for (corner_index=0 ; corner_index<FRUSTUM3_CORNER_Count ; ++corner_index)
        {
            Vector4 vect = _Corners[corner_index];
            vect *= viewport_to_camera_matrix;
            _Corners[corner_index].Set(vect.X, vect.Y, vect.Z);
        }
    }

}
}
