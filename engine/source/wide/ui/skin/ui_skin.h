#ifndef _COFFEE_UI_SKIN_H_
#define _COFFEE_UI_SKIN_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/skin/renderer/ui_skin_renderer_type.h"
#include "wide/ui/skin/ui_skin_icon.h"
#include "wide/ui/skin/ui_skin_widget.h"
#include "wide/ui/skin/ui_skin_theme.h"
#include "wide/ui/skin/renderer/ui_skin_renderer.h"
#include "wide/ui/skin/renderer/ui_skin_renderer_basic.h"
#include "wide/ui/skin/renderer/ui_skin_renderer_rounded.h"
#include "wide/ui/skin/widget/ui_skin_window.h"
#include "wide/ui/skin/widget/ui_skin_dialog.h"
#include "wide/ui/skin/widget/ui_skin_label.h"
#include "wide/ui/skin/widget/ui_skin_button.h"
#include "wide/ui/skin/widget/ui_skin_check_box.h"
#include "wide/ui/skin/widget/ui_skin_menu_item.h"
#include "wide/ui/skin/widget/ui_skin_edit_box.h"
#include "wide/ui/skin/widget/ui_skin_scroll_bar.h"
#include "wide/ui/skin/widget/ui_skin_group.h"
#include "wide/ui/skin/widget/ui_skin_view_control.h"
#include "wide/ui/skin/widget/ui_skin_view_container.h"
#include "wide/ui/skin/widget/ui_skin_tree_control_item.h"
#include "wide/ui/skin/widget/ui_skin_image.h"
#include "wide/ui/skin/widget/ui_skin_progress_bar.h"
#include "wide/ui/skin/widget/ui_skin_tool_tip.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Skin is the aggregation of the theme and specific widgets skins
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Skin : public resource::Object
    {
        COFFEE_Resource(Skin);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Skin();
        ~Skin();

        //-ACCESSORS------------------------------------------------------------------------------//

        const SkinTheme& GetTheme() const;
        SkinTheme& GetTheme();
        const SkinRenderer& GetRenderer() const;
        SkinRenderer& GetRenderer();
        const graphics::Texture& GetIcon(const SKIN_ICON& icon) const;
        graphics::Texture& GetIcon(const SKIN_ICON& icon);
        const SkinWidget* GetWidget(const Window& window) const;
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create();
        void DrawWindow(Window& window, const SkinContext& paint_context);
        SkinContext* CreateContext() const;
        void ApplyTheme();        
        void PreSerialize(storage::MODE mode);
        void PostSerialize(storage::MODE mode);
        
        //-HANDLERS-------------------------------------------------------------------------------//

        void OnPropertyModified(const void* prop);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _LoadIcons();
        void _RegisterWidgets();
        
        template <class widget>
        void _RegisterWidget()
        {
            _WidgetArray.Grab().AddItem(COFFEE_New(widget));
        }
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        resource::Property<SkinTheme> _Theme;
        resource::Property<SKIN_RENDERER_TYPE> _RendererType;
        resource::Property<SkinRenderer*> _Renderer;
        resource::Property< basic::Vector< graphics::Texture > > _IconArray;
        resource::Property< basic::Prow< SkinWidget*, true > > _WidgetArray;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Skin);
}
}
#endif
