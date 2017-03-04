#ifndef _COFFEE_PHYSICS_MATERIAL_H_
#define _COFFEE_PHYSICS_MATERIAL_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "kernel/resource/resources.h"

namespace coffee
{
namespace physics
{
    //--------------------------------------------------------------------------------------------//
    /// Defines the physical properties
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Material : public resource::Object
    {
        COFFEE_Resource(Material);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Material();
        ~Material();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetElasticity(real elasticity);
        real GetElasticity() const { return _Elasticity.Get(); }
        void SetSoftness(real softness);
        real GetSoftness() const { return _Softness.Get(); }
        void SetStaticFriction(real static_friction);
        real GetStaticFriction() const { return _StaticFriction.Get(); }
        void SetKineticFriction(real kinetic_friction);
        real GetKineticFriction() const { return _KineticFriction.Get(); }
        void SetIsCollidable(bool it_is_collidable);
        bool IsCollidable() const { return _ItIsCollidable.Get(); }

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        resource::Property<real> _Elasticity;
        resource::Property<real> _Softness;
        resource::Property<real> _StaticFriction;
        resource::Property<real> _KineticFriction;
        resource::Property<bool> _ItIsCollidable;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Material);
}
}
#endif
