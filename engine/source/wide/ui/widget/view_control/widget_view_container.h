#ifndef _COFFEE_UI_WIDGET_VIEW_CONTAINER_H_
#define _COFFEE_UI_WIDGET_VIEW_CONTAINER_H_

#include "coffee_includes.h"
#include "wide/ui/widget/widget.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// ViewContainer widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ViewContainer : public Window
    {
        COFFEE_Type(ViewContainer);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ViewContainer();
        ~ViewContainer();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(Window* parent, const basic::Vector2i& position,
            const basic::Vector2i& size, uint32 style=0);
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ViewContainer);
}
}
}
#endif
