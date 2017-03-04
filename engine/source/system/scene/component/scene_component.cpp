#include "system/scene/component/scene_component.h"
#include "system/scene/scene_world.h"
#include "system/graphics/viewport/graphics_viewport.h"
#include "wide/application/application.h"
#include "coffee.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(scene::Component);
        COFFEE_Attribute(uint32, _Flags, meta::MODE_Serializeable);
    COFFEE_EndType();

namespace scene
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Component::Component() :
        _Node(NULL),
        _Flags(FLAG_Automatic|FLAG_Instantiable)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Component::~Component()
    {
        COFFEE_Assert(!IsRunning(), core::ERROR_CODE_Unexpected, "component shouldn't be running");
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Component::SetIsAutomatic(bool it_is_automatic)
    {
        COFFEE_EnableFlag(_Flags, FLAG_Automatic, it_is_automatic);
        if (it_is_automatic)
        {
            if (!IsRunning() && HasNode() && GetNode().IsRunning())
            {
                if (!IsStoppedInEditor() || !Engine::Get().HasMode(RUN_MODE_Editor))
                   Start();
            }
        }
        else if (IsRunning())
        {
            Stop();
        }
    }
        
    //--------------------------------------------------------------------------------------------//

    void Component::SetIsStoppedInEditor(bool it_is_stopped_in_editor)
    {
        COFFEE_EnableFlag(_Flags, FLAG_StopInEditor, it_is_stopped_in_editor);
        SetIsAutomatic(IsAutomatic());

        if (IsRunning() && IsStoppedInEditor() && Engine::Get().HasMode(RUN_MODE_Editor))
            Stop();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Component::Start()
    {
        if (IsRunning())
            return;

        COFFEE_EnableFlag(_Flags, FLAG_Running, true);
        OnStart();
    }

    //--------------------------------------------------------------------------------------------//

    void Component::Stop()
    {
        if (!IsRunning())
            return;

        OnStop();
        COFFEE_EnableFlag(_Flags, FLAG_Running, false);        
    }
        
    //--------------------------------------------------------------------------------------------//

    void Component::Restart()
    {
        if (IsRunning())
        {
            Stop();
            Start();
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Component::PostSerialize(storage::MODE mode)
    {
        if (mode==storage::MODE_Input)
            COFFEE_EnableFlag(_Flags, FLAG_Running, false);                
    }
        
    //-HANDLERS-----------------------------------------------------------------------------------//

    void Component::OnPropertyModified(const void* prop)
    {
        if (prop==&_Flags)
            SetIsStoppedInEditor(IsStoppedInEditor());
    }
        
}
}
