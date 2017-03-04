#include "kernel/shell/module/shell_module.h"
#include "kernel/basic/alpha/basic_alpha.h"
#include "coffee.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(shell::Module);
        COFFEE_Ancestor(shell::EventHandler);
    COFFEE_EndType();

namespace shell
{
    //-VARIABLES----------------------------------------------------------------------------------//
        
    real Module::_FixedTimeStep = 0.033f;
    real Module::_FixedTime = 0.0f;
    bool Module::_ItIsFixedUpdate = false;

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Module::Module(uint32 attributes) :
        _Attributes(attributes),
        _Config(NULL),
        _Clock(NULL)
    {
        COFFEE_InitializeStateMachine(Module, MODULE_STATE_Unregistered);
    }

    //--------------------------------------------------------------------------------------------//

    Module::~Module()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Module::SetConfig(ModuleConfig& config)
    {
        _Config = &config;
    }

    //--------------------------------------------------------------------------------------------//

    const ModuleConfig& Module::GetConfig() const
    {
        return *_Config;
    }

    //--------------------------------------------------------------------------------------------//

    ModuleConfig& Module::GetConfig()
    {
        return *_Config;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Module::HasConfig() const
    {
        return _Config != NULL;
    }

    //--------------------------------------------------------------------------------------------//

    bool Module::HasAttribute(MODULE_ATTRIBUTE attribute) const
    {
        return (_Attributes&(uint32)attribute)>0;
    }

    //--------------------------------------------------------------------------------------------//

    bool Module::IsRunning() const
    {
        return GetStateMachine().HasCurrentState()
            && GetStateMachine().GetCurrentState().GetIdentifier()==MODULE_STATE_Running;
    }

    //--------------------------------------------------------------------------------------------//

    bool Module::IsSleeping() const
    {
        return GetStateMachine().HasCurrentState()
            && GetStateMachine().GetCurrentState().GetIdentifier()==MODULE_STATE_Sleeping;
    }

    //--------------------------------------------------------------------------------------------//

    bool Module::IsModuleAvailable() const
    {
        return IsRunning() || IsSleeping();
    }

    //--------------------------------------------------------------------------------------------//

    bool Module::IsThreadRunning() const
    {
        return _Thread.IsRunning();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Module::Start()
    {
        COFFEE_SendEvent(*this, MODULE_EVENT_Start, Module);
    }

    //--------------------------------------------------------------------------------------------//

    void Module::Stop()
    {
        COFFEE_SendEvent(*this, MODULE_EVENT_Stop, Module);
    }

    //--------------------------------------------------------------------------------------------//

    void Module::Pause()
    {
        COFFEE_SendEvent(*this, MODULE_EVENT_Sleep, Module);
    }

    //--------------------------------------------------------------------------------------------//

    void Module::Resume()
    {
        COFFEE_SendEvent(*this, MODULE_EVENT_Start, Module);
    }

    //--------------------------------------------------------------------------------------------//

    void Module::Kill()
    {
        COFFEE_SendEvent(*this, MODULE_EVENT_Kill, Module);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Module::Update(const basic::Time& time_step)
    {
        _TimeStep = time_step;
        _Time += time_step;
        _InternalFixedUpdate();
        _TimeStep = time_step;
        _InternalUpdate();
    }

    //--------------------------------------------------------------------------------------------//

    void Module::ThreadedUpdate(meta::Object* module)
    {
        Module* threaded_module(static_cast<Module*>(module));

        if (threaded_module->_Clock==NULL)
        {
            threaded_module->OnInitialize();
            threaded_module->_Clock = COFFEE_New(basic::Clock);   
        }

        threaded_module->_Clock->Update();
        threaded_module->Update(threaded_module->_Clock->GetTimeStep());
    }

    //--------------------------------------------------------------------------------------------//

    void Module::ExecuteMethod(void (*method)(Module&, void*), void* data)
    {
        (*method)(*this, data);
        for (uint32 child_index=0 ; child_index<GetChildCount() ; ++child_index)
            static_cast<Module*>(&GetChild(child_index))->ExecuteMethod(method, data);
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(Module, EventHandler)
        COFFEE_RegisterEventHandler(MODULE_EVENT_Register, Module, OnRegister)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool Module::OnRegister(Event& event)
    {
        Module* module = (Module*)event.GetParameters().GetParameter();

        COFFEE_Assert(
            module->GetState() == MODULE_STATE_Unregistered,
            core::ERROR_CODE_IncorrectUsage,
            "Failed to register already registered module.");

        module->GetStateMachine().SetCurrentState(MODULE_STATE_Stopped);
        EventHandler::Register(*module);
        
        if (!module->HasAttribute(MODULE_ATTRIBUTE_Threaded))
            module->OnInitialize();

        if (module->HasAttribute(MODULE_ATTRIBUTE_Automatic)
            && !module->GetStateMachine().HasCurrentStateTransition())
        {
            switch (GetState())
            {
                case MODULE_STATE_Running:
                    COFFEE_SendEvent(*module, MODULE_EVENT_Start, Module);
                    break;

                case MODULE_STATE_Stopped:
                    break;

                case MODULE_STATE_Sleeping:
                    COFFEE_SendEvent(*module, MODULE_EVENT_Sleep, Module);
                    break;

                case MODULE_STATE_Destroyed:
                    break;

                default:
                    COFFEE_Error(core::ERROR_CODE_Unexpected, "Failed to register module, while in unstable state.");
            }
        }
        return true;
    }

    //-STATES-------------------------------------------------------------------------------------//

    COFFEE_BeginStateMachineTriggers(Module, EventHandler)
        COFFEE_RegisterStateTrigger(MODULE_EVENT_Start, MODULE_STATE_Running)
        COFFEE_RegisterStateTrigger(MODULE_EVENT_Stop, MODULE_STATE_Stopped)
        COFFEE_RegisterStateTrigger(MODULE_EVENT_Sleep, MODULE_STATE_Sleeping)
        COFFEE_RegisterStateTrigger(MODULE_EVENT_Unregister, MODULE_STATE_Unregistered)
        COFFEE_RegisterStateTrigger(MODULE_EVENT_Kill, MODULE_STATE_Destroyed)
    COFFEE_EndStateMachineTriggers()

    //--------------------------------------------------------------------------------------------//

    COFFEE_BeginStateMachineStates(Module, EventHandler)
        COFFEE_RegisterState(MODULE_STATE_Stopped)
        COFFEE_RegisterState(MODULE_STATE_Sleeping)
        COFFEE_RegisterState(MODULE_STATE_Running)
        COFFEE_RegisterState(MODULE_STATE_Unregistered)
        COFFEE_RegisterState(MODULE_STATE_Destroyed)
    COFFEE_EndStateMachineStates()

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnEnterState(Module, MODULE_STATE_Stopped)
    {
        if (!GetStateMachine().HasStateHistory()
            || GetStateMachine().GetStateHistory(0)->GetIdentifier() != MODULE_STATE_Unregistered)
        {
            if (HasAttribute(MODULE_ATTRIBUTE_Threaded))
            {
                OnFinalize();
                _Thread.Stop();
                COFFEE_Delete(_Clock);
                _Clock = NULL;
            }

            OnStop();
        }
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnLeaveState(Module, MODULE_STATE_Stopped)
    {
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnUpdateState(Module, MODULE_STATE_Stopped)
    {
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnEnterState(Module, MODULE_STATE_Sleeping)
    {
        OnPause();
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnLeaveState(Module, MODULE_STATE_Sleeping)
    {
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnUpdateState(Module, MODULE_STATE_Sleeping)
    {
        OnSleep();
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnEnterState(Module, MODULE_STATE_Running)
    {
        if (GetStateMachine().HasStateHistory()
            && GetStateMachine().GetStateHistory(0)->GetIdentifier()==MODULE_STATE_Sleeping)
        {
            OnResume();
        }
        else
        {
            if (HasAttribute(MODULE_ATTRIBUTE_Threaded) && !_Thread.IsRunning())
            {
                _Thread.Start(*this, &ThreadedUpdate);
                _Thread.SetName(GetMetaType().GetName());
            }

            OnStart();
        }
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnLeaveState(Module, MODULE_STATE_Running)
    {
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnUpdateState(Module, MODULE_STATE_Running)
    {
        if (_ItIsFixedUpdate) OnFixedUpdate(_TimeStep);
        else OnUpdate(_TimeStep);
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnEnterState(Module, MODULE_STATE_Unregistered)
    {
        EventHandler::Unregister();
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnLeaveState(Module, MODULE_STATE_Unregistered)
    {
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnUpdateState(Module, MODULE_STATE_Unregistered)
    {
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnEnterState(Module, MODULE_STATE_Destroyed)
    {
        COFFEE_Assert(!HasChildren(), core::ERROR_CODE_Unexpected, "Destroying module with children");

        if (!HasAttribute(MODULE_ATTRIBUTE_Threaded))
            OnFinalize();
        Destroy();
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnLeaveState(Module, MODULE_STATE_Destroyed)
    {
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnUpdateState(Module, MODULE_STATE_Destroyed)
    {
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_BeginStateMachineStateTransitions(Module, EventHandler)
        COFFEE_RegisterStateTransition(MODULE_STATE_Stopped, MODULE_STATE_Running)
        COFFEE_RegisterStateTransition(MODULE_STATE_Stopped, MODULE_STATE_Sleeping)
        COFFEE_RegisterEmptyStateTransition(MODULE_STATE_Stopped, MODULE_STATE_Unregistered)
        COFFEE_RegisterEmptyStateTransition(MODULE_STATE_Unregistered, MODULE_STATE_Stopped)
        COFFEE_RegisterStateTransition(MODULE_STATE_Stopped, MODULE_STATE_Destroyed)
        COFFEE_RegisterStateTransition(MODULE_STATE_Running, MODULE_STATE_Stopped)
        COFFEE_RegisterStateTransition(MODULE_STATE_Running, MODULE_STATE_Sleeping)
        COFFEE_RegisterStateTransition(MODULE_STATE_Sleeping, MODULE_STATE_Running)
        COFFEE_RegisterStateTransition(MODULE_STATE_Sleeping, MODULE_STATE_Stopped)
    COFFEE_EndStateMachineStateTransitions()

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnEnterStateTransition(Module, MODULE_STATE_Stopped, MODULE_STATE_Running)
    {
        for (uint32 child_index=0 ; child_index<GetChildCount() ; ++child_index)
        {
            Module* child_module = static_cast<Module*>(&GetChild(child_index));
            if (child_module->HasAttribute(MODULE_ATTRIBUTE_Automatic))
                COFFEE_SendEvent(*child_module, MODULE_EVENT_Start, Module);
        }
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnLeaveStateTransition(Module, MODULE_STATE_Stopped, MODULE_STATE_Running)
    {
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnUpdateStateTransition(Module, MODULE_STATE_Stopped, MODULE_STATE_Running)
    {
        for (uint32 child_index=0 ; child_index<GetChildCount() ; ++child_index)
        {
            Module* child_module = static_cast<Module*>(&GetChild(child_index));
            if (child_module->HasAttribute(MODULE_ATTRIBUTE_Automatic)
                && child_module->GetState()!=MODULE_STATE_Running)
            {
                return false;
            }
        }

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnEnterStateTransition(Module, MODULE_STATE_Stopped, MODULE_STATE_Sleeping)
    {
        for (uint32 child_index=0 ; child_index<GetChildCount() ; ++child_index)
        {
            Module* child_module = static_cast<Module*>(&GetChild(child_index));
            if (child_module->HasAttribute(MODULE_ATTRIBUTE_Automatic))
                COFFEE_SendEvent(*child_module, MODULE_EVENT_Sleep, Module);
        }
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnLeaveStateTransition(Module, MODULE_STATE_Stopped, MODULE_STATE_Sleeping)
    {
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnUpdateStateTransition(Module, MODULE_STATE_Stopped, MODULE_STATE_Sleeping)
    {
        for (uint32 child_index=0 ; child_index<GetChildCount() ; ++child_index)
        {
            Module* child_module = static_cast<Module*>(&GetChild(child_index));
            if (child_module->HasAttribute(MODULE_ATTRIBUTE_Automatic)
                && child_module->GetState()!=MODULE_STATE_Sleeping)
            {
                return false;
            }
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnEnterStateTransition(Module, MODULE_STATE_Stopped, MODULE_STATE_Destroyed)
    {
        for (uint32 child_index=0 ; child_index<GetChildCount() ; ++child_index)
        {
            Module* child_module = static_cast<Module*>(&GetChild(child_index));
            if (child_module->HasAttribute(MODULE_ATTRIBUTE_Automatic))
                COFFEE_SendEvent(*child_module, MODULE_EVENT_Kill, Module);
        }
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnLeaveStateTransition(Module, MODULE_STATE_Stopped, MODULE_STATE_Destroyed)
    {
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnUpdateStateTransition(Module, MODULE_STATE_Stopped, MODULE_STATE_Destroyed)
    {
        for (uint32 child_index=0 ; child_index<GetChildCount() ; ++child_index)
        {
            Module* child_module = static_cast<Module*>(&GetChild(child_index));
            if (child_module->HasAttribute(MODULE_ATTRIBUTE_Automatic))
                return false;
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnEnterStateTransition(Module, MODULE_STATE_Running, MODULE_STATE_Stopped)
    {
        for (uint32 child_index=0 ; child_index<GetChildCount() ; ++child_index)
        {
            Module* child_module = static_cast<Module*>(&GetChild(child_index));
            if (child_module->HasAttribute(MODULE_ATTRIBUTE_Automatic))
                COFFEE_SendEvent(*child_module, MODULE_EVENT_Stop, Module);
        }
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnLeaveStateTransition(Module, MODULE_STATE_Running, MODULE_STATE_Stopped)
    {
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnUpdateStateTransition(Module, MODULE_STATE_Running, MODULE_STATE_Stopped)
    {
        for (uint32 child_index=0 ; child_index<GetChildCount() ; ++child_index)
        {
            Module* child_module = static_cast<Module*>(&GetChild(child_index));
            if (child_module->HasAttribute(MODULE_ATTRIBUTE_Automatic)
                && ((child_module->GetState()!=MODULE_STATE_Stopped)
                    || child_module->IsThreadRunning()))
            {
                return false;
            }
        }

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnEnterStateTransition(Module, MODULE_STATE_Running, MODULE_STATE_Sleeping)
    {
        for (uint32 child_index=0 ; child_index<GetChildCount() ; ++child_index)
        {
            Module* child_module = static_cast<Module*>(&GetChild(child_index));
            if (child_module->HasAttribute(MODULE_ATTRIBUTE_Automatic))
                COFFEE_SendEvent(*child_module, MODULE_EVENT_Sleep, Module);
        }
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnLeaveStateTransition(Module, MODULE_STATE_Running, MODULE_STATE_Sleeping)
    {
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnUpdateStateTransition(Module, MODULE_STATE_Running, MODULE_STATE_Sleeping)
    {
        for (uint32 child_index=0 ; child_index<GetChildCount() ; ++child_index)
        {
            Module* child_module = static_cast<Module*>(&GetChild(child_index));
            if (child_module->HasAttribute(MODULE_ATTRIBUTE_Automatic)
                && child_module->GetState()!=MODULE_STATE_Sleeping)
            {
                return false;
            }
        }

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnEnterStateTransition(Module, MODULE_STATE_Sleeping, MODULE_STATE_Running)
    {
        for (uint32 child_index=0 ; child_index<GetChildCount() ; ++child_index)
        {
            Module* child_module = static_cast<Module*>(&GetChild(child_index));
            if (child_module->HasAttribute(MODULE_ATTRIBUTE_Automatic))
                COFFEE_SendEvent(*child_module, MODULE_EVENT_Start, Module);
        }
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnLeaveStateTransition(Module, MODULE_STATE_Sleeping, MODULE_STATE_Running)
    {
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnUpdateStateTransition(Module, MODULE_STATE_Sleeping, MODULE_STATE_Running)
    {
        for (uint32 child_index=0 ; child_index<GetChildCount() ; ++child_index)
        {
            Module* child_module = static_cast<Module*>(&GetChild(child_index));
            if (child_module->HasAttribute(MODULE_ATTRIBUTE_Automatic)
                && child_module->GetState()!=MODULE_STATE_Running)
            {
                return false;
            }
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnEnterStateTransition(Module, MODULE_STATE_Sleeping, MODULE_STATE_Stopped)
    {
        for (uint32 child_index=0 ; child_index<GetChildCount() ; ++child_index)
        {
            Module* child_module = static_cast<Module*>(&GetChild(child_index));
            if (child_module->HasAttribute(MODULE_ATTRIBUTE_Automatic))
                COFFEE_SendEvent(*child_module, MODULE_EVENT_Stop, Module);
        }
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnLeaveStateTransition(Module, MODULE_STATE_Sleeping, MODULE_STATE_Stopped)
    {
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_OnUpdateStateTransition(Module, MODULE_STATE_Sleeping, MODULE_STATE_Stopped)
    {
        for (uint32 child_index=0 ; child_index<GetChildCount() ; ++child_index)
        {
            Module* child_module = static_cast<Module*>(&GetChild(child_index));
            if (child_module->HasAttribute(MODULE_ATTRIBUTE_Automatic)
                && ((child_module->GetState() != MODULE_STATE_Stopped)
                    || child_module->IsThreadRunning()))
            {
                return false;
            }
        }
        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Module::_InternalUpdate()
    {
        _LockUpdate();
        for (int32 child_index=0 ; child_index<(int32)GetChildCount() ; ++child_index)
        {
            uint32 child_count = GetChildCount();
            Module* child_module(static_cast<Module*>(&GetChild(child_index)));
            if (!child_module->IsThreadRunning())
            {
                child_module->Update(_TimeStep);
            }
            else if (child_module->IsRunning())
            {
                child_module->OnMainThreadUpdate(_TimeStep);
            }

            if (child_count!=GetChildCount())
            {
                --child_index;
                COFFEE_Assert(child_count-1==(int32)GetChildCount(),
                    core::ERROR_CODE_Unexpected, "Unexpected module error");
            }
        }
        COFFEE_UpdateStateMachine(Module);
        _UnlockUpdate();
        _ProcessEvents();
    }

    //--------------------------------------------------------------------------------------------//

    void Module::_InternalFixedUpdate()
    {
        // for now fixed update is handled for the root module only
        if (!HasParent() && _FixedTimeStep>0.0f)
        {
            _FixedTime += _TimeStep.GetSecondCount();
            _TimeStep.SetSecondCount(_FixedTimeStep);
            uint32 steps = (uint32)Floor(_FixedTime/_FixedTimeStep+0.5f);
            _FixedTime -= steps*_FixedTimeStep;
            if (_FixedTime<0.0f)
                _FixedTime = 0.0f;
            _ItIsFixedUpdate = true;
            for (uint32 i=0 ; i<steps ; ++i)
            {
                for (uint32 child_index=0 ; child_index<GetChildCount() ; ++child_index)
                {
                    Module* child_module(static_cast<Module*>(&GetChild(child_index)));
                    if (child_module->HasAttribute(MODULE_ATTRIBUTE_FixedTimeStep))
                    {
                        if (!child_module->IsThreadRunning())
                        {
                            child_module->Update(_TimeStep);
                        }
                        else if (child_module->IsRunning())
                        {
                            child_module->OnMainThreadUpdate(_TimeStep);
                        }
                    }
                }
            }
            _ItIsFixedUpdate = false;
        }
    }

}
}
