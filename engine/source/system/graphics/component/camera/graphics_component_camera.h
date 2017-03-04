#ifndef _COFFEE_GRAPHICS_COMPONENT_CAMERA_H_
#define _COFFEE_GRAPHICS_COMPONENT_CAMERA_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/component/graphics_component.h"

namespace coffee
{
namespace graphics
{
    class Viewport;

    //--------------------------------------------------------------------------------------------//
    /// Graphic component camera class
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ComponentCamera : public Component
    {
        friend class Viewport;

        COFFEE_Type(ComponentCamera);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ComponentCamera();
        virtual ~ComponentCamera();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetNearClip(real near_clip) { _NearClip = near_clip; }
        real GetNearClip() const { return _NearClip; }
        void SetFarClip(real far_clip) { _FarClip = far_clip; }
        real GetFarClip() const { return _FarClip; }
        const basic::Matrix& GetLocalToViewportMatrix() const { return _LocalToViewportMatrix; }
        basic::Matrix GetViewportToLocalMatrix() const;
        const basic::Matrix& GetInfiniteProjectionMatrix() const { return _InfiniteProjectionMatrix; }
        const Viewport& GetViewport() const { return *_Viewport; }
        Viewport& GetViewport() { return *_Viewport; }
        const basic::Frustum3& GetFrustum() const { return _Frustum; }
        void SetToneMapper(Material tone_mapper) { _ToneMapper = tone_mapper; }
        const Material& GetToneMapper() const { return _ToneMapper; }
        Material& GetToneMapper() { return _ToneMapper; }
        void SetExposure(real exposure) { _Exposure = exposure; }
        real GetExposure() const { return _Exposure; }
        void SetEyeAdaptation(real eye_adaptation) { _EyeAdaptation = eye_adaptation; }
        real GetEyeAdaptation() const { return _EyeAdaptation; }
        void SetBrightAdaptationTime(real bridght_adaptation_time) { _BrightAdaptationTime = bridght_adaptation_time; }
        real GetBrightAdaptationTime() const { return _BrightAdaptationTime; }
        void SetDarkAdaptationTime(real dark_adaptation_time) { _DarkAdaptationTime = dark_adaptation_time; }
        real GetDarkAdaptationTime() const { return _DarkAdaptationTime; }

        //-QUERIES--------------------------------------------------------------------------------//

        bool HasViewport() const { return _Viewport!=NULL; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void Update(Viewport& viewport) {}

        //-HANDLERS-------------------------------------------------------------------------------//

        void OnStart();
        void OnStop();

    protected:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        real _NearClip;
        real _FarClip;
        basic::Matrix _LocalToViewportMatrix;
        basic::Matrix _InfiniteProjectionMatrix;
        Viewport* _Viewport;
        basic::Frustum3 _Frustum;
        Material _ToneMapper;
        real _Exposure;
        real _EyeAdaptation;
        real _BrightAdaptationTime;
        real _DarkAdaptationTime;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ComponentCamera);
}
}
#endif
