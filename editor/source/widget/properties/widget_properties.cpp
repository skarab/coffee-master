#include "widget/properties/widget_properties.h"
#include "coffee_editor.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_ImplementSingleton(widget::Properties);

namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Properties::Properties() :
        ItIsCheckingAsset(false),
        _AssetWidget(NULL),
        _Object(NULL)
    {
        COFFEE_CreateSingleton(Properties);
    }

    //--------------------------------------------------------------------------------------------//

    Properties::~Properties()
    {
        COFFEE_DestroySingleton(Properties);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Properties::Create(ui::Window& panel)
    {
        ui::widget::Dialog::Create(
            &panel,
            basic::Vector2i(),
            basic::Vector2i(280, 0),
            ui::widget::DIALOG_STYLE_None);
        SetStyle(ui::WINDOW_STYLE_Activable
            | ui::WINDOW_STYLE_DrawFrame
            | ui::WINDOW_STYLE_DrawClientSunken
            | ui::WINDOW_STYLE_ResizeableLeft);
        GetLayout().SetStyle(ui::LAYOUT_STYLE_VerticalExpand
            | ui::LAYOUT_STYLE_VerticalCanvas);
        
        SetTitleBarText("Properties [none]");
    }

    //--------------------------------------------------------------------------------------------//

    void Properties::Edit(storage::Path object_path)
    {
        if (ItIsCheckingAsset)
            return;

        //if (_ObjectPath==object_path)
        //    return;

        Clear();

        _ObjectPath = object_path;

        // Create scrollable area
        ui::widget::ViewControl* view_control = COFFEE_New(ui::widget::ViewControl);
        view_control->Create(this, basic::Vector2i(), basic::Vector2i(),
            ui::widget::VIEW_CONTROL_STYLE_AlwaysShowVScrollBar);
        view_control->GetLayout().SetStyle(ui::LAYOUT_STYLE_Expand);
        view_control->GetContainer().GetLayout().SetStyle(
            ui::LAYOUT_STYLE_VerticalCanvas
            | ui::LAYOUT_STYLE_VerticalShrink
            | ui::LAYOUT_STYLE_HorizontalExpand);

        if (_ObjectPath.IsSuffixed(".import"))
        {
            // Create settings window
            _AssetWidget = COFFEE_New(asset::Widget);
            _AssetWidget->Create(_ObjectPath, &view_control->GetContainer());            
            SetTitleBarText(basic::String("Asset [")+_ObjectPath.GetFileName()-basic::String(".import").GetLength()+"]");
        }
        else
        {
            // Create resource window
            asset::ResourceWidget* widget;
            widget = COFFEE_New(asset::ResourceWidget);
            widget->Create(_ObjectPath, &view_control->GetContainer());            
            SetTitleBarText(basic::String("Resource [")+_ObjectPath.GetFileName()+"]");
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Properties::Edit(basic::String object_name, meta::Object& object)
    {
        if (ItIsCheckingAsset)
            return;

        Clear();

        _Object = &object;

        // Create scrollable area
        ui::widget::ViewControl* view_control = COFFEE_New(ui::widget::ViewControl);
        view_control->Create(this, basic::Vector2i(), basic::Vector2i(),
            ui::widget::VIEW_CONTROL_STYLE_AlwaysShowVScrollBar);
        view_control->GetLayout().SetStyle(ui::LAYOUT_STYLE_Expand);
        
        // Create resource window
        ui::PropertyWindow* properties = COFFEE_New(ui::PropertyWindow);
        properties->Create(*_Object, &view_control->GetContainer());
        properties->GetLayout().SetStyle(
            ui::LAYOUT_STYLE_HorizontalExpand
            | ui::LAYOUT_STYLE_VerticalShrink
            | ui::LAYOUT_STYLE_VerticalCanvas
            | ui::LAYOUT_STYLE_StickChildren);

        SetTitleBarText(basic::String("Properties [")+object_name+"]");
    }

    //--------------------------------------------------------------------------------------------//

    void Properties::Clear()
    {
        if (ItIsCheckingAsset)
            return;

        // Check for resource modification
        for (uint32 child=0 ; child<GetChildCount() ; ++child)
        {
            if (GetChild(child).IsKindOf<ui::widget::ViewControl>())
            {
                ui::widget::ViewControl& view_control = static_cast<ui::widget::ViewControl&>(GetChild(child));
                for (uint32 index=0 ; index<view_control.GetContainer().GetChildCount() ; ++index)
                {
                    if (view_control.GetContainer().GetChild(index).IsKindOf<asset::Widget>())
                    {
                        asset::Widget& asset_widget = static_cast<asset::Widget&>(
                            view_control.GetContainer().GetChild(index));
                        ItIsCheckingAsset = true;
                        asset_widget.CheckForModifications();
                    }
                }
            }
        }

        SetTitleBarText("Properties [none]");
        DestroyChildren();
        ItIsCheckingAsset = false;
        _ObjectPath = "";
        _AssetWidget = NULL;
        _Object = NULL;
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(Properties, ui::widget::Dialog)
    COFFEE_EndEventHandler()

}
}
