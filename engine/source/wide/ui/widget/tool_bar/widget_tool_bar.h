#ifndef _COFFEE_UI_WIDGET_TOOL_BAR_H_
#define _COFFEE_UI_WIDGET_TOOL_BAR_H_

#include "coffee_includes.h"
#include "wide/ui/widget/widget.h"
#include "wide/ui/widget/button/widget_button.h"
#include "wide/ui/widget/tool_bar/widget_tool_bar_style.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// ToolBar widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ToolBar : public Widget
    {
        COFFEE_Type(ToolBar);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ToolBar();
        ~ToolBar();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(Window* parent, uint32 height,
            uint32 style = TOOL_BAR_STYLE_Default | TOOL_BAR_STYLE_DrawFrame);

        Button* AddButton(basic::String text, uint32 style = BUTTON_STYLE_Default);
        Button* AddButton(basic::String help_text, storage::Path texture_path, uint32 style = BUTTON_STYLE_Default);
        Button* AddButton(basic::String help_text, const SKIN_ICON& icon, uint32 style = BUTTON_STYLE_Default);
        void AddSeparator();
        Window* AddWindow(uint32 size);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(ToolBar);

    private:

        //-QUERIES--------------------------------------------------------------------------------//

        uint32 _GetBaseSize() const;

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        uint32 _Height;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ToolBar);
}
}
}
#endif
