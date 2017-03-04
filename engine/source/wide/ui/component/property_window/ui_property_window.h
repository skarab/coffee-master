#ifndef _COFFEE_UI_PROPERTY_WINDOW_H_
#define _COFFEE_UI_PROPERTY_WINDOW_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/property/ui_property_list.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Property window
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyWindow : public Window
    {
        COFFEE_Type(PropertyWindow);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyWindow();
        virtual ~PropertyWindow();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(meta::Object& object, Window* parent);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(PropertyWindow);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        meta::Object* _Object;
        PropertyList* _PropertyList;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyWindow);
}
}
#endif
