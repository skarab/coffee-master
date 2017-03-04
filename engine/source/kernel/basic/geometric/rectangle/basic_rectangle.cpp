#include "kernel/basic/geometric/rectangle/basic_rectangle.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::Rectangle);
        COFFEE_Attribute(basic::Vector2i, Position, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Vector2i, Size, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Rectangle::Rectangle()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Rectangle::Rectangle(const Rectangle& other) :
        Position(other.Position),
        Size(other.Size)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Rectangle::Rectangle(const Vector2i& position, const Vector2i& size) :
        Position(position),
        Size(size)
    {
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    Rectangle& Rectangle::operator = (const Rectangle& other)
    {
        Position = other.Position;
        Size = other.Size;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Rectangle& Rectangle::operator -= (const Rectangle& other)
    {
        *this = (*this - other);
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Rectangle& Rectangle::operator += (const Rectangle& other)
    {
        *this = (*this + other);
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Rectangle Rectangle::operator - (const Rectangle& other) const
    {
        if (other.IsEmpty() || IsEmpty())
            return *this;

        Vector2i minimum_position;
        Vector2i maximum_position;
        minimum_position.X = Maximum(other.GetMinimum().X, GetMinimum().X);
        minimum_position.Y = Maximum(other.GetMinimum().Y, GetMinimum().Y);
        maximum_position.X = Minimum(other.GetMaximum().X, GetMaximum().X);
        maximum_position.Y = Minimum(other.GetMaximum().Y, GetMaximum().Y);

        Rectangle result;
        result.SetFromExtent(minimum_position, maximum_position);
        return result;
    }

    //--------------------------------------------------------------------------------------------//

    Rectangle Rectangle::operator + (const Rectangle& other) const
    {
        if (IsEmpty())
            return other;

        if (other.IsEmpty())
            return *this;

        Rectangle result;
        result = *this;
        result.AddPoint(other.GetMinimum());
        result.AddPoint(other.GetMaximum());
        return result;
    }

    //--------------------------------------------------------------------------------------------//
    
    bool Rectangle::operator == (const Rectangle& other) const
    {
        return Position==other.Position && Size==other.Size;
    }

    //--------------------------------------------------------------------------------------------//

    bool Rectangle::operator != (const Rectangle& other) const
    {
        return Position!=other.Position || Size!=other.Size;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    Vector2i Rectangle::GetMinimum() const
    {
        return Position;
    }

    //--------------------------------------------------------------------------------------------//

    Vector2i Rectangle::GetMaximum() const
    {
        return Position+Size;
    }

    //--------------------------------------------------------------------------------------------//

    bool Rectangle::IsEmpty() const
    {
        return (Size.X<=0) || (Size.Y<=0);
    }

    //--------------------------------------------------------------------------------------------//

    bool Rectangle::IsOverlapping(const Rectangle& other) const
    {
        if (IsEmpty() || other.IsEmpty())
            return false;

        if (GetMinimum().X>other.GetMaximum().X) return false;
        if (GetMaximum().X<other.GetMinimum().X) return false;
        if (GetMinimum().Y>other.GetMaximum().Y) return false;
        if (GetMaximum().Y<other.GetMinimum().Y) return false;
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Rectangle::IsPointInside(const Vector2i& point) const
    {
        if (IsEmpty())
            return false;
        return point>=GetMinimum() && point<=GetMaximum();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Rectangle::Set(const Vector2i& position, const Vector2i& size)
    {
        Position = position;
        Size = size;
    }

    //--------------------------------------------------------------------------------------------//

    void Rectangle::SetEmpty()
    {
        Size.Set(0, 0);
    }

    //--------------------------------------------------------------------------------------------//

    void Rectangle::SetFromExtent(const Vector2i& minimum, const Vector2i& maximum)
    {
        Position = minimum;
        Size = maximum-minimum;
    }

    //--------------------------------------------------------------------------------------------//

    void Rectangle::AddPoint(const Vector2i& point, bool it_is_first_point)
    {
        if (it_is_first_point)
        {
            Position = point;
            Size = 0;
            return;
        }

        Vector2i minimum(GetMinimum());
        Vector2i maximum(GetMaximum());
        maximum.X = Maximum(maximum.X, point.X);
        maximum.Y = Maximum(maximum.Y, point.Y);
        minimum.X = Minimum(minimum.X, point.X);
        minimum.Y = Minimum(minimum.Y, point.Y);
        SetFromExtent(minimum, maximum);
    }

}
}
