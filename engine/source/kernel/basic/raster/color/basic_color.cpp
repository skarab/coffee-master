#include "kernel/basic/raster/color/basic_color.h"
#include "kernel/core/core.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::Color);
        COFFEE_Attribute(real, R, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, G, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, B, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, A, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Color::Color() :
        R(0.0f),
        G(0.0f),
        B(0.0f),
        A(0.0f)
    {
    }
    
    //----------------------------------------------------------------------------------------//

    Color::Color(const Color& other):
        R(other.R),
        G(other.G),
        B(other.B),
        A(other.A)
    {
    }

    //----------------------------------------------------------------------------------------//

    Color::Color(real r, real g, real b, real a) :
        R(r),
        G(g),
        B(b),
        A(a)
    {
    }
        
    //----------------------------------------------------------------------------------------//

    Color::~Color()
    {
    }

    //-OPERATORS------------------------------------------------------------------------------//

    Color& Color::operator = (const Color& other)
    {
        R = other.R;
        G = other.G;
        B = other.B;
        A = other.A;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------//

    bool Color::operator == (const Color& other) const
    {
        return IsEqual(R, other.R) && IsEqual(G, other.G) && IsEqual(B, other.B)
            && IsEqual(A, other.A);
    }
    
    //----------------------------------------------------------------------------------------//

    bool Color::operator != (const Color& other) const
    {
        return IsNotEqual(R, other.R) || IsNotEqual(G, other.G) || IsNotEqual(B, other.B)
            || IsNotEqual(A, other.A);
    }
    
    //----------------------------------------------------------------------------------------//

    const Color& Color::operator += (const Color& other)
    {
        R += other.R;
        G += other.G;
        B += other.B;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------//

    Color Color::operator + (const Color& other) const
    {
        return Color(R+other.R, G+other.G, B+other.B, A);
    }
    
    //----------------------------------------------------------------------------------------//

    const Color& Color::operator -= (const Color& other)
    {
        R -= other.R;
        G -= other.G;
        B -= other.B;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------//

    Color Color::operator - (const Color& other) const
    {
        return Color(R-other.R, G-other.G, B-other.B, A);
    }
    
    //----------------------------------------------------------------------------------------//

    const Color& Color::operator *= (const Color& other)
    {
        R *= other.R;
        G *= other.G;
        B *= other.B;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------//

    Color Color::operator * (const Color& other) const
    {
        return Color(R*other.R, G*other.G, B*other.B, A);
    }
    
    //----------------------------------------------------------------------------------------//

    const Color& Color::operator *= (real value)
    {
        R *= value;
        G *= value;
        B *= value;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------//

    Color Color::operator * (real value) const
    {
        return Color(R*value, G*value, B*value, A);
    }
    
    //----------------------------------------------------------------------------------------//

    const Color& Color::operator /= (const Color& other)
    {
        COFFEE_Assert(IsNotEqual(other.R, 0.0f)
            && IsNotEqual(other.G, 0.0f)
            && IsNotEqual(other.B, 0.0f), core::ERROR_CODE_Unexpected, "Zero division");
        R /= other.R;
        G /= other.G;
        B /= other.B;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------//

    Color Color::operator / (const Color& other) const
    {
        COFFEE_Assert(IsNotEqual(other.R, 0.0f)
            && IsNotEqual(other.G, 0.0f)
            && IsNotEqual(other.B, 0.0f), core::ERROR_CODE_Unexpected, "Zero division");
        return Color(R/other.R, G/other.G, B/other.B, A);
    }
    
    //----------------------------------------------------------------------------------------//

    const Color& Color::operator /= (real value)
    {
        COFFEE_Assert(IsNotEqual(value, 0.0f), core::ERROR_CODE_Unexpected, "Zero division");
        R /= value;
        G /= value;
        B /= value;
        return *this;
    }
    
    //----------------------------------------------------------------------------------------//

    Color Color::operator / (real value) const
    {
        COFFEE_Assert(IsNotEqual(value, 0.0f), core::ERROR_CODE_Unexpected, "Zero division");
        return Color(R/value, G/value, B/value, A);
    }    

    //-ACCESSORS------------------------------------------------------------------------------//

    void Color::Set(real r, real g, real b, real a)
    {
        R = r;
        G = g;
        B = b;
        A = a;
    }
    
    //----------------------------------------------------------------------------------------//

    const real* Color::GetBuffer() const
    {
        return &R;
    }
    
    //----------------------------------------------------------------------------------------//

    real* Color::GetBuffer()
    {
        return &R;
    }

    //-OPERATIONS-----------------------------------------------------------------------------//

    void Color::Clamp()
    {
        coffee::Clamp(R, 0.0f, 1.0f);
        coffee::Clamp(G, 0.0f, 1.0f);
        coffee::Clamp(B, 0.0f, 1.0f);
        coffee::Clamp(A, 0.0f, 1.0f);
    }

}
}
