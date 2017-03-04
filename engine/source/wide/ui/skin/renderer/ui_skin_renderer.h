#ifndef _COFFEE_UI_SKIN_RENDERER_H_
#define _COFFEE_UI_SKIN_RENDERER_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Skin renderer interface
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API SkinRenderer : public meta::Object
    {
        COFFEE_Type(SkinRenderer);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SkinRenderer();
        virtual ~SkinRenderer();

        //-OPERATIONS-----------------------------------------------------------------------------//
        
        virtual void Line(const basic::Vector2i& point_a, const basic::Vector2i& point_b);
        virtual void Rectangle(const basic::Vector2i& point_a, const basic::Vector2i& point_b);
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, SkinRenderer);
}
}
#endif
