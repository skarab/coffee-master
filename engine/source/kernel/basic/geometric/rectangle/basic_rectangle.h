#ifndef _COFFEE_BASIC_GEOMETRIC_RECTANGLE_H_
#define _COFFEE_BASIC_GEOMETRIC_RECTANGLE_H_

#include "coffee_includes.h"
#include "kernel/basic/math/basic_math.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Simple rectangle in 2D
    ///
    /// Rectangle defined by two points, in integer [Position, Position+Size].
    /// For now its only used in the GUI to define regions.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Rectangle : public meta::Object
    {
        COFFEE_Type(Rectangle);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        /// Construct an empty rectangle
        Rectangle();

        /// Construct copying other rectangle
        Rectangle(const Rectangle& other);

        /// Construct from given position and size
        Rectangle(const Vector2i& position, const Vector2i& size);

        //-OPERATORS------------------------------------------------------------------------------//

        /// Assign values from other rectangle
        Rectangle& operator = (const Rectangle& other);

        /// Substract the other rectangle
        Rectangle& operator -= (const Rectangle& other);

        /// Add the other rectangle
        Rectangle& operator += (const Rectangle& other);

        /// Create a rectangle which is the difference of self and other
        Rectangle operator - (const Rectangle& other) const;

        /// Create a rectangle which is the addition of self and other
        Rectangle operator + (const Rectangle& other) const;

        /// Check if the two rectangles are equal
        bool operator == (const Rectangle& other) const;

        /// Check if the two rectangles are different
        bool operator != (const Rectangle& other) const;

        //-QUERIES--------------------------------------------------------------------------------//

        /// Get the minimum position of the rectangle
        Vector2i GetMinimum() const;

        /// Get the maximum position of the rectangle
        Vector2i GetMaximum() const;

        /// Check if the rectangle is empty
        bool IsEmpty() const;

        /// Check if it's overlapping the other rectangle
        bool IsOverlapping(const Rectangle& other) const;

        /// Check if the point is inside the rectangle
        bool IsPointInside(const Vector2i& point) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        /// Set from position and size
        void Set(const Vector2i& position, const Vector2i& size);

        /// Set from extent [minimum, maximum]
        void SetFromExtent(const Vector2i& minimum, const Vector2i& maximum);

        /// Set as empty
        void SetEmpty();

        /// Enlarge by adding a point, require to empty it the first time to set the start position        
        void AddPoint(const Vector2i& point, bool it_is_first_point=false);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Vector2i Position;
        Vector2i Size;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Rectangle);
}
}
#endif
