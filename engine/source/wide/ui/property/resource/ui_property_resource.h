#ifndef _COFFEE_UI_PROPERTY_RESOURCE_H_
#define _COFFEE_UI_PROPERTY_RESOURCE_H_

#include "coffee_includes.h"
#include "kernel/resource/resources.h"
#include "wide/ui/property/ui_property_manager.h"
#include "wide/ui/widget/widgets.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Resource instance edition
    ///
    /// This custom dialog manages resource instance edition.
    /// It gives a resource selector, and the instantiable property list.
    ///
    /// @see resource::Object
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyResource : public Property
    {
        COFFEE_Type(PropertyResource);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyResource();
        virtual ~PropertyResource();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void CreateContent();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(PropertyResource);
        COFFEE_Event bool OnSet(shell::Event& event);
        COFFEE_Event bool OnPropertyModified(shell::Event& event);
        COFFEE_Event bool OnQueryDrag(shell::Event& event);
        COFFEE_Event bool OnQueryDrop(shell::Event& event);
        COFFEE_Event bool OnDrop(shell::Event& event);
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        widget::Label* _Text;
        widget::EditBox* _ResourcePath;
        widget::Button* _SetButton;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyResource);
}
}
#endif
