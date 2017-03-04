#ifndef _COFFEE_UI_PROPERTY_ARRAY_H_
#define _COFFEE_UI_PROPERTY_ARRAY_H_

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
    class COFFEE_API PropertyArray : public Property
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_PropertyInterface(PropertyArray, "", "", true);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyArray();
        virtual ~PropertyArray();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void CreateContent();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(PropertyArray);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        widget::Group* _Group;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyArray);
}
}
#endif
