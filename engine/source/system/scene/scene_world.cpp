#include "system/scene/scene_world.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(scene::World);
        COFFEE_Ancestor(shell::Module);
    COFFEE_EndType();

namespace scene
{
    COFFEE_ImplementModuleSingleton(World);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    World::World() :
        shell::Module(shell::MODULE_ATTRIBUTE_Automatic | shell::MODULE_ATTRIBUTE_FixedTimeStep)
    {
        COFFEE_CreateModuleSingleton(World);
    }

    //--------------------------------------------------------------------------------------------//

    World::~World()
    {
        COFFEE_DestroyModuleSingleton(World);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    resource::Handler<scene::Resource> World::Load(storage::Path scene_path)
    {
        scene::Resource* scene = COFFEE_New(scene::Resource);
        *scene = resource::Manager::Get().Load(scene_path);
        _Scenes.AddItem(scene);
        return scene;
    }
        
    //--------------------------------------------------------------------------------------------//

    bool World::Unload(resource::Handler<scene::Resource>& scene)
    {
        uint32 index = _Scenes.FindItem(&scene.Get());
        if (index!=NONE)
        {
            _Scenes.Remove(index);
            scene.Set(NULL);
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    resource::Handler<scene::Resource> World::Attach(scene::Resource& scene)
    {
        _Scenes.AddItem(&scene);
        return &scene;
    }

    //--------------------------------------------------------------------------------------------//

    bool World::Detach(resource::Handler<scene::Resource>& scene)
    {
        uint32 index = _Scenes.FindItem(&scene.Get());
        if (index!=NONE)
        {
            _Scenes[index] = NULL;
            _Scenes.Remove(index);
            scene.Set(NULL);
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    scene::Resource* World::GetScene(storage::Path scene_path)
    {
        for (uint32 i=0 ; i<_Scenes.GetSize() ; ++i)
        {
            if (_Scenes[i]->GetFilePath()==scene_path)
                return _Scenes[i];
        }
        return NULL;
    }

    //--------------------------------------------------------------------------------------------//

    void World::OnInitialize()
    {
        COFFEE_RegisterResourceLibrary("scene");
    }

    //--------------------------------------------------------------------------------------------//

    void World::OnFinalize()
    {
        _Scenes.Erase();
    }

    //--------------------------------------------------------------------------------------------//

    void World::OnUpdate(const basic::Time& time_step)
    {
        for (uint32 index=0 ; index<_Scenes.GetSize() ; ++index)
        {
            if (_Scenes[index]->IsAvailable())
            {
                if (!_Scenes[index]->GetRoot().IsRunning())
                    _Scenes[index]->GetRoot().Start();
                _Scenes[index]->GetRoot().Update(time_step);
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    void World::OnFixedUpdate(const basic::Time& time_step)
    {
        for (uint32 index=0 ; index<_Scenes.GetSize() ; ++index)
        {
            if (_Scenes[index]->IsAvailable() && _Scenes[index]->GetRoot().IsRunning())
            {
                _Scenes[index]->GetRoot().FixedUpdate(time_step);
            }
        }
    }

}
}
