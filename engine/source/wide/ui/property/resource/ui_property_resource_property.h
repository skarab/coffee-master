#ifndef _COFFEE_UI_PROPERTY_RESOURCE_PROPERTY_H_
#define _COFFEE_UI_PROPERTY_RESOURCE_PROPERTY_H_

#include "coffee_includes.h"
#include "kernel/resource/resources.h"
#include "wide/ui/property/ui_property_manager.h"
#include "wide/ui/widget/widgets.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Resource property edition
    ///
    /// This custom dialog manages resource property edition.
    /// It gives an instantiation state and manage resource property flags.
    ///
    /// @see resource::Object
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyResourceProperty : public Property
    {
        COFFEE_Type(PropertyResourceProperty);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyResourceProperty();
        virtual ~PropertyResourceProperty();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void CreateContent();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(PropertyResourceProperty);
        COFFEE_Event bool OnStateButton(shell::Event& event);
        
    private:

        //-QUERIES--------------------------------------------------------------------------------//

        bool _IsSwitchable() const;
        resource::Object* _FindResource() const;

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Window* _PropWindow;
        widget::Button* _StateButton;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyResourceProperty);
}
}
#endif
