#ifndef _COFFEE_UI_PROPERTY_ENUM_H_
#define _COFFEE_UI_PROPERTY_ENUM_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "kernel/meta/type/enum/meta_enum.h"
#include "wide/ui/property/ui_property_manager.h"
#include "wide/ui/widget/widgets.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Enum property widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyEnum : public Property
    {
        COFFEE_PropertyInterface(PropertyEnum, "enum", "", false);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyEnum();
        virtual ~PropertyEnum();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void CreateContent();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(PropertyEnum);
        COFFEE_Event bool OnSelectItem(shell::Event& event);
        COFFEE_Event bool OnCheckItem(shell::Event& event);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _UpdateSelection();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        const meta::Enum* _EnumType;
        widget::Label* _Text;
        widget::ComboBox* _ComboBox;
        widget::Group* _Group;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyEnum);
}
}
#endif
