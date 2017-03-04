#ifndef _COFFEE_UI_WIDGET_H_
#define _COFFEE_UI_WIDGET_H_

#include "coffee_includes.h"
#include "wide/ui/window/ui_window.h"
#include "wide/ui/widget/widget_event.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Base class for all widgets
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Widget : public Window
    {
        COFFEE_Type(Widget);

    public:            

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Widget();
        virtual ~Widget();
        
        //-ACCESSORS------------------------------------------------------------------------------//

        void SetData(void* data);
        void* GetData();
        void SetObjectData(meta::Object* object);
        meta::Object* GetObjectData();

        //-QUERIES--------------------------------------------------------------------------------//

        int32 GetIconSize() const;
        int32 GetButtonSize() const;
        int32 GetRealButtonSize() const;
        int32 GetEditBoxSize() const;
        int32 GetScrollSize() const;
        int32 GetRealScrollSize() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void SendEvent(const EVENT& widget_event, void* parameters=NULL);
        bool SendImmediateEvent(const EVENT& widget_event, void* parameters=NULL);
        virtual void Destroy();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(Widget);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        void* _Data;
        meta::Object* _ObjectData;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Widget);
}
}
}
#endif
