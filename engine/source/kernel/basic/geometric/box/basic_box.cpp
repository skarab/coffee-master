#include "kernel/basic/geometric/box/basic_box.h"
#include "kernel/basic/geometric/sphere/basic_sphere.h"
#include "kernel/basic/geometric/ray/basic_ray3.h"
#include "kernel/basic/geometric/plane/basic_plane.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::Box);
        COFFEE_Attribute(basic::Vector3, Center, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Vector3, Size, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Box::Box()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Box::Box(const Vector3& center, const Vector3& size) :
        Center(center),
        Size(size)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Box::Box(const Box& other) :
        Center(other.Center),
        Size(other.Size)
    {
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    Box& Box::operator = (const Box& other)
    {
        Center = other.Center;
        Size = other.Size;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Box& Box::operator *= (const Matrix& transform)
    {
        if (IsEmpty())
        {
            Center *= transform;
        }
        else
        {
            Vector3 minimum, maximum;
            GetExtent(minimum, maximum);            
            AddPoint(minimum*transform, true);
            AddPoint(Vector3(maximum.X, minimum.Y, minimum.Z)*transform);
            AddPoint(Vector3(minimum.X, maximum.Y, minimum.Z)*transform);
            AddPoint(Vector3(minimum.X, minimum.Y, maximum.Z)*transform);
            AddPoint(Vector3(maximum.X, minimum.Y, maximum.Z)*transform);
            AddPoint(Vector3(maximum.X, maximum.Y, minimum.Z)*transform);
            AddPoint(Vector3(minimum.X, maximum.Y, maximum.Z)*transform);
            AddPoint(maximum*transform);
        }
        return *this;
    }
    
    //--------------------------------------------------------------------------------------------//

    Box Box::operator * (const Matrix& transform) const
    {
        Box box(*this);
        box *= transform;
        return box;
    }

    //--------------------------------------------------------------------------------------------//

    bool Box::operator == (const Box& other) const
    {
        return Center==other.Center && Size==other.Size;
    }

    //--------------------------------------------------------------------------------------------//

    bool Box::operator != (const Box& other) const
    {
        return Center!=other.Center || Size!=other.Size;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Box::IsEmpty() const
    {
        return Size.IsZero();
    }

    //--------------------------------------------------------------------------------------------//

    bool Box::IsPointInside(const Vector3& point) const
    {
        if (IsEmpty())
            return false;
        return (point>=GetMinimum()) && (point<=GetMaximum());
    }

    //--------------------------------------------------------------------------------------------//

    // Simple ray-box intersection test, coming from here :
    // http://www.3dkingdoms.com/weekly/weekly.php?a=3

    inline bool _GetIntersection(basic::Vector3 &Hit, real fDst1, real fDst2, basic::Vector3 P1, basic::Vector3 P2)
    {
        if (fDst1==fDst2 || fDst1*fDst2>=0.0f)
            return false;
        Hit = P1-(P2-P1)*(fDst1/(fDst2-fDst1));
        return true;
    }

    inline bool _InBox(basic::Vector3 Hit, basic::Vector3 B1, basic::Vector3 B2, const int Axis)
    {
        return (Axis==1 && Hit.Z>B1.Z && Hit.Z<B2.Z && Hit.Y>B1.Y && Hit.Y<B2.Y)
            || (Axis==2 && Hit.Z>B1.Z && Hit.Z<B2.Z && Hit.X>B1.X && Hit.X<B2.X)
            || (Axis==3 && Hit.X>B1.X && Hit.X<B2.X && Hit.Y>B1.Y && Hit.Y<B2.Y);
    }

    bool CheckLineBox(basic::Vector3 &Hit, basic::Vector3 B1, basic::Vector3 B2, basic::Vector3 L1, basic::Vector3 L2)
    {
        if ((L2.X<B1.X && L1.X<B1.X) || (L2.X>B2.X && L1.X>B2.X) || (L2.Y<B1.Y && L1.Y<B1.Y)
            || (L2.Y>B2.Y && L1.Y>B2.Y) || (L2.Z<B1.Z && L1.Z<B1.Z) || (L2.Z>B2.Z && L1.Z>B2.Z))
        {
            return false;
        }
        
        if (L1.X>B1.X && L1.X<B2.X && L1.Y>B1.Y && L1.Y<B2.Y && L1.Z>B1.Z && L1.Z<B2.Z) 
        {
            Hit = L1; 
            return true;
        }

        return ((_GetIntersection(Hit, L1.X-B1.X, L2.X-B1.X, L1, L2) && _InBox(Hit, B1, B2, 1))
            || (_GetIntersection(Hit, L1.Y-B1.Y, L2.Y-B1.Y, L1, L2) && _InBox(Hit, B1, B2, 2)) 
            || (_GetIntersection(Hit, L1.Z-B1.Z, L2.Z-B1.Z, L1, L2) && _InBox(Hit, B1, B2, 3)) 
            || (_GetIntersection(Hit, L1.X-B2.X, L2.X-B2.X, L1, L2) && _InBox(Hit, B1, B2, 1)) 
            || (_GetIntersection(Hit, L1.Y-B2.Y, L2.Y-B2.Y, L1, L2) && _InBox(Hit, B1, B2, 2)) 
            || (_GetIntersection(Hit, L1.Z-B2.Z, L2.Z-B2.Z, L1, L2) && _InBox(Hit, B1, B2, 3)));
    }

    //--------------------------------------------------------------------------------------------//

    bool Box::FindRayIntersection(Vector3& intersection, const Ray3& ray) const
    {
        return CheckLineBox(intersection, GetMinimum(), GetMaximum(), ray.Origin,
            ray.Origin+ray.Direction*1000.0f);
    }
        
    //--------------------------------------------------------------------------------------------//

    void Box::GetExtent(Vector3& minimum, Vector3& maximum) const
    {
        minimum = Center-Size/2.0f;
        maximum = Center+Size/2.0f;
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Box::GetMinimum() const
    {
        return Center - Size/2.0f;
    }

    //--------------------------------------------------------------------------------------------//

    Vector3 Box::GetMaximum() const
    {
        return Center + Size/2.0f;
    }

    //--------------------------------------------------------------------------------------------//

    void Box::GetCorners(Vector<Vector3>& corners) const
    {
        Vector3 minimum;
        Vector3 maximum;
        GetExtent(minimum, maximum);        
        corners.Resize(8);
        corners[0] = minimum;
        corners[1].Set(maximum.X, minimum.Y, minimum.Z);
        corners[2].Set(minimum.X, maximum.Y, minimum.Z);
        corners[3].Set(minimum.X, minimum.Y, maximum.Z);
        corners[4].Set(maximum.X, minimum.Y, maximum.Z);
        corners[5].Set(maximum.X, maximum.Y, minimum.Z);
        corners[6].Set(minimum.X, maximum.Y, maximum.Z);
        corners[7] = maximum;        
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Box::Set(const Vector3& center, const Vector3& size)
    {
        Center = center;
        Size = size;
    }

    //--------------------------------------------------------------------------------------------//

    void Box::SetExtent(const Vector3& minimum, const Vector3& maximum)
    {
        Center = (maximum+minimum)/2.0f;
        Size = maximum-minimum;
        Size.X = Absolute(Size.X);
        Size.Y = Absolute(Size.Y);
        Size.Z = Absolute(Size.Z);
    }

    //--------------------------------------------------------------------------------------------//

    void Box::SetEmpty()
    {
        Center = Vector3::Zero;
        Size = Vector3::Zero;
    }

    //--------------------------------------------------------------------------------------------//

    void Box::AddPoint(const Vector3& point, bool it_has_to_empty)
    {
        if (it_has_to_empty)
        {
            Center = point;
            Size = Vector3::Zero;
        }
        else
        {
            Vector3 minimum, maximum;
            GetExtent(minimum, maximum);
            for (uint32 i=0 ; i<3 ; ++i)
            {
                if (point[i]<minimum[i]) minimum[i] = point[i];
                if (point[i]>maximum[i]) maximum[i] = point[i];
            }
            SetExtent(minimum, maximum);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Box::AddSphere(const Sphere& sphere, bool it_has_to_empty)
    {
        if (it_has_to_empty)
        {
            Center = sphere.Center;
            Size = sphere.Radius * 2.0f;
        }
        else
        {
            Vector3 minimum, maximum;
            GetExtent(minimum, maximum);
            Vector3 min = sphere.Center-sphere.Radius;
            Vector3 max = sphere.Center+sphere.Radius;
            for (uint32 i=0 ; i<3 ; ++i)
            {
                if (min[i]<minimum[i]) minimum[i] = min[i];
                if (max[i]>maximum[i]) maximum[i] = max[i];
            }
            SetExtent(minimum, maximum);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Box::AddBox(const Box& other, bool it_has_to_empty)
    {
        if (it_has_to_empty)
        {
            Center = other.Center;
            Size = other.Size;
        }
        else
        {
            Vector3 minimum, maximum;
            GetExtent(minimum, maximum);
            Vector3 min = other.GetMinimum();
            Vector3 max = other.GetMaximum();
            for (uint32 i=0 ; i<3 ; ++i)
            {
                if (min[i]<minimum[i]) minimum[i] = min[i];
                if (max[i]>maximum[i]) maximum[i] = max[i];
            }
            SetExtent(minimum, maximum);
        }
    }
    
}
}
