#ifndef _COFFEE_UI_PROPERTY_H_
#define _COFFEE_UI_PROPERTY_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "kernel/meta/info/meta_object_info.h"
#include "wide/ui/window/ui_window.h"
#include "wide/ui/property/ui_property_message.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Property widget interface
    ///
    /// Base class of property widget, used to edit an object from a specific meta type,
    /// depending of specific parameters.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Property : public Window
    {
        COFFEE_Type(Property);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Property();
        virtual ~Property();

        //-ACCESSORS------------------------------------------------------------------------------//

        const basic::String& GetName() const;
        const meta::Type& GetType() const;
        const void* GetData() const;
        void* GetData();
        const meta::ObjectInfo& GetObjectInfo() const;
        meta::ObjectInfo& GetObjectInfo();

        //-QUERIES--------------------------------------------------------------------------------//

        bool HasObjectInfo() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(meta::ObjectInfo& object_info, Window& parent_window);
        void SendEvent(const PROPERTY_MESSAGE& message, void* parameters = NULL);
        virtual void CreateContent();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(Property);
        COFFEE_Event bool OnPropertyModified(shell::Event& event);

    protected:

        //-QUERIES--------------------------------------------------------------------------------//

        int32 GetTextControlSize() const;

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::String _Name;
        const meta::Type* _Type;
        void* _Data;
        meta::ObjectInfo* _ObjectInfo;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Property);
}
}
#endif
