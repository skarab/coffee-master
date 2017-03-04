#include "wide/ui/widget/tool_bar/widget_tool_bar.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::widget::ToolBar);
        COFFEE_Ancestor(ui::widget::Widget);
    COFFEE_EndType();

namespace ui
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ToolBar::ToolBar():
        _Height(0)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ToolBar::~ToolBar()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ToolBar::Create(Window* parent, uint32 height, uint32 style)
    {
        SetExtendedStyle(style);
        Window::Create(
            parent,
            basic::Vector2i(),
            basic::Vector2i(
                HasExtendedStyle(TOOL_BAR_STYLE_Vertical)?height:50,
                HasExtendedStyle(TOOL_BAR_STYLE_Vertical)?50:height),
            WINDOW_STYLE_Activable);

        _Height = height;
        
        if (HasExtendedStyle(TOOL_BAR_STYLE_Vertical))
        {
            GetLayout().SetStyle(
                LAYOUT_STYLE_VerticalCanvas
                | LAYOUT_STYLE_StickChildren
                | LAYOUT_STYLE_VerticalExpand);
        }
        else
        {
            GetLayout().SetStyle(
                LAYOUT_STYLE_HorizontalCanvas
                | LAYOUT_STYLE_StickChildren
                | LAYOUT_STYLE_HorizontalExpand);
        }

        if(HasExtendedStyle(TOOL_BAR_STYLE_DrawFrame))
            SetStyle(GetStyle() | WINDOW_STYLE_DrawFrame);
    }

    //--------------------------------------------------------------------------------------------//

    Button* ToolBar::AddButton(basic::String text, uint32 style)
    {
        Button* button = COFFEE_New(Button);
        button->Create(this, basic::Vector2i(),
            basic::Vector2i(_GetBaseSize()-1, _GetBaseSize()-1), style);
        button->SetText(text);
        
        if(!HasExtendedStyle(TOOL_BAR_STYLE_DrawButtons))
            button->SetExtendedStyle(button->GetExtendedStyle() | BUTTON_STYLE_HideFrame);

        return button;
    }

    //--------------------------------------------------------------------------------------------//

    Button* ToolBar::AddButton(basic::String help_text, storage::Path texture_path, uint32 style)
    {
        Button* button;
        graphics::Texture texture;

        texture = coffee::resource::Manager::Get().Load(texture_path);

        button = COFFEE_New(Button);

        button->Create(
            this,
            basic::Vector2i(),
            basic::Vector2i(_GetBaseSize()-1, _GetBaseSize()-1), style);

        button->SetImage(texture);
        button->SetHelpText(help_text);

        if(!HasExtendedStyle(TOOL_BAR_STYLE_DrawButtons))
            button->SetExtendedStyle(button->GetExtendedStyle() | BUTTON_STYLE_HideFrame);

        return button;
    }

    //--------------------------------------------------------------------------------------------//

    Button* ToolBar::AddButton(basic::String help_text, const SKIN_ICON & icon, uint32 style)
    {
        Button * button;

        button = COFFEE_New(Button);

        button->Create(
            this,
            basic::Vector2i(),
            basic::Vector2i(_GetBaseSize()-1, _GetBaseSize()-1), style);

        button->SetImage(icon);
        button->SetHelpText(help_text);
        
        if(!HasExtendedStyle(TOOL_BAR_STYLE_DrawButtons))
            button->SetExtendedStyle(button->GetExtendedStyle() | BUTTON_STYLE_HideFrame);

        return button;
    }

    //--------------------------------------------------------------------------------------------//

    void ToolBar::AddSeparator()
    {
        Image* separator;

        separator = COFFEE_New(Image);

        if (HasExtendedStyle(TOOL_BAR_STYLE_Vertical))
        {
            separator->Create(
                this,
                basic::Vector2i(),
                basic::Vector2i(_GetBaseSize(), _GetBaseSize() / 2));
        }
        else
        {
            separator->Create(
                this,
                basic::Vector2i(),
                basic::Vector2i(_GetBaseSize() / 2, _GetBaseSize()));
        }

        separator->SetImage(SKIN_ICON_Separator);
    }

    //--------------------------------------------------------------------------------------------//

    Window* ToolBar::AddWindow(uint32 size)
    {
        Window* window;

        window = COFFEE_New(Window);

        if (HasExtendedStyle(TOOL_BAR_STYLE_Vertical))
        {
            window->Create(
                this,
                basic::Vector2i(),
                basic::Vector2i(_GetBaseSize(), size),
                WINDOW_STYLE_Focusable
                | WINDOW_STYLE_DrawFrame
                | WINDOW_STYLE_DrawClientSunken);
        }
        else
        {
            window->Create(
                this,
                basic::Vector2i(),
                basic::Vector2i(size, _GetBaseSize()),
                WINDOW_STYLE_Focusable
                | WINDOW_STYLE_DrawFrame
                | WINDOW_STYLE_DrawClientSunken);
        }
        return window;
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(ToolBar, Widget)
    COFFEE_EndEventHandler()

    //-QUERIES------------------------------------------------------------------------------------//

    uint32 ToolBar::_GetBaseSize() const
    {
        return _Height;

        if (HasExtendedStyle(TOOL_BAR_STYLE_Vertical))
        {
            return GetClientRect().Size.X;
        }

        return GetClientRect().Size.Y;
    }

}
}
}
