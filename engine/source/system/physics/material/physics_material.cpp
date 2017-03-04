#include "system/physics/material/physics_material.h"
#include "system/physics/physics_world.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginResource(physics, Material, "Physics Material", "physics_material", 0);
        COFFEE_Ancestor(resource::Object);
        COFFEE_ResourceProperty(real, _Elasticity, meta::MODE_Serializeable | meta::MODE_Editable, 0);
        COFFEE_ResourceProperty(real, _Softness, meta::MODE_Serializeable | meta::MODE_Editable, 0);
        COFFEE_ResourceProperty(real, _StaticFriction, meta::MODE_Serializeable | meta::MODE_Editable, 0);
        COFFEE_ResourceProperty(real, _KineticFriction, meta::MODE_Serializeable | meta::MODE_Editable, 0);
        COFFEE_ResourceProperty(bool, _ItIsCollidable, meta::MODE_Serializeable | meta::MODE_Editable, 0);
    COFFEE_EndResource();

namespace physics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Material::Material() :
        _Elasticity(0.4f),
        _Softness(0.1f),
        _StaticFriction(0.9f),
        _KineticFriction(0.5f),
        _ItIsCollidable(true)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Material::~Material()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Material::SetElasticity(real elasticity)
    {
        _Elasticity.Set(elasticity);
    }
    
    //--------------------------------------------------------------------------------------------//

    void Material::SetSoftness(real softness)
    {
        _Softness.Set(softness);
    }
        
    //--------------------------------------------------------------------------------------------//

    void Material::SetStaticFriction(real static_friction)
    {
        _StaticFriction.Set(static_friction);
    }
        
    //--------------------------------------------------------------------------------------------//

    void Material::SetKineticFriction(real kinetic_friction)
    {
        _KineticFriction.Set(kinetic_friction);
    }

}
}
