#ifndef _COFFEE_UI_PROPERTY_LIST_H_
#define _COFFEE_UI_PROPERTY_LIST_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/widget/widget.h"
#include "kernel/meta/info/meta_object_info.h"
#include "wide/ui/property/ui_property_flag.h"
#include "wide/ui/property/ui_property_undo.h"

namespace coffee
{
namespace ui
{
    class Property;

    //--------------------------------------------------------------------------------------------//
    /// Property list
    ///
    /// It manages the creation of widgets based on meta hierarchy coming from a meta object.
    /// The hierarchy is preprocessed by coffee::meta::ObjectInfo and then parsed looking current
    /// states (resource type and so).
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyList : public widget::Widget
    {
        COFFEE_Type(PropertyList);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyList();
        virtual ~PropertyList();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(meta::Object& object, const basic::Vector2i& position,
            const basic::Vector2i& size, Window* parent, bool it_has_to_handle_undo);

        //-FUNCTIONS------------------------------------------------------------------------------//

        static void CreateHierarchy(meta::ObjectInfo& object_info, Window& parent_window,
            uint32 flags = PROPERTY_FLAG_None);
        static void OnPreModify(Property* property);
            
        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(PropertyList);
        COFFEE_Event bool OnPropertyModified(shell::Event& event);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        meta::Object* _Object;
        meta::ObjectInfo* _ObjectInfo;
        bool _ItHasToHandleUndo;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyList);
}
}
#endif
