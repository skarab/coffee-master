#ifndef _COFFEE_UI_PROPERTY_COLOR_H_
#define _COFFEE_UI_PROPERTY_COLOR_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/property/ui_property_manager.h"
#include "wide/ui/widget/widgets.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Color property
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyColor : public Property
    {
        COFFEE_PropertyInterface(PropertyColor, "basic::Color", "", false);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyColor();
        ~PropertyColor();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void CreateContent();
        void Update();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(PropertyColor);
        COFFEE_Event bool OnScrollUp(shell::Event& event);
        COFFEE_Event bool OnScrollDown(shell::Event& event);
        COFFEE_Event bool OnButtonReleased(shell::Event& event);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _SetValue(basic::Color value, bool it_has_to_notify=true);
        basic::Color _GetValue();
            
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        widget::Label* _Text;
        widget::Button* _ButtonArray[4];
        real _MinimumValue;
        real _MaximumValue;
        basic::Color _Value;
        bool _ItIsSliding;
        uint32 _SlideIndex;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyColor);
}
}
#endif
