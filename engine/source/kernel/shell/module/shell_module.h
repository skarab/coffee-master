#ifndef _COFFEE_SHELL_MODULE_H_
#define _COFFEE_SHELL_MODULE_H_

#include "coffee_includes.h"
#include "kernel/basic/time/basic_clock.h"
#include "kernel/shell/thread/shell_thread.h"
#include "kernel/shell/event/shell_event_handler.h"
#include "kernel/shell/module/shell_module_attribute.h"
#include "kernel/shell/state/shell_state_machine.h"
#include "kernel/shell/module/shell_module_state.h"
#include "kernel/shell/module/shell_module_event.h"
#include "kernel/shell/module/shell_module_config.h"

namespace coffee
{
namespace shell
{
    //--------------------------------------------------------------------------------------------//
    /// Module
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Module : public EventHandler
    {
        COFFEE_Type(Module);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Module(uint32 attributes = MODULE_ATTRIBUTE_Defaults);
        virtual ~Module();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetConfig(ModuleConfig& config);
        const ModuleConfig& GetConfig() const;
        ModuleConfig& GetConfig();
        const basic::Time& GetTimeStep() const { return _TimeStep; }
        const basic::Time& GetTime() const { return _Time; }

        //-QUERIES--------------------------------------------------------------------------------//

        bool HasConfig() const;
        bool HasAttribute(MODULE_ATTRIBUTE attribute) const;
        bool IsRunning() const;
        bool IsSleeping() const;
        bool IsModuleAvailable() const;
        bool IsThreadRunning() const;
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        void Start();
        void Stop();
        void Pause();
        void Resume();
        void Kill();

        // Register a child module
        // note: specific to scripted plugins and singleton modules
        template<class module>
        void Register()
        {
            COFFEE_RegisterChildModule(module);
        }
        
        // Unregister a child module
        // note: specific to scripted plugins and singleton modules
        template<class module>
        void Unregister()
        {
            if (module::IsInstantiated())
            {
                module::Get().Kill();
                while (module::IsInstantiated() && !module::Get().IsDestroyed())
                {
                    Update(basic::Time());
                }
            }
        }

        //-HANDLERS-------------------------------------------------------------------------------//

        virtual void OnInitialize() {}
        virtual void OnFinalize() {}
        virtual void OnStart() {}
        virtual void OnStop() {}
        virtual void OnPause() {}
        virtual void OnResume() {}
        virtual void OnUpdate(const basic::Time& time_step) {}
        virtual void OnFixedUpdate(const basic::Time& time_step) {}
        virtual void OnMainThreadUpdate(const basic::Time& time_step) {}
        virtual void OnSleep() {}
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        void Update(const basic::Time& time_step);
        static void ThreadedUpdate(meta::Object* module);

        void ExecuteMethod(void (*method)(Module&, void*), void* data=NULL);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(Module);
        COFFEE_Event bool OnRegister(Event & event);

        //-STATES---------------------------------------------------------------------------------//

        COFFEE_DeclareStateMachine(Module);
        COFFEE_DeclareState(Module, MODULE_STATE_Stopped);
        COFFEE_DeclareState(Module, MODULE_STATE_Sleeping);
        COFFEE_DeclareState(Module, MODULE_STATE_Running);
        COFFEE_DeclareState(Module, MODULE_STATE_Unregistered);
        COFFEE_DeclareState(Module, MODULE_STATE_Destroyed);
        COFFEE_DeclareStateTransition(Module, MODULE_STATE_Stopped, MODULE_STATE_Running);
        COFFEE_DeclareStateTransition(Module, MODULE_STATE_Stopped, MODULE_STATE_Sleeping);
        COFFEE_DeclareEmptyStateTransition(Module, MODULE_STATE_Stopped, MODULE_STATE_Unregistered);
        COFFEE_DeclareEmptyStateTransition(Module, MODULE_STATE_Unregistered, MODULE_STATE_Stopped);
        COFFEE_DeclareStateTransition(Module, MODULE_STATE_Stopped, MODULE_STATE_Destroyed);
        COFFEE_DeclareStateTransition(Module, MODULE_STATE_Running, MODULE_STATE_Stopped);
        COFFEE_DeclareStateTransition(Module, MODULE_STATE_Running, MODULE_STATE_Sleeping);
        COFFEE_DeclareStateTransition(Module, MODULE_STATE_Sleeping, MODULE_STATE_Running);
        COFFEE_DeclareStateTransition(Module, MODULE_STATE_Sleeping, MODULE_STATE_Stopped);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _InternalUpdate();
        void _InternalFixedUpdate();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        uint32 _Attributes;
        ModuleConfig* _Config;
        Thread _Thread;
        basic::Clock* _Clock;
        basic::Time _TimeStep;
        basic::Time _Time;

        //-VARIABLES------------------------------------------------------------------------------//
        
        static real _FixedTimeStep;
        static real _FixedTime;
        static bool _ItIsFixedUpdate;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Module);
}
}
#endif
