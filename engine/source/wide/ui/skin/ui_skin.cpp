#include "wide/ui/skin/ui_skin.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginResource(ui, Skin, "Skin", "skin", resource::MODE_ImmediateLoad);
        COFFEE_Ancestor(resource::Object);
        COFFEE_ResourceProperty(ui::SkinTheme, _Theme, meta::MODE_Serializeable | meta::MODE_Editable, 0);
        COFFEE_ResourceProperty(ui::SKIN_RENDERER_TYPE, _RendererType, meta::MODE_Serializeable | meta::MODE_Editable, 0);
        COFFEE_ResourceProperty(ui::SkinRenderer*, _Renderer, meta::MODE_Serializeable, 0);
        COFFEE_ResourcePropertyCustom(< graphics::Texture >, _IconArray, COFFEE_New(meta::ParamArrayCombo, meta::MODE_Serializeable | meta::MODE_Editable, basic::String("ui::SKIN_ICON")), 0);
        COFFEE_ResourcePropertyCustom(< ui::SkinWidget * >, _WidgetArray, COFFEE_New(meta::ParamArrayCombo, meta::MODE_Serializeable | meta::MODE_Editable, basic::String("Name")), 0);
    COFFEE_EndResource();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Skin::Skin() :
        _Renderer(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Skin::~Skin()
    {
        if (!IsInstantiated() && _Renderer.Get()!=NULL)
            COFFEE_Delete(_Renderer.Grab());
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const SkinTheme& Skin::GetTheme() const
    {
        return _Theme.Get();
    }

    //--------------------------------------------------------------------------------------------//

    SkinTheme& Skin::GetTheme()
    {
        return _Theme.Grab();
    }

    //--------------------------------------------------------------------------------------------//

    const SkinRenderer& Skin::GetRenderer() const
    {
        return *_Renderer.Get();
    }
 
    //--------------------------------------------------------------------------------------------//

    SkinRenderer& Skin::GetRenderer()
    {
        return *_Renderer.Grab();
    }

    //--------------------------------------------------------------------------------------------//

    const graphics::Texture& Skin::GetIcon(const SKIN_ICON& icon) const
    {
        return _IconArray.Get()[(uint32)icon];
    }

    //--------------------------------------------------------------------------------------------//

    graphics::Texture& Skin::GetIcon(const SKIN_ICON& icon)
    {
        return _IconArray.Grab()[(uint32)icon];
    }

    //--------------------------------------------------------------------------------------------//

    const SkinWidget* Skin::GetWidget(const Window& window) const
    {
        uint32 widget_index;
        meta::Class* type = (meta::Class*) &window.GetMetaType();

        while(type!=NULL)
        {
            for(widget_index=0 ; widget_index<_WidgetArray.Get().GetSize() ; ++widget_index)
            {
                if(type==&_WidgetArray.Get()[widget_index]->GetWidgetType())
                    return _WidgetArray.Get()[widget_index];
            }
            type = type->GetAncestor();
        }

        COFFEE_Error(core::ERROR_CODE_WindowManager, "Widget not handled by skin");
        return NULL;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Skin::Create()
    {
        COFFEE_Assert(_Renderer.Get()==NULL, core::ERROR_CODE_Unexpected, "SkinRenderer not NULL");
        _RendererType = SKIN_RENDERER_TYPE_Basic;
        _Renderer = COFFEE_New(SkinRendererBasic);
        _LoadIcons();
        _RegisterWidgets();
        _Theme.Grab().SetDefaults();
        ApplyTheme();
    }

    //--------------------------------------------------------------------------------------------//

    void Skin::DrawWindow(Window& window, const SkinContext& paint_context)
    {
        if (IsAvailable())
        {
            for (uint32 widget_index=0 ; widget_index<_WidgetArray.Get().GetSize() ; ++widget_index)
            {
                if (window.GetMetaType().IsKindOf(_WidgetArray.Get()[widget_index]->GetWidgetType()))
                    _WidgetArray.Grab()[widget_index]->Render(window, paint_context);
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    SkinContext* Skin::CreateContext() const
    {
        return COFFEE_New(SkinContext);
    }

    //--------------------------------------------------------------------------------------------//

    void Skin::ApplyTheme()
    {
        for (uint32 widget_index=0 ; widget_index<_WidgetArray.Get().GetSize() ; ++widget_index)
            _WidgetArray.Grab()[widget_index]->ApplyTheme(_Theme.Grab());
    }
    
    //--------------------------------------------------------------------------------------------//

    void Skin::PreSerialize(storage::MODE mode)
    {
        if (mode==storage::MODE_Input && !IsInstantiated())
        {
            if (_Renderer.Get()!=NULL)
            {
                COFFEE_Delete(_Renderer.Grab());
                _Renderer = NULL;
            }
            _IconArray.Grab().Erase();
            _WidgetArray.Grab().Erase();
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Skin::PostSerialize(storage::MODE mode)
    {
        resource::Object::PostSerialize(mode);

        if (mode==storage::MODE_Input && _IconArray.Get().GetSize()!=(uint32)SKIN_ICON_Count
            && !IsInstantiated())
        {
            _IconArray.Grab().Resize((uint32)SKIN_ICON_Count);
            _LoadIcons();
        }
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void Skin::OnPropertyModified(const void* prop)
    {
        if (prop==&_Theme.Get())
        {
            ApplyTheme();
        }
        else if (prop==&_RendererType.Get())
        {
            if (_Renderer.Get()!=NULL)
            {
                COFFEE_Delete(_Renderer.Grab());
                _Renderer = NULL;
            }
            switch(_RendererType.Get())
            {
                case SKIN_RENDERER_TYPE_Basic:
                    _Renderer = COFFEE_New(SkinRendererBasic);
                    break;

                case SKIN_RENDERER_TYPE_Rounded:
                    _Renderer = COFFEE_New(SkinRendererRounded);
                    break;

                default:
                    COFFEE_Error(core::ERROR_CODE_Unexpected, "Invalid skin renderer type");
            }
        }
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Skin::_LoadIcons()
    {
        if (_IconArray.Get().GetSize()!=(uint32)SKIN_ICON_Count)
            _IconArray.Grab().Resize((uint32)SKIN_ICON_Count);
        
        GetIcon(SKIN_ICON_CursorDefault) = resource::Manager::Get().Load("/coffee/import/skins/default/cursors/default.texture");
        GetIcon(SKIN_ICON_CursorMove) = resource::Manager::Get().Load("/coffee/import/skins/default/cursors/move.texture");
        GetIcon(SKIN_ICON_CursorResizeUp) = resource::Manager::Get().Load("/coffee/import/skins/default/cursors/resize_up.texture");
        GetIcon(SKIN_ICON_CursorResizeDown) = resource::Manager::Get().Load("/coffee/import/skins/default/cursors/resize_down.texture");
        GetIcon(SKIN_ICON_CursorResizeLeft) = resource::Manager::Get().Load("/coffee/import/skins/default/cursors/resize_left.texture");
        GetIcon(SKIN_ICON_CursorResizeRight) = resource::Manager::Get().Load("/coffee/import/skins/default/cursors/resize_right.texture");
        GetIcon(SKIN_ICON_CursorResizeUpLeft) = resource::Manager::Get().Load("/coffee/import/skins/default/cursors/resize_up_left.texture");
        GetIcon(SKIN_ICON_CursorResizeUpRight) = resource::Manager::Get().Load("/coffee/import/skins/default/cursors/resize_up_right.texture");
        GetIcon(SKIN_ICON_CursorResizeDownLeft) = resource::Manager::Get().Load("/coffee/import/skins/default/cursors/resize_down_left.texture");
        GetIcon(SKIN_ICON_CursorResizeDownRight) = resource::Manager::Get().Load("/coffee/import/skins/default/cursors/resize_down_right.texture");
        GetIcon(SKIN_ICON_CursorEditText) = resource::Manager::Get().Load("/coffee/import/skins/default/cursors/edit_text.texture");
        GetIcon(SKIN_ICON_CursorDrop) = resource::Manager::Get().Load("/coffee/import/skins/default/cursors/drop.texture");
        GetIcon(SKIN_ICON_CursorNoDrop) = resource::Manager::Get().Load("/coffee/import/skins/default/cursors/no_drop.texture");
        GetIcon(SKIN_ICON_Close) = resource::Manager::Get().Load("/coffee/import/skins/default/icons/close.texture");
        GetIcon(SKIN_ICON_New) = resource::Manager::Get().Load("/coffee/import/skins/default/icons/new.texture");
        GetIcon(SKIN_ICON_Open) = resource::Manager::Get().Load("/coffee/import/skins/default/icons/open.texture");
        GetIcon(SKIN_ICON_Save) = resource::Manager::Get().Load("/coffee/import/skins/default/icons/save.texture");
        GetIcon(SKIN_ICON_Return) = resource::Manager::Get().Load("/coffee/import/skins/default/icons/return.texture");
        GetIcon(SKIN_ICON_Left) = resource::Manager::Get().Load("/coffee/import/skins/default/icons/left.texture");
        GetIcon(SKIN_ICON_Right) = resource::Manager::Get().Load("/coffee/import/skins/default/icons/right.texture");
        GetIcon(SKIN_ICON_Down) = resource::Manager::Get().Load("/coffee/import/skins/default/icons/down.texture");
        GetIcon(SKIN_ICON_Up) = resource::Manager::Get().Load("/coffee/import/skins/default/icons/up.texture");
        GetIcon(SKIN_ICON_Combo) = resource::Manager::Get().Load("/coffee/import/skins/default/icons/combo.texture");
        GetIcon(SKIN_ICON_Separator) = resource::Manager::Get().Load("/coffee/import/skins/default/icons/separator.texture");
        GetIcon(SKIN_ICON_GroupOn) = resource::Manager::Get().Load("/coffee/import/skins/default/icons/group_on.texture");
        GetIcon(SKIN_ICON_GroupOff) = resource::Manager::Get().Load("/coffee/import/skins/default/icons/group_off.texture");
        GetIcon(SKIN_ICON_On) = resource::Manager::Get().Load("/coffee/import/skins/default/icons/on.texture");
        GetIcon(SKIN_ICON_Off) = resource::Manager::Get().Load("/coffee/import/skins/default/icons/off.texture");
        GetIcon(SKIN_ICON_Undo) = resource::Manager::Get().Load("/coffee/import/skins/default/icons/undo.texture");
        GetIcon(SKIN_ICON_Redo) = resource::Manager::Get().Load("/coffee/import/skins/default/icons/redo.texture");
        GetIcon(SKIN_ICON_Empty) = resource::Manager::Get().Load("/coffee/import/skins/default/icons/empty.texture");
        GetIcon(SKIN_ICON_DisplayLines) = resource::Manager::Get().Load("/coffee/import/skins/default/icons/display_lines.texture");
        GetIcon(SKIN_ICON_PlugOn) = resource::Manager::Get().Load("/coffee/import/skins/default/icons/plug_on.texture");
        GetIcon(SKIN_ICON_PlugOff) = resource::Manager::Get().Load("/coffee/import/skins/default/icons/plug_off.texture");
        GetIcon(SKIN_ICON_PlugFailed) = resource::Manager::Get().Load("/coffee/import/skins/default/icons/plug_failed.texture");
        GetIcon(SKIN_ICON_Scroll) = resource::Manager::Get().Load("/coffee/import/skins/default/icons/scroll.texture");
    }

    //--------------------------------------------------------------------------------------------//

    void Skin::_RegisterWidgets()
    {
        _RegisterWidget<SkinWindow>();
        _RegisterWidget<SkinDialog>();
        _RegisterWidget<SkinLabel>();
        _RegisterWidget<SkinButton>();
        _RegisterWidget<SkinCheckBox>();
        _RegisterWidget<SkinMenuItem>();
        _RegisterWidget<SkinEditBox>();
        _RegisterWidget<SkinScrollBar>();
        _RegisterWidget<SkinGroup>();
        _RegisterWidget<SkinViewControl>();
        _RegisterWidget<SkinViewContainer>();
        _RegisterWidget<SkinTreeControlItem>();
        _RegisterWidget<SkinImage>();
        _RegisterWidget<SkinProgressBar>();
        _RegisterWidget<SkinToolTip>();
    }

}
}
