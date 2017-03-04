#ifndef _COFFEE_UI_SKIN_RENDERER_ROUNDED_H_
#define _COFFEE_UI_SKIN_RENDERER_ROUNDED_H_

#include "coffee_includes.h"
#include "wide/ui/skin/renderer/ui_skin_renderer.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Skin renderer using immediate renderering, forcing rounded forms
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API SkinRendererRounded : public SkinRenderer
    {
        COFFEE_Type(SkinRendererRounded);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SkinRendererRounded();
        ~SkinRendererRounded();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Line(const basic::Vector2i& point_a, const basic::Vector2i& point_b);
        void Rectangle(const basic::Vector2i& point_a, const basic::Vector2i& point_b);
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, SkinRendererRounded);
}
}
#endif
