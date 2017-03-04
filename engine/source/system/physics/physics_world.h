#ifndef _COFFEE_PHYSICS_WORLD_H_
#define _COFFEE_PHYSICS_WORLD_H_

#include "coffee_includes.h"
#include "system/physics/scene/physics_scene.h"
#include "system/physics/rigid_body/physics_rigid_body.h"

namespace coffee
{
namespace physics
{
    //--------------------------------------------------------------------------------------------//
    /// Physical world
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API World : public shell::Module
    {
        COFFEE_Type(World);
        COFFEE_DeclareModuleSingleton(World);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        World();
        ~World();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void OnInitialize();
        void OnFinalize();
        void OnFixedUpdate(const basic::Time& time_step);

        //-HANDLER--------------------------------------------------------------------------------//

        void OnRegisterScene(Scene* scene);
        void OnUnregisterScene(Scene* scene);
        
    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _PlatformCreate();
        void _PlatformDestroy();
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Prow<Scene*> _Scenes;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, World);
}
}
#endif
