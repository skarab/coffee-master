#ifndef _COFFEE_PHYSICS_SCENE_H_
#define _COFFEE_PHYSICS_SCENE_H_

#include "coffee_includes.h"
#include "kernel/shell/shell.h"
#include "system/physics/physics_component.h"
#include "system/physics/material/physics_material.h"

namespace coffee
{
namespace physics
{
    //--------------------------------------------------------------------------------------------//
    /// Scene physics simulation
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Scene : public Component
    {
        COFFEE_Component(Scene, "Physics", "Physics/");

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Scene();
        ~Scene();

        //-ACCESSORS------------------------------------------------------------------------------//

        const basic::Vector3& GetGravity() const { return _Gravity; }
        NewtonWorld* GetWorld() { return _World; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Simulate(const basic::Time& time_step);
        
        //-HANDLERS-------------------------------------------------------------------------------//

        void OnStart();
        void OnStop();
        void OnUpdate(const basic::Time& time_step);

        //-OPERATIONS-----------------------------------------------------------------------------//

        int32 _RegisterMaterial(Material& material);
        
        //-FUNCTIONS------------------------------------------------------------------------------//

        static int32 _OnCollide(const NewtonMaterial* material, const NewtonBody* body0,
            const NewtonBody* body1, int32 threadIndex);
   
    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Initialize();
        void _Finalize();
        void _UpdateMaterials();
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Vector3 _Gravity;
        uint32 _Stamp;
        NewtonWorld* _World;
        basic::Prow<Material*, true> _Materials;
        basic::Prow< resource::Handler<Material> *, true > _MaterialHandlers;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Scene);
}
}
#endif
