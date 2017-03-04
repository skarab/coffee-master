#ifndef _COFFEE_UI_PROPERTY_QUATERNION_H_
#define _COFFEE_UI_PROPERTY_QUATERNION_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/property/ui_property_manager.h"
#include "wide/ui/widget/widgets.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Quaternion property widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyQuaternion : public Property
    {
        COFFEE_PropertyInterface(PropertyQuaternion, "basic::Quaternion", "", false);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyQuaternion();
        virtual ~PropertyQuaternion();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void CreateContent();
        virtual void Update();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(PropertyQuaternion);
        COFFEE_Event bool OnScrollUp(shell::Event& event);
        COFFEE_Event bool OnScrollDown(shell::Event& event);
        COFFEE_Event bool OnButtonReleased(shell::Event& event);
        COFFEE_Event bool OnEdit(shell::Event& event);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _SetValue(basic::Euler value, bool it_has_to_notify=true);
        basic::Euler _GetValue();
            
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        widget::Label* _Text;
        widget::Button* _ButtonArray[3];
        widget::EditBox* _ComponentArray[3];
        real _MinimumValue;
        real _MaximumValue;
        basic::Euler _Value;
        bool _ItIsSliding;
        uint32 _SlideIndex;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyQuaternion);
}
}
#endif
