#include "wide/ui/property/resource/ui_property_resource.h"
#include "wide/ui/window/ui_window_manager.h"
#include "wide/ui/component/file_dialog/ui_file_dialog.h"
#include "wide/ui/property/ui_property_list.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::PropertyResource);
        COFFEE_Ancestor(ui::Property);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PropertyResource::PropertyResource() :
        _Text(NULL),
        _SetButton(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    PropertyResource::~PropertyResource()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyResource::CreateContent()
    {
        resource::Object* resource = (resource::Object*)GetData();

        if(resource->IsInstantiated())
        {
            widget::Group* groove;
            groove = COFFEE_New(widget::Group);
            groove->Create(this, basic::Vector2i(), basic::Vector2i());
            groove->SetTitleBarText(basic::String(GetObjectInfo().GetName()));
            
            Window* window;
            window = COFFEE_New(Window);
            window->Create(groove, basic::Vector2i(0, 0), basic::Vector2i(20, 18),
                WINDOW_STYLE_DrawFrame | WINDOW_STYLE_DrawClientSunken);
            window->GetLayout().SetStyle(LAYOUT_STYLE_HorizontalCanvas
                | LAYOUT_STYLE_HorizontalExpand | LAYOUT_STYLE_StickChildren);
            window->GetLayout().SetCanvas(22, false);
            
            _Text = COFFEE_New(widget::Label);
            _Text->Create(window, basic::Vector2i(0, 0), basic::Vector2i(84, 22));
            _Text->SetText(basic::String("Resource"));
            _Text->GetLayout().SetCanvas(GetTextControlSize(), true);

            _ResourcePath = COFFEE_New(widget::EditBox);
            _ResourcePath->Create(window, basic::Vector2i(10, 0), 84,
                widget::EDIT_BOX_STYLE_ReadOnly);
            _ResourcePath->SetText(resource->GetFilePath());
            _ResourcePath->GetLayout().SetCanvas(100 - GetTextControlSize(), true);

            _SetButton = COFFEE_New(widget::Button);
            _SetButton->Create(window, coffee::basic::Vector2i(100, 1), basic::Vector2i(40, 20),
                widget::BUTTON_STYLE_Default);
            _SetButton->SetText(basic::String("set"));
            _SetButton->GetLayout().SetCanvas(40, false);
            _SetButton->SetHelpText(basic::String("Set resource"));

/*
            widget::Group* properties;
            properties = COFFEE_New(widget::Group);
            properties->Create(groove, basic::Vector2i(), basic::Vector2i());
            properties->GetLayout().SetCanvas(100, true);
            properties->SetTitleBarText(basic::String("Properties"));
        */
            for (uint32 child_index=0 ; child_index<GetObjectInfo().GetChildCount() ; ++child_index)
            {
                PropertyList::CreateHierarchy(GetObjectInfo().GetChild(child_index),
                    *groove, PROPERTY_FLAG_ResourceInstance);
            }
        }
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(PropertyResource, Property)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Pressed, widget::Widget, _SetButton, OnSet)
        COFFEE_RegisterEventHandler(PROPERTY_MESSAGE_Modified, Property, OnPropertyModified)
        COFFEE_RegisterEventHandler(ui::WINDOW_EVENT_QueryDrag, ui::Window, OnQueryDrag)
        COFFEE_RegisterEventHandler(ui::WINDOW_EVENT_QueryDrop, ui::Window, OnQueryDrop)
        COFFEE_RegisterEventHandler(ui::WINDOW_EVENT_Drop, ui::Window, OnDrop)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool PropertyResource::OnSet(shell::Event& event)
    {
        resource::Object* resource = (resource::Object*)GetData();
        FileDialog* file_dialog;
        basic::Text extensions;

        extensions.AddLine(resource->GetResourceType() + " " + basic::String("resource"));
        extensions.AddLine(resource->GetResourceType());

        file_dialog = COFFEE_New(FileDialog);
        file_dialog->Create(basic::String("Set resource"),
            FILE_DIALOG_FLAG_Open | FILE_DIALOG_FLAG_FileMustExist, extensions);
        if (file_dialog->DoModal())
        {
            *resource = resource::Manager::Get().Load(file_dialog->GetFilePath());
            _ResourcePath->SetText(resource->GetFilePath());
            file_dialog->Destroy();
        }
        SendEvent(PROPERTY_MESSAGE_Modified, this);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyResource::OnPropertyModified(shell::Event& event)
    {
        Property* property = (Property*)event.GetParameters().GetCustomParameter();
        resource::Object* resource = (resource::Object*)GetData();
        resource->OnPropertyModified(property->GetData());
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyResource::OnQueryDrag(shell::Event& event)
    {
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyResource::OnQueryDrop(shell::Event& event)
    {
        if (event.GetParameters().GetParameter()!=NULL)
        {
            if (event.GetParameters().GetParameter()->IsKindOf<PropertyResource>())
            {
                const PropertyResource* propsource = static_cast<const PropertyResource*>(event.GetParameters().GetParameter());
                const resource::Object* source = (const resource::Object*)propsource->GetData();
                resource::Object* resource = (resource::Object*)GetData();
                return source->GetResourceType()==resource->GetResourceType();
            }
            else if (event.GetParameters().GetParameter()->IsKindOf<widget::TreeControlItem>())
            {
                return true;
            }
        }
        return false;
    }
    
    //--------------------------------------------------------------------------------------------//

    bool PropertyResource::OnDrop(shell::Event& event)
    {
        if (event.GetParameters().GetParameter()!=NULL)
        {
            if (event.GetParameters().GetParameter()->IsKindOf<PropertyResource>())
            {
                const PropertyResource* propsource = static_cast<const PropertyResource*>(event.GetParameters().GetParameter());
                const resource::Object* source = (const resource::Object*)propsource->GetData();
                resource::Object* resource = (resource::Object*)GetData();
                *resource = *source;
                _ResourcePath->SetText(resource->GetFilePath());
                SendEvent(PROPERTY_MESSAGE_Modified, this);
                return true;
            }
            else if (event.GetParameters().GetParameter()->IsKindOf<widget::TreeControlItem>())
            {
                const widget::TreeControlItem* item = static_cast<const widget::TreeControlItem*>(event.GetParameters().GetParameter());
                storage::Path path = item->GetPath();
                storage::Path head = path.GetHeadFilePath("*");
                resource::Object* resource = (resource::Object*)GetData();
                if (head!=path || head.GetFileExtension()!=resource->GetResourceType())
                {
                    if (head.IsPrefixed("/assets")) { head.CutLeft(strlen("/assets")); head = basic::String("/import")+head; }
                    if (head.IsPrefixed("/coffee/assets")) { head.CutLeft(strlen("/coffee/assets")); head = basic::String("/coffee/import")+head; }

                    path = head;

                    if (head.GetFileExtension()!=resource->GetResourceType())
                    {
                        if (path.GetFileExtension()==resource->GetResourceType())
                        {
                            path = head.GetPath() + "/" + path.GetFileName();
                        }
                        else
                        {
                            path = head.GetPath() + "/" + path.GetFileNameWithoutExtension()
                                + "." + resource->GetResourceType();
                        }
                    }
                }
                
                if (path.GetFileExtension()!=resource->GetResourceType() || !storage::System::Get().HasPath(path))
                    return false;

                *resource = resource::Manager::Get().Load(path);
                _ResourcePath->SetText(resource->GetFilePath());
                SendEvent(PROPERTY_MESSAGE_Modified, this);
                return true;
            }
        }
        return false;
    }

}
}
