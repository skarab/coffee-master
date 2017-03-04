#ifndef _COFFEE_UI_PROPERTY_BASE_H_
#define _COFFEE_UI_PROPERTY_BASE_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/property/ui_property_manager.h"
#include "wide/ui/widget/widgets.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// PropertyBase
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyBase : public Property
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_PropertyInterface(PropertyBase, "basic::PropertyBase", "", false);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyBase();
        virtual ~PropertyBase();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void CreateContent();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(PropertyBase);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        meta::ObjectInfo* _ObjectInfo;
        meta::Attribute _Attribute;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyBase);
}
}
#endif
