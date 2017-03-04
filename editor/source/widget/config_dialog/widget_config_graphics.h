#ifndef _EDITOR_WIDGET_CONFIG_GRAPHICS_H_
#define _EDITOR_WIDGET_CONFIG_GRAPHICS_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Graphics configuration window
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API ConfigGraphics : public ui::Window
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ConfigGraphics();
        ~ConfigGraphics();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(ui::Window* tab_client);
        
        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(ConfigGraphics);
        COFFEE_Event bool OnApply(shell::Event& event);
        COFFEE_Event bool OnSelect(shell::Event& event);
        
    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _UpdateContent();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        graphics::Config _Config;
        ui::widget::Button* _ApplyButton;    
        ui::widget::ComboBoxProperty* _DeviceProperty;
        ui::widget::ComboBoxProperty* _ResolutionProperty;
        ui::widget::ComboBoxProperty* _DepthProperty;
        ui::widget::ComboBoxProperty* _QualityProperty;
        ui::widget::ComboBoxProperty* _AspectRatioProperty;
        ui::widget::ComboBoxProperty* _AnisoProperty;
        ui::widget::CheckBox* _FullscreenProperty;
        ui::widget::CheckBox* _VsyncProperty;
    };
}
}
#endif
