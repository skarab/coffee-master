#ifndef _COFFEE_UI_PROPERTY_IMAGE_H_
#define _COFFEE_UI_PROPERTY_IMAGE_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/property/ui_property_manager.h"
#include "wide/ui/widget/widgets.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Image property
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyImage : public Property
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_PropertyInterface(PropertyImage, "basic::Image", "", false);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyImage();
        ~PropertyImage();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void CreateContent();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        widget::Image* _Image;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyImage);
}
}
#endif
