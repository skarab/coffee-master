#include "widget/config_dialog/widget_config_graphics.h"
#include "coffee_editor.h"

bool operator ==(const DISPLAY_DEVICE &,const DISPLAY_DEVICE &) { return false; }
bool operator ==(const DEVMODE &,const DEVMODE &) { return false; }

namespace coffee_editor
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ConfigGraphics::ConfigGraphics() :
        _DeviceProperty(NULL),
        _DepthProperty(NULL),
        _ResolutionProperty(NULL),
        _QualityProperty(NULL),
        _AspectRatioProperty(NULL),
        _AnisoProperty(NULL),
        _FullscreenProperty(NULL),
        _VsyncProperty(NULL),
        _ApplyButton(NULL)
    {
        _Config = graphics::Device::Get().GetConfig();
    }

    //--------------------------------------------------------------------------------------------//

    ConfigGraphics::~ConfigGraphics()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ConfigGraphics::Create(ui::Window* tab_client)
    {
        ui::Window::Create(
            tab_client,
            basic::Vector2i(),
            basic::Vector2i(), 0);
        GetLayout().SetStyle(tab_client->GetLayout().GetStyle());
        
        _DeviceProperty = COFFEE_New(ui::widget::ComboBoxProperty);
        _DeviceProperty->Create("Device", this, basic::Vector2i(0,0), 0);
        _DeviceProperty->GetLayout().SetStyle(_DeviceProperty->GetLayout().GetStyle()
            | ui::LAYOUT_STYLE_HorizontalExpand);

        _ResolutionProperty = COFFEE_New(ui::widget::ComboBoxProperty);
        _ResolutionProperty->Create("Resolution", this, basic::Vector2i(0,30), 0);
        _ResolutionProperty->GetLayout().SetStyle(_ResolutionProperty->GetLayout().GetStyle()
            | ui::LAYOUT_STYLE_HorizontalExpand);

        _DepthProperty = COFFEE_New(ui::widget::ComboBoxProperty);
        _DepthProperty->Create("Color Depth", this, basic::Vector2i(0,60), 0);
        _DepthProperty->GetLayout().SetStyle(_DepthProperty->GetLayout().GetStyle()
            | ui::LAYOUT_STYLE_HorizontalExpand);

        _QualityProperty = COFFEE_New(ui::widget::ComboBoxProperty);
        _QualityProperty->Create("Quality", this, basic::Vector2i(0,120), 0);
        _QualityProperty->GetLayout().SetStyle(_QualityProperty->GetLayout().GetStyle()
            | ui::LAYOUT_STYLE_HorizontalExpand);
        for (uint32 index=0 ; index<graphics::CONFIG_QUALITY_Count ; ++index)
            _QualityProperty->GetComboBox().AddItem(graphics::CONFIG_QUALITY_GetString((graphics::CONFIG_QUALITY)index));
        
        _AspectRatioProperty = COFFEE_New(ui::widget::ComboBoxProperty);
        _AspectRatioProperty->Create("Monitor AspectRatio", this, basic::Vector2i(0,150), 0);
        _AspectRatioProperty->GetLayout().SetStyle(_AspectRatioProperty->GetLayout().GetStyle()
            | ui::LAYOUT_STYLE_HorizontalExpand);
        for (uint32 index=0 ; index<graphics::CONFIG_ASPECT_RATIO_Count ; ++index)
            _AspectRatioProperty->GetComboBox().AddItem(graphics::CONFIG_ASPECT_RATIO_GetString((graphics::CONFIG_ASPECT_RATIO)index));
        
        _AnisoProperty = COFFEE_New(ui::widget::ComboBoxProperty);
        _AnisoProperty->Create("Anisotropic Filtering", this, basic::Vector2i(0,210), 0);
        _AnisoProperty->GetLayout().SetStyle(_AnisoProperty->GetLayout().GetStyle()
            | ui::LAYOUT_STYLE_HorizontalExpand);
        _AnisoProperty->GetComboBox().AddItem("none");
        _AnisoProperty->GetComboBox().AddItem("8x");
        _AnisoProperty->GetComboBox().AddItem("16x");
        _AnisoProperty->GetComboBox().AddItem("24x");
        _AnisoProperty->GetComboBox().AddItem("32x");

        _FullscreenProperty = COFFEE_New(ui::widget::CheckBox);
        _FullscreenProperty->Create(this, basic::Vector2i(0,240), basic::Vector2i(0,20));
        _FullscreenProperty->SetText("Fullscreen");
        _FullscreenProperty->GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalExpand);
        
        _VsyncProperty = COFFEE_New(ui::widget::CheckBox);
        _VsyncProperty->Create(this, basic::Vector2i(0,270), basic::Vector2i(0,20));
        _VsyncProperty->SetText("Vertical Synchronization");
        _VsyncProperty->GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalExpand);
        
        ui::PropertyList* properties = COFFEE_New(ui::PropertyList);
        properties->Create(_Config, basic::Vector2i(), basic::Vector2i(0, 0), this, false);
        //properties->GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalExpand);
        
        _ApplyButton = COFFEE_New(ui::widget::Button);
        _ApplyButton->Create(this, basic::Vector2i(10,300), basic::Vector2i(80,20));
        _ApplyButton->SetText("Apply");
        
        _UpdateContent();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(ConfigGraphics, ui::Window)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _ApplyButton, OnApply)
        COFFEE_RegisterEventHandler(ui::widget::EVENT_Select, ui::widget::Widget, OnSelect)
        COFFEE_RegisterEventHandler(ui::widget::EVENT_Changed, ui::widget::Widget, OnSelect)
        COFFEE_RegisterEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, OnSelect)        
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool ConfigGraphics::OnApply(shell::Event& event)
    {
        graphics::Device::Get().GetConfig() = _Config;
        ui::DoMessageBox("Information", "In order to apply those settings you may need to restart the application.");
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool ConfigGraphics::OnSelect(shell::Event& event)
    {
        if (event.GetTarget()==&_DeviceProperty->GetComboBox())
        {
            _Config.SetState(graphics::CONFIG_STATE_Device, _DeviceProperty->GetComboBox().GetSelectedIndex()-1);
        }
        else if (event.GetTarget()==&_ResolutionProperty->GetComboBox())
        {
            basic::Array<DEVMODE> mode_array;
            graphics::Device::Get().ListModes(mode_array, _Config.GetState(graphics::CONFIG_STATE_Device));
            for (uint32 mode_index=0 ; mode_index<mode_array.GetSize() ; ++mode_index)
            {
                if (_ResolutionProperty->GetComboBox().GetSelectedString()
                    ==basic::String("%dx%d", mode_array[mode_index].dmPelsWidth, mode_array[mode_index].dmPelsHeight))
                {
                    _Config.SetState(graphics::CONFIG_STATE_Width, mode_array[mode_index].dmPelsWidth);
                    _Config.SetState(graphics::CONFIG_STATE_Height, mode_array[mode_index].dmPelsHeight);

                    real monitor_format = mode_array[mode_index].dmPelsWidth/(real)mode_array[mode_index].dmPelsHeight;
                    uint32 index;
                    for (index=0 ; index<graphics::CONFIG_ASPECT_RATIO_Count ; ++index)
                    {
                        if (IsEqual(monitor_format, graphics::CONFIG_ASPECT_RATIO_GetValue((graphics::CONFIG_ASPECT_RATIO)index)))
                        {
                            _Config.SetFormat((graphics::CONFIG_ASPECT_RATIO)index);
                            break;
                        }
                    }

                    if (index==graphics::CONFIG_ASPECT_RATIO_Count)
                        _Config.SetFormat(graphics::CONFIG_ASPECT_RATIO_4_3);

                    break;
                }
            }
        }
        else if (event.GetTarget()==&_DepthProperty->GetComboBox())
        {
            basic::Array<DEVMODE> mode_array;
            graphics::Device::Get().ListModes(mode_array, _Config.GetState(graphics::CONFIG_STATE_Device));
            for (uint32 mode_index=0 ; mode_index<mode_array.GetSize() ; ++mode_index)
            {
                if (_DepthProperty->GetComboBox().GetSelectedString()
                    ==basic::String("%d bits", mode_array[mode_index].dmBitsPerPel))
                {
                    _Config.SetState(graphics::CONFIG_STATE_Bpp, mode_array[mode_index].dmBitsPerPel);
                    break;
                }
            }
        }
        else if (event.GetTarget()==&_QualityProperty->GetComboBox())
        {
            _Config.SetQuality((graphics::CONFIG_QUALITY)_QualityProperty->GetComboBox().GetSelectedIndex());
        }
        else if (event.GetTarget()==&_AspectRatioProperty->GetComboBox())
        {
            _Config.SetFormat((graphics::CONFIG_ASPECT_RATIO)_AspectRatioProperty->GetComboBox().GetSelectedIndex());
        }
        else if (event.GetTarget()==&_AnisoProperty->GetComboBox())
        {
            _Config.SetState(graphics::CONFIG_STATE_Anisotropic, _AnisoProperty->GetComboBox().GetSelectedIndex()*8);
        }
        else if (event.GetTarget()==_FullscreenProperty)
        {
            _Config.EnableMode(graphics::CONFIG_MODE_Fullscreen, _FullscreenProperty->GetState()==ui::widget::CHECK_BOX_STATE_Checked);
        }
        else if (event.GetTarget()==_VsyncProperty)
        {
            _Config.EnableMode(graphics::CONFIG_MODE_VerticalSync, _VsyncProperty->GetState()==ui::widget::CHECK_BOX_STATE_Checked);
        }
        else
        {
            return false;
        }

        _UpdateContent();
        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ConfigGraphics::_UpdateContent()
    {
        // Device
        basic::Array<DISPLAY_DEVICE> device_array;
        basic::Array<DEVMODE> mode_array;
        graphics::Device::Get().ListDevices(device_array);
        uint32 device_index;
        _DeviceProperty->GetComboBox().RemoveItems();
        _DeviceProperty->GetComboBox().AddItem("None");
        for (device_index=0 ; device_index<device_array.GetSize() ; ++device_index)
            _DeviceProperty->GetComboBox().AddItem(device_array[device_index].DeviceString);
        if (_Config.GetState(graphics::CONFIG_STATE_Device)>=device_index)
        {
            _Config.SetState(graphics::CONFIG_STATE_Device, NONE);
            _DeviceProperty->GetComboBox().SelectItem(0);
        }
        else
        {
            _DeviceProperty->GetComboBox().SelectItem(_Config.GetState(graphics::CONFIG_STATE_Device)+1);
            graphics::Device::Get().ListModes(mode_array, _Config.GetState(graphics::CONFIG_STATE_Device));
        }

        // Resolution
        _ResolutionProperty->GetComboBox().RemoveItems();
        if (mode_array.GetSize()>0)
        {
            basic::List<uint32> resx_array;
            basic::List<uint32> resy_array;
            for (uint32 mode_index=0 ; mode_index<mode_array.GetSize() ; ++mode_index)
            {
                bool exists(false);
                for (uint32 res_index=0 ; res_index<resx_array.GetSize() ; ++res_index)
                {
                    if (mode_array[mode_index].dmPelsWidth==resx_array[res_index]
                        && mode_array[mode_index].dmPelsHeight==resy_array[res_index])
                    {
                        exists = true;
                        break;
                    }

                    if (mode_array[mode_index].dmPelsWidth+mode_array[mode_index].dmPelsHeight/4
                        <resx_array[res_index]+resy_array[res_index]/4)
                    {
                        resx_array.AddItem(mode_array[mode_index].dmPelsWidth, res_index);
                        resy_array.AddItem(mode_array[mode_index].dmPelsHeight, res_index);
                        exists = true;
                        break;
                    }
                }
                if (!exists)
                {
                    resx_array.AddItem(mode_array[mode_index].dmPelsWidth);
                    resy_array.AddItem(mode_array[mode_index].dmPelsHeight);
                }
            }

            for (uint32 res_index=0 ; res_index<resx_array.GetSize() ; ++res_index)
            {
                _ResolutionProperty->GetComboBox().AddItem(basic::String("%dx%d", resx_array[res_index], resy_array[res_index]));
                if (resx_array[res_index]==_Config.GetState(graphics::CONFIG_STATE_Width)
                    && resy_array[res_index]==_Config.GetState(graphics::CONFIG_STATE_Height))
                {
                    _ResolutionProperty->GetComboBox().SelectItem(res_index);
                }
            }
        }
        else
        {
            _ResolutionProperty->GetComboBox().AddItem("1024x768");
            _ResolutionProperty->GetComboBox().SelectItem(0);
        }
        
        // Depth
        _DepthProperty->GetComboBox().RemoveItems();
        if (mode_array.GetSize()>0)
        {
            basic::List<uint32> depth_array;
            for (uint32 mode_index=0 ; mode_index<mode_array.GetSize() ; ++mode_index)
            {
                if (mode_array[mode_index].dmPelsWidth!=_Config.GetState(graphics::CONFIG_STATE_Width)
                    || mode_array[mode_index].dmPelsHeight!=_Config.GetState(graphics::CONFIG_STATE_Height))
                {
                    continue;
                }

                bool exists(false);
                for (uint32 depth_index=0 ; depth_index<depth_array.GetSize() ; ++depth_index)
                {
                    if (mode_array[mode_index].dmBitsPerPel==depth_array[depth_index])
                    {
                        exists = true;
                        break;
                    }

                    if (mode_array[mode_index].dmBitsPerPel<depth_array[depth_index])
                    {
                        depth_array.AddItem(mode_array[mode_index].dmBitsPerPel, depth_index);
                        exists = true;
                        break;
                    }
                }
                if (!exists)
                    depth_array.AddItem(mode_array[mode_index].dmBitsPerPel);
            }

            for (uint32 depth_index=0 ; depth_index<depth_array.GetSize() ; ++depth_index)
            {
                _DepthProperty->GetComboBox().AddItem(basic::String("%d bits", depth_array[depth_index]));
                if (depth_array[depth_index]==_Config.GetState(graphics::CONFIG_STATE_Bpp))
                    _DepthProperty->GetComboBox().SelectItem(depth_index);
            }
        }
        else
        {
            _DepthProperty->GetComboBox().AddItem("32 bits");
            _DepthProperty->GetComboBox().SelectItem(0);
        }

        // Others
        _QualityProperty->GetComboBox().SelectItem((uint32)_Config.GetQuality());
        _AspectRatioProperty->GetComboBox().SelectItem((uint32)_Config.GetFormat());
        _AnisoProperty->GetComboBox().SelectItem(_Config.GetState(graphics::CONFIG_STATE_Anisotropic)/8);
        _FullscreenProperty->SetState(_Config.IsModeEnabled(graphics::CONFIG_MODE_Fullscreen)?
            ui::widget::CHECK_BOX_STATE_Checked : ui::widget::CHECK_BOX_STATE_UnChecked);
        _VsyncProperty->SetState(_Config.IsModeEnabled(graphics::CONFIG_MODE_VerticalSync)?
            ui::widget::CHECK_BOX_STATE_Checked : ui::widget::CHECK_BOX_STATE_UnChecked);

        _DepthProperty->Enable(_Config.IsModeEnabled(graphics::CONFIG_MODE_Fullscreen));
    }

}
}
