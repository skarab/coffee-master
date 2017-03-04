#include "wide/ui/component/property_window/ui_property_window.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::PropertyWindow);
        COFFEE_Ancestor(ui::Window);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PropertyWindow::PropertyWindow() :
        _Object(NULL),
        _PropertyList(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    PropertyWindow::~PropertyWindow()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyWindow::Create(meta::Object& object, Window* parent)
    {
        Window::Create(
            parent, basic::Vector2i(), basic::Vector2i(200, 200),
            WINDOW_STYLE_None);
        GetLayout().SetStyle(
            LAYOUT_STYLE_Expand
            | LAYOUT_STYLE_VerticalCanvas
            | LAYOUT_STYLE_StickChildren);

        _Object = &object;

        _PropertyList = COFFEE_New(PropertyList);
        _PropertyList->Create(object, basic::Vector2i(),
            basic::Vector2i(GetClientRect().Size.X, 0), this, true);
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(PropertyWindow, ui::Window)
    COFFEE_EndEventHandler()
}
}
