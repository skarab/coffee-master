#ifndef _COFFEE_GRAPHICS_COMPONENT_LIGHT_H_
#define _COFFEE_GRAPHICS_COMPONENT_LIGHT_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/component/graphics_component.h"
#include "system/graphics/material/graphics_material.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Graphics light interface
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ComponentLight : public Component
    {
        COFFEE_Type(ComponentLight);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ComponentLight();
        virtual ~ComponentLight();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetMaterial(Material material) { _Material = material; }
        const Material& GetMaterial() const { return _Material; }
        Material& GetMaterial() { return _Material; }
        void SetColor(const basic::Color& color);
        const basic::Color& GetColor() const { return _Color; }
        void SetIntensity(real intensity);
        real GetIntensity() const { return _Intensity; }
        void SetSoftness(real softness) { _Softness = softness; }
        real GetSoftness() const { return _Softness; }
        virtual real GetRadius() const { return 0.0f; }
        virtual real GetApex() const { return 0.0f; }
        real GetRadiusMultiplier() const { return _RadiusMultiplier; }

        //-HANDLERS-------------------------------------------------------------------------------//

        void OnUpdate(const basic::Time& time_step);
        void OnPropertyModified(const void* prop);

    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void _UpdateBounding() {};

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        bool _ItIsUpToDate;
    
    private:
        
        Material _Material;
        basic::Color _Color;
        real _Intensity;
        real _Softness;
        real _RadiusMultiplier;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ComponentLight);
}
}
#endif
