#ifndef _COFFEE_BASIC_RASTER_COLOR_H_
#define _COFFEE_BASIC_RASTER_COLOR_H_

#include "coffee_includes.h"
#include "kernel/meta/meta.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Color with RGBA components
    ///
    /// @note: the operators don't affect the alpha component
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Color : public meta::Object
    {
        COFFEE_Type(Color);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Color();
        Color(const Color& other);
        Color(real r, real g, real b, real a = 1.0f);
        ~Color();

        //-OPERATORS------------------------------------------------------------------------------//

        Color& operator = (const Color& other);
        bool operator == (const Color& other) const;
        bool operator != (const Color& other) const;
        const Color& operator += (const Color& other);
        Color operator + (const Color& other) const;
        const Color& operator -= (const Color& other);
        Color operator - (const Color& other) const;
        const Color& operator *= (const Color& other);
        Color operator * (const Color& other) const;
        const Color& operator *= (real value);
        Color operator * (real value) const;
        const Color& operator /= (const Color& other);
        Color operator / (const Color& other) const;
        const Color& operator /= (real value);
        Color operator / (real value) const;

        //-ACCESSORS------------------------------------------------------------------------------//

        void Set(real r, real g, real b, real a = 1.0f);
        const real* GetBuffer() const;
        real* GetBuffer();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Clamp();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        real R;
        real G;
        real B;
        real A;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Color);
}
}
#endif
