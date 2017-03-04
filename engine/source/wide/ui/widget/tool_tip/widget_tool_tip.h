#ifndef _COFFEE_UI_WIDGET_TOOL_TIP_H_
#define _COFFEE_UI_WIDGET_TOOL_TIP_H_

#include "coffee_includes.h"
#include "wide/ui/widget/widget.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// ToolTip widget
    ///
    /// It displays an help message on CursorOver.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ToolTip : public Widget
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_Type(ToolTip);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ToolTip();
        virtual ~ToolTip();

        //-ACCESSORS------------------------------------------------------------------------------//

        const basic::String& GetHelpText() const;
        const Window* GetOverWindow() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void Create(const basic::String& help_text, const basic::Vector2i& position,
            Window* over_window);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(ToolTip);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::String _HelpText;
        Window* _OverWindow;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ToolTip);
}
}
}
#endif
