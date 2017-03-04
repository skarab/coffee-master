#ifndef _COFFEE_SCENE_WORLD_H_
#define _COFFEE_SCENE_WORLD_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/scene/scene_resource.h"
#include "system/scene/node/scene_node.h"
#include "system/scene/path/scene_path.h"
#include "system/physics/physics_world.h"

namespace coffee
{
namespace scene
{
    //--------------------------------------------------------------------------------------------//
    /// Scene world management
    ///
    /// The world own all the loaded scenes, and handles the updates / fixed updates.
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

        resource::Handler<scene::Resource> Load(storage::Path scene_path);
        bool Unload(resource::Handler<scene::Resource>& scene);
        resource::Handler<scene::Resource> Attach(scene::Resource& scene);
        bool Detach(resource::Handler<scene::Resource>& scene);
        scene::Resource* GetScene(storage::Path scene_path);

        void OnInitialize();
        void OnFinalize();
        void OnUpdate(const basic::Time& time_step);
        void OnFixedUpdate(const basic::Time& time_step);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Prow<scene::Resource*, true> _Scenes;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, World);
}
}
#endif
