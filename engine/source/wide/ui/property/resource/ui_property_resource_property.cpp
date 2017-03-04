#include "wide/ui/property/resource/ui_property_resource_property.h"
#include "wide/ui/window/ui_window_manager.h"
#include "wide/ui/component/file_dialog/ui_file_dialog.h"
#include "wide/ui/property/ui_property_list.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::PropertyResourceProperty);
        COFFEE_Ancestor(ui::Property);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PropertyResourceProperty::PropertyResourceProperty() :
        _PropWindow(NULL),
        _StateButton(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    PropertyResourceProperty::~PropertyResourceProperty()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyResourceProperty::CreateContent()
    {
        while (GetObjectInfo().HasChildren())
            GetObjectInfo().GetChild(GetObjectInfo().GetChildCount()-1).Destroy();

        GetObjectInfo().BuildTree(true);

        if (_IsSwitchable())
        {
            _StateButton = COFFEE_New(widget::Button);
            _StateButton->Create(this, basic::Vector2i(0, 0),
                basic::Vector2i(_StateButton->GetButtonSize(), _StateButton->GetButtonSize()),
                widget::BUTTON_STYLE_PushLike | widget::BUTTON_STYLE_HideFrame);
            
            if (GetObjectInfo().GetResourceProperty()->IsFlagEnabled(resource::PROPERTY_FLAG_Enabled))
            {
                _StateButton->SetState(widget::BUTTON_STATE_On);
                _StateButton->SetImage(SKIN_ICON_On);
                _StateButton->SetHelpText(basic::String("Uninstantiate"));
            }
            else
            {
                _StateButton->SetState(widget::BUTTON_STATE_Off);
                _StateButton->SetImage(SKIN_ICON_Off);
                _StateButton->SetHelpText(basic::String("Instantiate"));
            }
        
            _StateButton->GetLayout().SetCanvas(_StateButton->GetButtonSize(), false);
        }

        if (GetObjectInfo().GetResourceProperty()->IsFlagEnabled(resource::PROPERTY_FLAG_Enabled))
        {
            _PropWindow = COFFEE_New(Window);
            _PropWindow->Create(this, basic::Vector2i(_StateButton->GetButtonSize() + 2, 0),
                basic::Vector2i(30, 20), WINDOW_STYLE_DrawFrame | WINDOW_STYLE_DrawClientSunken);
            _PropWindow->GetLayout().SetStyle(LAYOUT_STYLE_VerticalCanvas
                | LAYOUT_STYLE_VerticalShrink | LAYOUT_STYLE_StickChildren);
            _PropWindow->GetLayout().SetCanvas(100, true);
            
            PropertyList::CreateHierarchy(GetObjectInfo(), *_PropWindow, PROPERTY_FLAG_ResourceProperty);
        }
        else
        {
            widget::Label* text_widget = COFFEE_New(widget::Label);
            text_widget->Create(this, basic::Vector2i(10, 0), basic::Vector2i(20, 16));
            text_widget->SetText(GetObjectInfo().GetName());
            text_widget->GetLayout().SetCanvas(100, true);
        }
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(PropertyResourceProperty, Property)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Pressed, widget::Widget, _StateButton, OnStateButton)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool PropertyResourceProperty::OnStateButton(shell::Event& event)
    {
        if(!_IsSwitchable())
            COFFEE_Error(core::ERROR_CODE_Unexpected, "Trying to switch flag on source resource property");

        resource::Object* resource = _FindResource();

        if (resource->OnInstantiateProperty(*GetObjectInfo().GetResourceProperty(),
            GetObjectInfo().GetResourceProperty()->GetSourceProperty(),
            !GetObjectInfo().GetResourceProperty()->IsFlagEnabled(resource::PROPERTY_FLAG_Enabled)))
        {
            GetObjectInfo().GetResourceProperty()->EnableFlag(resource::PROPERTY_FLAG_Enabled,
                !GetObjectInfo().GetResourceProperty()->IsFlagEnabled(resource::PROPERTY_FLAG_Enabled));
        
            DestroyChildren();
            CreateContent();
        }
        else
        {
            _StateButton->SetState(ui::widget::BUTTON_STATE_Off);
        }

        return true;
    }

    //-QUERIES--------------------------------------------------------------------------------------------------------//

    bool PropertyResourceProperty::_IsSwitchable() const
    {
        const resource::PropertyBase* prop = GetObjectInfo().GetResourceProperty();
        resource::Object* resource = _FindResource();

        if (resource->IsInstantiated())
        {
            if (!prop->IsFlagEnabled(resource::PROPERTY_FLAG_Instantiable))
                COFFEE_Error(core::ERROR_CODE_Unexpected, "Unexpected error");
        }
        else
        {
            if (!prop->IsFlagEnabled(resource::PROPERTY_FLAG_LOD) && resource->GetLODIndex() != 0)
                COFFEE_Error(core::ERROR_CODE_Unexpected, "Unexpected error");

            if (resource->GetLODIndex() == 0)
                return false;
        }

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    resource::Object * PropertyResourceProperty::_FindResource() const
    {
        const resource::PropertyBase* prop = GetObjectInfo().GetResourceProperty();
        const meta::ObjectInfo* parent = (const meta::ObjectInfo *) &GetObjectInfo().GetParent();
        resource::Object* resource(NULL);

        while(parent->HasParent()
            && (parent->GetType().GetInfo() != meta::TYPE_INFO_Class
                || !static_cast<const meta::Class&>(parent->GetType()).IsKindOf<resource::Object>()))
        {
            parent = &parent->GetParent();
        }

        if(static_cast<const meta::Class&>(parent->GetType()).IsKindOf<resource::Object>())
        {
            resource = (resource::Object *) parent->GetData();
        }
        else
        {
            COFFEE_Error(core::ERROR_CODE_Unexpected, "Unexpected error");
        }

        return resource;
    }

}
}
