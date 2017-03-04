#ifndef _COFFEE_GRAPHICS_DEVICE_H_
#define _COFFEE_GRAPHICS_DEVICE_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/device/config/graphics_config.h"
#include "system/graphics/device/graphics_device_support.h"

//#define COFFEE_GRAPHICS_Debug()   graphics::Device::Get().CheckStatus()
#define COFFEE_GRAPHICS_Debug()

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Manages the graphics device / context, depending of the platform
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Device
    {
        COFFEE_DeclareSingleton(Device);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Device();
        ~Device();

        //-ACCESSORS------------------------------------------------------------------------------//

        const Config& GetConfig() const { return _Config; }
        Config& GetConfig() { return _Config; }
        basic::String GetExtensions() const { return _ExtensionsString; }
        uint32 GetFrameBufferWidth() const { return _FrameWidth; }
        uint32 GetFrameBufferHeight() const { return _FrameHeight; }
        uint32 GetWidth() const { return _Width; }
        uint32 GetHeight() const { return _Height; }
        uint32 GetBitsPerPixel() const { return _BitsPerPixel; }
        uint32 GetFrequency() const { return _Frequency; }
        real GetAspectRatio() const { return _AspectRatio; }
        bool IsVisible() const { return _ItIsVisible; }
        uint32 GetMaximumFrameColorLayers() const { return _MaximumFrameColorLayers; }

        //-QUERIES--------------------------------------------------------------------------------//

        bool CheckStatus() const;
        bool IsWindowFocused() const;
        bool IsSupporting(DEVICE_SUPPORT feature) const { return COFFEE_IsFlagEnabled(_SupportedFeatures, feature); }

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Initialize();
        void Finalize();
        void Update(bool it_is_visible);
        void EnableContext(bool it_is_enabled);
        void PositionWindowToCenter(uint32 width, uint32 height);
        void Maximize();

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _InitializeExtensions();
        void _EnableVerticalSync();
        void _CreateWindow();
        void _DestroyWindow();
        void _UpdateWindow(bool it_is_visible);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Config _Config;
        char * _ExtensionsString;
        uint32 _FrameWidth, _FrameHeight;
        uint32 _Width, _Height, _BitsPerPixel, _Frequency;
        real _AspectRatio;
        bool _ItHasActiveContext;
        bool _ItIsVisible;
        uint32 _SupportedFeatures;
        uint32 _MaximumFrameColorLayers;

        //-SPECIFICS------------------------------------------------------------------------------//

        #include "system/graphics/device/graphics_device_windows.h"
    };
}
}
#endif
