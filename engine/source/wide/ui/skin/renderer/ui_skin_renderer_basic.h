#ifndef _COFFEE_UI_SKIN_RENDERER_BASIC_H_
#define _COFFEE_UI_SKIN_RENDERER_BASIC_H_

#include "coffee_includes.h"
#include "wide/ui/skin/renderer/ui_skin_renderer.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Skin renderer using immediate rendering
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API SkinRendererBasic : public SkinRenderer
    {
        COFFEE_Type(SkinRendererBasic);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SkinRendererBasic();
        ~SkinRendererBasic();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Line(const basic::Vector2i& point_a, const basic::Vector2i& point_b);
        void Rectangle(const basic::Vector2i& point_a, const basic::Vector2i& point_b);
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, SkinRendererBasic);
}
}
#endif
