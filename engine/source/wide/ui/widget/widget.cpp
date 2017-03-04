#include "wide/ui/widget/widget.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::widget::Widget);
        COFFEE_Ancestor(ui::Window);
    COFFEE_EndType();

namespace ui
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Widget::Widget():
        _Data(NULL),
        _ObjectData(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Widget::~Widget()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Widget::SetData(void* data)
    {
        _Data = data;
    }

    //--------------------------------------------------------------------------------------------//

    void* Widget::GetData()
    {
        return _Data;
    }

    //--------------------------------------------------------------------------------------------//

    void Widget::SetObjectData(meta::Object* object)
    {
        _ObjectData = object;
    }

    //--------------------------------------------------------------------------------------------//

    meta::Object* Widget::GetObjectData()
    {
        return _ObjectData;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    int32 Widget::GetIconSize() const
    {
        return 16;
    }

    //--------------------------------------------------------------------------------------------//

    int32 Widget::GetButtonSize() const
    {
        return 17;
    }

    //--------------------------------------------------------------------------------------------//

    int32 Widget::GetRealButtonSize() const
    {
        return 18;
    }

    //--------------------------------------------------------------------------------------------//

    int32 Widget::GetEditBoxSize() const
    {
        return 18;
    }

    //--------------------------------------------------------------------------------------------//

    int32 Widget::GetScrollSize() const
    {
        return 12;
    }

    //--------------------------------------------------------------------------------------------//

    int32 Widget::GetRealScrollSize() const
    {
        return 13;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Widget::SendEvent(const EVENT& widget_event, void* parameters)
    {
        shell::EventCode event_code((uint32)widget_event, widget::Widget::GetClassMetaType());
        shell::EventParameters event_parameters(parameters);
        shell::Event event;
        event.Set(event_code, event_parameters,
            shell::EVENT_FLAG_StopWhenHandled|shell::EVENT_FLAG_ForwardToParent);
        shell::EventHandler::SendEvent(event);
    }

    //--------------------------------------------------------------------------------------------//

    bool Widget::SendImmediateEvent(const EVENT& widget_event, void* parameters)
    {
        shell::EventCode event_code((uint32)widget_event, widget::Widget::GetClassMetaType());
        shell::EventParameters event_parameters(parameters);
        shell::Event event;
        event.Set(event_code, event_parameters,
            shell::EVENT_FLAG_StopWhenHandled|shell::EVENT_FLAG_ForwardToParent);
        return shell::EventHandler::SendImmediateEvent(event);
    }

    //--------------------------------------------------------------------------------------------//

    void Widget::Destroy()
    {
        _Data = NULL;
        _ObjectData = NULL;
        Window::Destroy();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(Widget, Window)
    COFFEE_EndEventHandler()

}
}
}
