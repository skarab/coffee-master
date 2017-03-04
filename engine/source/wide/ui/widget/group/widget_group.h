#ifndef _COFFEE_UI_WIDGET_GROUP_H_
#define _COFFEE_UI_WIDGET_GROUP_H_

#include "coffee_includes.h"
#include "wide/ui/widget/widget.h"
#include "wide/ui/widget/button/widget_button.h"
#include "wide/ui/widget/group/widget_group_style.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Group widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Group : public Widget
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_Type(Group);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Group();
        virtual ~Group();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetTitleBarText(const basic::String& title_bar_text);
        const basic::String& GetTitleBarText();
        int32 GetTitleBarHeight() const;
        const Button& GetGrooveButton() const;
        Button& GetGrooveButton();

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void Create(Window* parent, const basic::Vector2i& position,
            const basic::Vector2i& size, uint32 style=GROUP_STYLE_VerticalShrink);
        virtual void Update();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(Group);
        COFFEE_Event bool OnGroove(shell::Event& event);

    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void _UpdateClientArea();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        uint32 _Height;
        basic::String _TitleBarText;
        int32 _TitleBarHeight;
        Button* _Button;
        bool _ItIsOpen;
        bool _ItIsSliding;
        basic::Time _SlideTime;
        real _AnimatedHeight;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Group);
}
}
}
#endif
