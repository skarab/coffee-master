#include "wide/ui/property/ui_property.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::Property);
        COFFEE_Ancestor(ui::Window);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Property::Property() :
        _ObjectInfo(NULL),
        _Data(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Property::~Property()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const basic::String& Property::GetName() const
    {
        return _Name;
    }

    //--------------------------------------------------------------------------------------------//

    const meta::Type& Property::GetType() const
    {
        return *_Type;
    }

    //--------------------------------------------------------------------------------------------//

    const void* Property::GetData() const
    {
        return _Data;
    }

    //--------------------------------------------------------------------------------------------//

    void* Property::GetData()
    {
        return _Data;
    }

    //--------------------------------------------------------------------------------------------//

    const meta::ObjectInfo& Property::GetObjectInfo() const
    {
        return *_ObjectInfo;
    }

    //--------------------------------------------------------------------------------------------//

    meta::ObjectInfo& Property::GetObjectInfo()
    {
        return *_ObjectInfo;
    }

    //-QUERIES--------------------------------------------------------------------------------//

    bool Property::HasObjectInfo() const
    {
        return _ObjectInfo!=NULL;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Property::Create(meta::ObjectInfo& object_info, Window& parent_window)
    {
        _Name = object_info.GetName();
        _Data = object_info.GetData();
        _Type = &object_info.GetType();
        _ObjectInfo = &object_info;

        Window::Create(
            &parent_window,
            coffee::basic::Vector2i(),
            coffee::basic::Vector2i(parent_window.GetClientRect().Size.X, 0),
            WINDOW_STYLE_Focusable);

        GetLayout().SetStyle(
            LAYOUT_STYLE_HorizontalCanvas
            | LAYOUT_STYLE_StickChildren
            | LAYOUT_STYLE_VerticalShrink
            | LAYOUT_STYLE_HorizontalExpand);

        CreateContent();
    }

    //--------------------------------------------------------------------------------------------//

    void Property::SendEvent(const PROPERTY_MESSAGE& message, void* parameters)
    {
        shell::EventCode event_code((uint32) message, Property::GetClassMetaType());
        shell::EventParameters event_parameters(parameters);
        shell::Event event;

        event.Set(event_code, event_parameters,
            shell::EVENT_FLAG_StopWhenHandled|shell::EVENT_FLAG_ForwardToParent);
        GetParent().SendEvent(event);
    }

    //--------------------------------------------------------------------------------------------//

    void Property::CreateContent()
    {
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(Property, Window)
        COFFEE_RegisterEventHandler(PROPERTY_MESSAGE_Modified, Property, OnPropertyModified)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool Property::OnPropertyModified(shell::Event& event)
    {
        SendEvent(PROPERTY_MESSAGE_Modified, this);
        return true;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    int32 Property::GetTextControlSize() const
    {
        return 33;
    }

}
}
