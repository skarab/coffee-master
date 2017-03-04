#include "system/physics/physics_world.h"
#include "wide/application/application.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(physics::World);
        COFFEE_Ancestor(shell::Module);
    COFFEE_EndType();

namespace physics
{
    //-FUNCTIONS----------------------------------------------------------------------------------//

    // this allows to catch leaks from newton, and to use custom allocator in the future
    static void* NewtonAllocMemory (int sizeInBytes) { return COFFEE_Allocate(sizeInBytes); }
    static void NewtonFreeMemory (void *ptr, int sizeInBytes) { COFFEE_Free(ptr); }

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

    void World::OnInitialize()
    {
        COFFEE_RegisterResourceLibrary("physics_material");
        NewtonSetMemorySystem(NewtonAllocMemory, NewtonFreeMemory);
    }

    //--------------------------------------------------------------------------------------------//

    void World::OnFinalize()
    {
    }

    //--------------------------------------------------------------------------------------------//

    void World::OnFixedUpdate(const basic::Time& time_step)
    {
        // TODO: Add checkbox to stop it if its in editor mode
        //if (Application::IsAvailable() && !Engine::Get().HasMode(RUN_MODE_Editor))
        {
            for (uint32 i=0 ; i<_Scenes.GetSize() ; ++i)
                _Scenes[i]->Simulate(time_step);
        }
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void World::OnRegisterScene(Scene* scene)
    {
        _Scenes.AddItem(scene);
    }

    //--------------------------------------------------------------------------------------------//

    void World::OnUnregisterScene(Scene* scene)
    {
        _Scenes.RemoveItem(scene);
    }

}
}
