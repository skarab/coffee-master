#include "system/graphics/device/config/graphics_config.h"
#include "system/graphics/device/graphics_device.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::Config);
        COFFEE_Ancestor(shell::ModuleConfig);
        COFFEE_Attribute(uint32, _Quality, meta::MODE_Serializeable);
        COFFEE_Attribute(uint32, _Modes, meta::MODE_Serializeable);
        COFFEE_Attribute(<uint32>, _States, meta::MODE_Serializeable);
        COFFEE_Attribute(uint32, _Format, meta::MODE_Serializeable);
        COFFEE_Attribute(real, _Brightness, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, _Contrast, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, _Gamma, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Config::Config() :
        _Brightness(1.0f),
        _Contrast(1.0f),
        _Gamma(2.2f)
    {
        _States.Resize(CONFIG_STATE_Count);
    }

    //--------------------------------------------------------------------------------------------//

    Config::~Config()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Config::SetQuality(CONFIG_QUALITY quality)
    {
        _Quality = quality;
    }

    //--------------------------------------------------------------------------------------------//

    CONFIG_QUALITY Config::GetQuality() const
    {
        return _Quality;
    }

    //--------------------------------------------------------------------------------------------//

    void Config::EnableMode(CONFIG_MODE mode, bool it_has_to_enable)
    {
        if (it_has_to_enable!=IsModeEnabled(mode))
            _Modes ^= (uint32) mode;
    }

    //--------------------------------------------------------------------------------------------//

    bool Config::IsModeEnabled(CONFIG_MODE mode) const
    {
        return (_Modes & ((uint32) mode)) != 0;
    }

    //--------------------------------------------------------------------------------------------//

    void Config::SetState(CONFIG_STATE state, uint32 value)
    {
        _States[(uint32)state] = value;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 Config::GetState(CONFIG_STATE state) const
    {
        return _States[(uint32)state];
    }

    //--------------------------------------------------------------------------------------------//

    void Config::SetFormat(CONFIG_ASPECT_RATIO format)
    {
        _Format = format;
    }

    //--------------------------------------------------------------------------------------------//

    CONFIG_ASPECT_RATIO Config::GetFormat() const
    {
        return _Format;
    }

    //--------------------------------------------------------------------------------------------//

    void Config::SetDefaults()
    {
        SetState(CONFIG_STATE_Device, NONE);
        
        uint32 width, height, bpp;
        CONFIG_ASPECT_RATIO aspect_ratio;
        Device::Get().GetDesktopResolution(width, height, bpp, aspect_ratio);

        SetState(CONFIG_STATE_Bpp, bpp);
        SetState(CONFIG_STATE_Width, width);
        SetState(CONFIG_STATE_Height, height);
        SetState(CONFIG_STATE_Anisotropic, 0);

        SetQuality(CONFIG_QUALITY_Medium);

        EnableMode(CONFIG_MODE_Fullscreen, false);
        EnableMode(CONFIG_MODE_VerticalSync, false);

        SetFormat(aspect_ratio);

        _Brightness = 1.0f;
        _Contrast = 1.0f;
        _Gamma = 2.2f;
    }

}
}
