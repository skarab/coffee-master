#ifndef _COFFEE_UI_PROPERTY_ARRAY_COMBO_H_
#define _COFFEE_UI_PROPERTY_ARRAY_COMBO_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/property/ui_property_manager.h"
#include "wide/ui/widget/widgets.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Array property
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyArrayCombo : public Property
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_PropertyInterface(PropertyArrayCombo, "", "meta::ParamArrayCombo", true);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyArrayCombo();
        virtual ~PropertyArrayCombo();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void CreateContent();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(PropertyArrayCombo);
        COFFEE_Event bool OnSelectItem(shell::Event& event);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _InitializeContent();
        void _CreateHierarchy(uint32 item_index);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        widget::Group* _Group;
        widget::ComboBox* _ComboBox;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyArrayCombo);
}
}
#endif
