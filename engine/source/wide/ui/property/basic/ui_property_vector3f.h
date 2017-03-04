#ifndef _COFFEE_UI_PROPERTY_VECTOR3F_H_
#define _COFFEE_UI_PROPERTY_VECTOR3F_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/property/ui_property_manager.h"
#include "wide/ui/widget/widgets.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Vector3 property
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyVector3 : public Property
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_PropertyInterface(PropertyVector3, "basic::Vector3", "", false);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyVector3();
        virtual ~PropertyVector3();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void CreateContent();
        virtual void Update();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(PropertyVector3);
        COFFEE_Event bool OnScrollUp(shell::Event& event);
        COFFEE_Event bool OnScrollDown(shell::Event& event);
        COFFEE_Event bool OnButtonReleased(shell::Event& event);
        COFFEE_Event bool OnEdit(shell::Event& event);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _SetValue(basic::Vector3 value, bool it_has_to_notify=true);
        basic::Vector3 _GetValue();
            
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        widget::Label* _Text;
        widget::Button* _ButtonArray[3];
        widget::EditBox* _ComponentArray[3];
        real _MinimumValue;
        real _MaximumValue;
        basic::Vector3 _Value;
        bool _ItIsSliding;
        uint32 _SlideIndex;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyVector3);
}
}
#endif
