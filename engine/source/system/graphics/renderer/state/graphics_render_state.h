#ifndef _COFFEE_GRAPHICS_RENDER_STATE_H_
#define _COFFEE_GRAPHICS_RENDER_STATE_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/renderer/state/graphics_render_state_shade_model.h"
#include "system/graphics/renderer/state/graphics_render_state_test_function.h"
#include "system/graphics/renderer/state/graphics_render_state_blending_factor.h"
#include "system/graphics/renderer/state/graphics_render_state_face_culling.h"
#include "system/graphics/renderer/state/graphics_render_state_polygon_mode.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Graphic Render State
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API RenderState : public meta::Object
    {
        COFFEE_Type(RenderState);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        RenderState();
        ~RenderState();

        //-OPERATORS------------------------------------------------------------------------------//

        RenderState& operator = (const RenderState& render_state);

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetFaceCullingMode(RENDER_STATE_FACE_CULLING face_culling_mode) { _FaceCullingMode = face_culling_mode; }
        RENDER_STATE_FACE_CULLING GetFaceCullingMode() const { return _FaceCullingMode; }
        void SetPolygonModes(RENDER_STATE_POLYGON_MODE front_polygon_mode, RENDER_STATE_POLYGON_MODE back_polygon_mode) { _FrontPolygonMode = front_polygon_mode; _BackPolygonMode = back_polygon_mode; }
        RENDER_STATE_POLYGON_MODE GetFrontPolygonMode() const { return _FrontPolygonMode; }
        RENDER_STATE_POLYGON_MODE GetBackPolygonMode() const { return _BackPolygonMode; }
        void EnableDepthTest(bool it_has_to_enable_depth_test) { _ItHasDepthTestEnabled = it_has_to_enable_depth_test; }
        bool IsDepthTestEnabled() const { return _ItHasDepthTestEnabled; }
        void SetDepthTestFunction(RENDER_STATE_TEST_FUNCTION depth_test_function) { _DepthTestFunction = depth_test_function; }
        RENDER_STATE_TEST_FUNCTION GetDepthTestFunction() const { return _DepthTestFunction; }
        void EnableDepthWriting(bool it_has_to_enable_depth_writing) { _ItHasDepthWritingEnabled = it_has_to_enable_depth_writing; }
        bool IsDepthWritingEnabled() const { return _ItHasDepthWritingEnabled; }
        void SetShadeModel(RENDER_STATE_SHADE_MODEL shade_model) { _ShadeModel = shade_model; }
        RENDER_STATE_SHADE_MODEL GetShadeModel() const { return _ShadeModel; }
        void EnableBlending(bool it_has_to_enable_blending) { _ItHasBlendingEnabled = it_has_to_enable_blending; }
        bool IsBlendingEnabled() const { return _ItHasBlendingEnabled; }
        void SetBlendingFactors(RENDER_STATE_BLENDING_FACTOR source_factor, RENDER_STATE_BLENDING_FACTOR destination_factor) { _BlendingSourceFactor = source_factor; _BlendingDestinationFactor = destination_factor; }
        void SetBlendingSourceFactor(RENDER_STATE_BLENDING_FACTOR source_factor) { _BlendingSourceFactor = source_factor; }
        RENDER_STATE_BLENDING_FACTOR GetBlendingSourceFactor() const { return _BlendingSourceFactor; }
        void SetBlendingDestinationFactor(RENDER_STATE_BLENDING_FACTOR destination_factor) { _BlendingDestinationFactor = destination_factor; }
        RENDER_STATE_BLENDING_FACTOR GetBlendingDestinationFactor() const { return _BlendingDestinationFactor; }
        void EnableAlphaTest(bool it_has_to_enable_alpha_test) { _ItHasAlphaTestEnabled = it_has_to_enable_alpha_test; }
        bool IsAlphaTestEnabled() const { return _ItHasAlphaTestEnabled; }
        void SetAlphaTestFunction(RENDER_STATE_TEST_FUNCTION alpha_test_function) { _AlphaTestFunction = alpha_test_function; }
        RENDER_STATE_TEST_FUNCTION GetAlphaTestFunction() const { return _AlphaTestFunction; }
        void SetAlphaTestThreshold(real alpha_test_threshold) { _AlphaTestThreshold = alpha_test_threshold; }
        real GetAlphaTestThreshold() const { return _AlphaTestThreshold; }
        void EnableColorWriting(bool it_has_to_enable_color_writing) { _ItHasColorWritingEnabled = it_has_to_enable_color_writing; }
        bool IsColorWritingEnabled() const { return _ItHasColorWritingEnabled; }
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        void SetDefaultValues();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        RENDER_STATE_FACE_CULLING _FaceCullingMode;
        RENDER_STATE_POLYGON_MODE _FrontPolygonMode;
        RENDER_STATE_POLYGON_MODE _BackPolygonMode;
        bool _ItHasDepthTestEnabled;
        RENDER_STATE_TEST_FUNCTION _DepthTestFunction;
        bool _ItHasDepthWritingEnabled;
        RENDER_STATE_SHADE_MODEL _ShadeModel;
        bool _ItHasBlendingEnabled;
        RENDER_STATE_BLENDING_FACTOR _BlendingSourceFactor;
        RENDER_STATE_BLENDING_FACTOR _BlendingDestinationFactor;
        bool _ItHasAlphaTestEnabled;
        RENDER_STATE_TEST_FUNCTION _AlphaTestFunction;
        real _AlphaTestThreshold;
        bool _ItHasColorWritingEnabled;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, RenderState);
}
}
#endif
