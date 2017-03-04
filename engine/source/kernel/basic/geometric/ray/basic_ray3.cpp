#include "kernel/basic/geometric/ray/basic_ray3.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::Ray3);
        COFFEE_Attribute(basic::Vector3, Origin, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Vector3, Direction, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Ray3::Ray3() :
        Origin(),
        Direction(Vector3::XAxis)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Ray3::Ray3(const Ray3& other) :
        Origin(other.Origin),
        Direction(other.Direction)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Ray3::Ray3(const Vector3& origin, const Vector3& direction) :
        Origin(origin),
        Direction(direction)
    {
        COFFEE_Assert(Direction.IsNormalized(), core::ERROR_CODE_IncorrectUsage, "Direction is not normalized");
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    Ray3& Ray3::operator = (const Ray3& other)
    {
        Origin = other.Origin;
        Direction = other.Direction;
        return *this;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Ray3::Set(const Vector3& origin, const Vector3& direction)
    {
        COFFEE_Assert(direction.IsNormalized(), core::ERROR_CODE_IncorrectUsage, "Direction is not normalized");
        Origin = origin;
        Direction = direction;
    }

    //--------------------------------------------------------------------------------------------//

    void Ray3::SetFromTarget(const Vector3& origin, const Vector3& target)
    {
        COFFEE_Assert(target!=origin, core::ERROR_CODE_IncorrectUsage, "Target is equal to origin");
        Origin = origin;
        Direction = target-origin;
        Direction.Normalize();
    }

}
}
