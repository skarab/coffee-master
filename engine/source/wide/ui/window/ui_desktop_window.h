#ifndef _COFFEE_UI_DESKTOP_WINDOW_H_
#define _COFFEE_UI_DESKTOP_WINDOW_H_

#include "coffee_includes.h"
#include "wide/ui/window/ui_window.h"
#include "system/graphics/viewport/graphics_viewport.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// DesktopWindow is the main viewport
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API DesktopWindow : public graphics::Viewport
    {
        COFFEE_Type(DesktopWindow);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        DesktopWindow();
        ~DesktopWindow();
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, DesktopWindow);
}
}
#endif
