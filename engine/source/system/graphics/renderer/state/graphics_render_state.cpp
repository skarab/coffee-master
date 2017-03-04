#include "coffee.h"
#include "system/graphics/renderer/state/graphics_render_state.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::RenderState);
        COFFEE_Attribute(graphics::RENDER_STATE_FACE_CULLING, _FaceCullingMode, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(graphics::RENDER_STATE_POLYGON_MODE, _FrontPolygonMode, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(graphics::RENDER_STATE_POLYGON_MODE, _BackPolygonMode, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(bool, _ItHasDepthTestEnabled, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(graphics::RENDER_STATE_TEST_FUNCTION, _DepthTestFunction, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(bool, _ItHasDepthWritingEnabled, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(graphics::RENDER_STATE_SHADE_MODEL, _ShadeModel, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(bool, _ItHasBlendingEnabled, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(graphics::RENDER_STATE_BLENDING_FACTOR, _BlendingSourceFactor, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(graphics::RENDER_STATE_BLENDING_FACTOR, _BlendingDestinationFactor, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(bool, _ItHasAlphaTestEnabled, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(graphics::RENDER_STATE_TEST_FUNCTION, _AlphaTestFunction, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, _AlphaTestThreshold, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(bool, _ItHasColorWritingEnabled, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    RenderState::RenderState()
    {
        SetDefaultValues();
    }

    //--------------------------------------------------------------------------------------------//

    RenderState::~RenderState()
    {
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    RenderState& RenderState::operator = (const RenderState& render_state)
    {
        if (this!=&render_state)
        {
            _FaceCullingMode = render_state._FaceCullingMode;
            _FrontPolygonMode = render_state._FrontPolygonMode;
            _BackPolygonMode = render_state._BackPolygonMode;
            _ItHasDepthTestEnabled = render_state._ItHasDepthTestEnabled;
            _DepthTestFunction = render_state._DepthTestFunction;
            _ItHasDepthWritingEnabled = render_state._ItHasDepthWritingEnabled;
            _ShadeModel = render_state._ShadeModel;
            _ItHasBlendingEnabled = render_state._ItHasBlendingEnabled;
            _BlendingSourceFactor = render_state._BlendingSourceFactor;
            _BlendingDestinationFactor = render_state._BlendingDestinationFactor;
            _ItHasAlphaTestEnabled = render_state._ItHasAlphaTestEnabled;
            _AlphaTestFunction = render_state._AlphaTestFunction;
            _AlphaTestThreshold = render_state._AlphaTestThreshold;
            _ItHasColorWritingEnabled = render_state._ItHasColorWritingEnabled;
        }
        return *this;
    }
    
    //-OPERATIONS---------------------------------------------------------------------------------//

    void RenderState::SetDefaultValues()
    {
        _FaceCullingMode = RENDER_STATE_FACE_CULLING_Back;
        _FrontPolygonMode = RENDER_STATE_POLYGON_MODE_Fill;
        _BackPolygonMode = RENDER_STATE_POLYGON_MODE_Fill;
        _ItHasDepthTestEnabled = true;
        _DepthTestFunction = RENDER_STATE_TEST_FUNCTION_LessOrEqual;
        _ItHasDepthWritingEnabled = true;
        _ShadeModel = RENDER_STATE_SHADE_MODEL_Smooth;
        _ItHasBlendingEnabled = false;
        _BlendingSourceFactor = RENDER_STATE_BLENDING_FACTOR_One;
        _BlendingDestinationFactor = RENDER_STATE_BLENDING_FACTOR_One;
        _ItHasAlphaTestEnabled = false;
        _AlphaTestFunction = RENDER_STATE_TEST_FUNCTION_GreaterOrEqual;
        _AlphaTestThreshold = 0.5f;
        _ItHasColorWritingEnabled = true;
    }

}
}
