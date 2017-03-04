#include "wide/ui/property/ui_property_list.h"
#include "wide/ui/property/ui_properties.h"
#include "wide/ui/widget/group/widget_group.h"
#include "wide/ui/property/ui_property_manager.h"
#include "wide/edition/edition.h"
#include "wide/application/application.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::PropertyList);
        COFFEE_Ancestor(ui::widget::Widget);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PropertyList::PropertyList() :
        _Object(NULL),
        _ObjectInfo(NULL),
        _ItHasToHandleUndo(false)
    {
    }

    //--------------------------------------------------------------------------------------------//

    PropertyList::~PropertyList()
    {
        if(_ObjectInfo != NULL)
            _ObjectInfo->Destroy();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyList::Create(meta::Object& object, const basic::Vector2i& position,
        const basic::Vector2i& size, Window* parent, bool it_has_to_handle_undo)
    {
        _ItHasToHandleUndo = it_has_to_handle_undo;
        Window::Create(parent, position, size, WINDOW_STYLE_Focusable);

        GetLayout().SetStyle(
            LAYOUT_STYLE_VerticalShrink
            | LAYOUT_STYLE_VerticalCanvas
            | LAYOUT_STYLE_StickChildren
            | LAYOUT_STYLE_HorizontalExpand);

        _Object = &object;
        _ObjectInfo = COFFEE_New(meta::ObjectInfo, _Object);
        CreateHierarchy(*_ObjectInfo, *this, PROPERTY_FLAG_Root);
    }

    //-FUNCTIONS----------------------------------------------------------------------------------//

    void PropertyList::CreateHierarchy(meta::ObjectInfo& object_info, Window& parent_window,
        uint32 flags)
    {
        const meta::Type* meta_type(NULL);
        const meta::Param* meta_param(NULL);
        Property* property_window(NULL);

        meta_type = &object_info.GetType();
        flags |= object_info.IsArray() * PROPERTY_FLAG_Array;

        if (object_info.IsAttribute() && object_info.IsResourceProperty())
        {
            meta::ObjectInfo* parent = &object_info.GetParent();
            resource::Object* resource;

            while (parent->HasParent() && (parent->GetType().GetInfo()!=meta::TYPE_INFO_Class
                || !static_cast<meta::Class&>(parent->GetType()).IsKindOf<resource::Object>()))
            {
                parent = &parent->GetParent();
            }

            if (static_cast<meta::Class&>(parent->GetType()).IsKindOf<resource::Object>())
            {
                resource = (resource::Object*) parent->GetData();
                if(resource->IsInstantiated())
                    flags |= PROPERTY_FLAG_ResourceInstance;
            }
            else
            {
                COFFEE_Error(core::ERROR_CODE_Unexpected, "Unexpected error");
            }

            if (flags & PROPERTY_FLAG_ResourceInstance)
            {
                if(!object_info.GetResourceProperty()->IsFlagEnabled(resource::PROPERTY_FLAG_Instantiable))
                    return;
            }
            else if (!object_info.GetResourceProperty()->IsFlagEnabled(resource::PROPERTY_FLAG_LOD))
            {
                if (resource->GetLODIndex() != 0)
                    return;
            }

            if (!(flags & PROPERTY_FLAG_ResourceProperty))
            {
                property_window = COFFEE_New(PropertyResourceProperty);
                property_window->Create(object_info, parent_window);
                return;
            }
        }

        if (object_info.IsAttribute() && object_info.GetAttribute()._Param!=NULL)
            meta_param = object_info.GetAttribute()._Param;

        property_window = PropertyManager::Get().CreatePropertyInterface(
            parent_window, object_info, meta_type, meta_param, flags);

        if (!property_window
            && object_info.IsClass()
            && object_info.GetChildCount() > 0
            && !object_info.IsArray())
        {
            uint32 child_index;

            if (object_info.IsAncestor() || (flags & PROPERTY_FLAG_Root))
            {
                for (child_index=0 ; child_index<object_info.GetChildCount() ; ++child_index)
                {
                    CreateHierarchy(
                        object_info.GetChild(child_index),
                        parent_window,
                        flags & PROPERTY_FLAG_ResourceInstance);
                }
            }
            else
            {
                widget::Group* group;

                group = COFFEE_New(widget::Group);
                group->Create(
                    &parent_window,
                    basic::Vector2i(),
                    basic::Vector2i(parent_window.GetClientRect().Size.X, 20));
                group->SetTitleBarText(object_info.GetName());
                
                for (child_index=0 ; child_index<object_info.GetChildCount() ; ++child_index)
                    CreateHierarchy(object_info.GetChild(child_index), *group);
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    void PropertyList::OnPreModify(Property* property)
    {
        if (!property->GetObjectInfo().IsAttribute())
            return;

        PropertyList* head(NULL);
        Window* window = property;
        while(window->HasParent())
        {
            window = &window->GetParentWindow();
            if (window->IsKindOf<PropertyList>()
                && static_cast<PropertyList*>(window)->_ItHasToHandleUndo)
            {
                head = static_cast<PropertyList*>(window);
                break;
            }
        }
        if (head==NULL)
            return;

        if (property->GetObjectInfo().GetAttribute()._Param!=NULL
            && ((property->GetObjectInfo().GetAttribute()._Param->GetMode() & meta::MODE_Undoable)>0))
        {
            if (Application::Get().GetControlManager().HasEditionPlugin())
            {
                edition::Plugin& plugin = Application::Get().GetControlManager().GetEditionPlugin();
                edition::UndoManager& undo_manager = plugin.GetUndoManager();
                basic::String name(basic::String("Modify ")+*property->GetObjectInfo().GetAttribute()._Name);
                PropertyUndo* property_undo = COFFEE_New(PropertyUndo, head->_Object, property->GetData(),
                    *property->GetObjectInfo().GetAttribute()._Type);
               
                if (undo_manager.HasUndoGroup() && undo_manager.GetLastUndoGroup().GetName()==name)
                {
                    PropertyUndo* undo = (PropertyUndo*)undo_manager.GetLastUndoGroup().GetObjects()[0];
                    if (*undo==*property_undo)
                    {
                        COFFEE_Delete(property_undo);
                        return;
                    }
                }

                undo_manager.Begin();
                undo_manager.Add(property_undo);
                undo_manager.Accept(name);
            }
        }
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(PropertyList, widget::Widget)
        COFFEE_RegisterEventHandler(PROPERTY_MESSAGE_Modified, Property, OnPropertyModified)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool PropertyList::OnPropertyModified(shell::Event& event)
    {
        Property* property = (Property*)event.GetParameters().GetCustomParameter();
        _Object->OnPropertyModified(property->GetData());
        return false;
    }
  
}
}
