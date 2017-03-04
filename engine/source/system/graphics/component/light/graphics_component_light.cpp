#include "system/graphics/component/light/graphics_component_light.h"
#include "system/graphics/renderer/graphics_renderer.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::ComponentLight);
        COFFEE_Ancestor(graphics::Component);
        COFFEE_Attribute(graphics::Material, _Material, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Color, _Color, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, _Intensity, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, _Softness, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, _RadiusMultiplier, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ComponentLight::ComponentLight() :
        _Intensity(100.0f),
        _Color(1.0f, 1.0f, 1.0f, 1.0f),
        _Softness(0.0f),
        _ItIsUpToDate(false),
        _RadiusMultiplier(1.0f)
    {
        EnableFlag(COMPONENT_FLAG_Pickable, true);
        EnableFlag(COMPONENT_FLAG_CastShadows, true);
    }

    //--------------------------------------------------------------------------------------------//

    ComponentLight::~ComponentLight()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void ComponentLight::SetColor(const basic::Color& color)
    {
        _Color = color;
        _ItIsUpToDate = false;
    }
        
    //--------------------------------------------------------------------------------------------//

    void ComponentLight::SetIntensity(real intensity)
    {
        _Intensity = intensity;
        _ItIsUpToDate = false;
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void ComponentLight::OnUpdate(const basic::Time& time_step)
    {
        if (!_ItIsUpToDate)
        {
            if (GetNode().HasBounding())
                _UpdateBounding();
            _ItIsUpToDate = true;
        }
    }
    
    //--------------------------------------------------------------------------------------------//

    void ComponentLight::OnPropertyModified(const void* prop)
    {
        if (prop==&_Intensity)
            _ItIsUpToDate = false;
    }
}
}
