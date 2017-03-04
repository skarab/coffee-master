#ifndef _COFFEE_GRAPHICS_CONFIG_H_
#define _COFFEE_GRAPHICS_CONFIG_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/device/config/graphics_config_mode.h"
#include "system/graphics/device/config/graphics_config_state.h"
#include "system/graphics/device/config/graphics_config_quality.h"
#include "system/graphics/device/config/graphics_config_aspect_ratio.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Graphics module configuration
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Config : public shell::ModuleConfig
    {
        COFFEE_Type(Config);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Config();
        ~Config();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetQuality(CONFIG_QUALITY quality);
        CONFIG_QUALITY GetQuality() const;
        void EnableMode(CONFIG_MODE mode, bool it_has_to_enable);
        bool IsModeEnabled(CONFIG_MODE mode) const;
        void SetState(CONFIG_STATE state, uint32 value);
        uint32 GetState(CONFIG_STATE state) const;
        void SetFormat(CONFIG_ASPECT_RATIO format);
        CONFIG_ASPECT_RATIO GetFormat() const;
        void SetBrightness(real brightness) { _Brightness = brightness; }
        real GetBrightness() const { return _Brightness; }
        void SetContrast(real contrast) { _Contrast = contrast; }
        real GetContrast() const { return _Contrast; }
        void SetGamma(real gamma) { _Gamma = gamma; }
        real GetGamma() const { return _Gamma; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        void SetDefaults();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        CONFIG_QUALITY _Quality;
        uint32 _Modes;
        basic::Array<uint32> _States;
        CONFIG_ASPECT_RATIO _Format;
        real _Brightness;
        real _Contrast;
        real _Gamma;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Config);
}
}
#endif
