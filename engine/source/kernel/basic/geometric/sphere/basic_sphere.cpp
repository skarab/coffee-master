#include "kernel/basic/geometric/box/basic_box.h"
#include "kernel/basic/geometric/sphere/basic_sphere.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::Sphere);
        COFFEE_Attribute(basic::Vector3, Center, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, Radius, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Sphere::Sphere() :
        Radius(0.0f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Sphere::Sphere(const Vector3& center, real radius) :
        Center(center),
        Radius(radius)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Sphere::Sphere(const Sphere& other) :
        Center(other.Center),
        Radius(other.Radius)
    {
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    Sphere& Sphere::operator = (const Sphere& other)
    {
        Center = other.Center;
        Radius = other.Radius;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Sphere& Sphere::operator *= (const Matrix& transform)
    {
        Center *= transform;
        Radius *= transform.GetScale().GetMaximum();    
        return *this;
    }
    
    //--------------------------------------------------------------------------------------------//

    Sphere Sphere::operator * (const Matrix& transform) const
    {
        Sphere sphere(*this);
        sphere *= transform;
        return sphere;
    }

    //--------------------------------------------------------------------------------------------//

    bool Sphere::operator == (const Sphere& other) const
    {
        return IsEqual(Radius, other.Radius) && Center==other.Center;
    }

    //--------------------------------------------------------------------------------------------//

    bool Sphere::operator != (const Sphere& other) const
    {
        return IsNotEqual(Radius, other.Radius) || Center!=other.Center;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Sphere::IsEmpty() const
    {
        return IsEqual(Radius, 0.0f);
    }

    //--------------------------------------------------------------------------------------------//

    bool Sphere::IsPointInside(const Vector3& point) const
    {
        if (IsEmpty())
            return false;
        return point.GetDistance(Center)<=Radius;
    }

    //--------------------------------------------------------------------------------------------//

    bool Sphere::IsOverlapping(const Sphere& other) const
    {
        if (IsEmpty() || other.IsEmpty())
            return false;
        return other.Center.GetDistance(Center)<=other.Radius+Radius;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Sphere::Set(const Vector3& center, real radius)
    {
        Center = center;
        Radius = radius;
    }

    //--------------------------------------------------------------------------------------------//

    void Sphere::SetEmpty()
    {
        Center = Vector3::Zero;
        Radius = 0.0f;
    }

    //--------------------------------------------------------------------------------------------//

    void Sphere::AddPoint(const Vector3& point, bool it_has_to_empty)
    {
        if (it_has_to_empty)
        {
            Center = point;
            Radius = 0.0f;
        }
        else
        {
            if (point.GetDistance(Center)>Radius)
            {
                Vector3 normal = point-Center;
                normal.Normalize();
                Center = (point-normal*Radius)/2.0f;
                Radius = point.GetDistance(Center);
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Sphere::AddBox(const Box& box, bool it_has_to_empty)
    {
        if (it_has_to_empty)
        {
            Center = box.Center;
            Radius = box.Size.GetMaximum();
        }
        else
        {
            Sphere sphere;
            sphere.AddBox(box, true);
            AddSphere(sphere);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Sphere::AddSphere(const Sphere& other, bool it_has_to_empty)
    {
        if (it_has_to_empty)
        {
            Center = other.Center;
            Radius = other.Radius;
        }
        else
        {
            Vector3 normal(other.Center-Center);
            normal.Normalize();
            Vector3 minimum(-normal*Radius);
            Vector3 maximum(other.Center+normal*other.Radius);
            Center = (minimum+maximum)/2.0f;
            Radius = minimum.GetDistance(Center);
        }
    }

}
}
