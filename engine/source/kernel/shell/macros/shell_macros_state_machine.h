#ifndef _COFFEE_SHELL_MACROS_STATE_MACHINE_H_
#define _COFFEE_SHELL_MACROS_STATE_MACHINE_H_

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_DeclareStateMachine
/// @brief State machine declaration
//------------------------------------------------------------------------------------------------//
#define COFFEE_DeclareStateMachine(_class_) \
    public: \
        uint32 GetState() const { return _class_##_StateMachine.GetCurrentStateIdentifier(); } \
        const coffee::shell::StateMachine & GetStateMachine() const { return _class_##_StateMachine; } \
        coffee::shell::StateMachine & GetStateMachine() { return _class_##_StateMachine; } \
        virtual bool OnEvent(shell::Event & event); \
        virtual bool IsLockingEvents() const { return GetStateMachine().HasWantedState(); } \
    private: \
        void InitializeStateMachineStates_##_class_(uint32 initial_state); \
        void InitializeStateMachineStateTransitions_##_class_(); \
        coffee::shell::StateMachine _class_##_StateMachine; \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_DeclareState
/// @brief State declaration
//------------------------------------------------------------------------------------------------//
#define COFFEE_DeclareState(_class_, _state_) \
    public: \
        void OnEnterState_##_state_(shell::Event & event); \
        static void STATIC_OnEnterState_##_state_(void * instance, shell::Event & event) \
        { \
            ((_class_ *) instance)->OnEnterState_##_state_(event); \
        } \
        void OnLeaveState_##_state_(shell::Event & event); \
        static void STATIC_OnLeaveState_##_state_(void * instance, shell::Event & event) \
        { \
            ((_class_ *) instance)->OnLeaveState_##_state_(event); \
        } \
        void OnUpdateState_##_state_(shell::Event & event); \
        static void STATIC_OnUpdateState_##_state_(void * instance, shell::Event & event) \
        { \
            ((_class_ *) instance)->OnUpdateState_##_state_(event); \
        } \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_DeclareStateTransition
/// @brief State transition declaration
//------------------------------------------------------------------------------------------------//
#define COFFEE_DeclareStateTransition(_class_, _source_state_, _destination_state_) \
    public: \
        void OnEnterStateTransition_##_source_state_##_destination_state_(shell::Event & event); \
        static void STATIC_OnEnterStateTransition_##_source_state_##_destination_state_(void * instance, shell::Event & event) \
        { \
            ((_class_ *) instance)->OnEnterStateTransition_##_source_state_##_destination_state_(event); \
        } \
        void OnLeaveStateTransition_##_source_state_##_destination_state_(shell::Event & event); \
        static void STATIC_OnLeaveStateTransition_##_source_state_##_destination_state_(void * instance, shell::Event & event) \
        { \
            ((_class_ *) instance)->OnLeaveStateTransition_##_source_state_##_destination_state_(event); \
        } \
        bool OnUpdateStateTransition_##_source_state_##_destination_state_(shell::Event & event); \
        static bool STATIC_OnUpdateStateTransition_##_source_state_##_destination_state_(void * instance, shell::Event & event) \
        { \
            return ((_class_ *) instance)->OnUpdateStateTransition_##_source_state_##_destination_state_(event); \
        } \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_DeclareEmptyStateTransition
/// @brief Empty state transition declaration
//------------------------------------------------------------------------------------------------//
#define COFFEE_DeclareEmptyStateTransition(_class_, _source_state_, _destination_state_)

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_InitializeStateMachine
/// @brief State machine initialization
//------------------------------------------------------------------------------------------------//
#define COFFEE_InitializeStateMachine(_class_, _initial_state_) \
    InitializeStateMachineStates_##_class_(_initial_state_); \
    InitializeStateMachineStateTransitions_##_class_()

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_UpdateStateMachine
/// @brief Update state machine
//------------------------------------------------------------------------------------------------//
#define COFFEE_UpdateStateMachine(_class_) \
    _class_##_StateMachine.Update()

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_BeginStateMachineTriggers
/// @brief Implement state machine triggers
//------------------------------------------------------------------------------------------------//
#define COFFEE_BeginStateMachineTriggers(_class_, _parent_class_) \
    bool _class_::OnEvent(shell::Event & event) \
    { \
        if(&event.GetCode().GetType() != &_class_ ::GetClassMetaType()) \
            return _parent_class_::OnEvent(event); \
        if (_HandleEvent(event)) return true; \
        coffee::shell::StateMachine * state_machine = &_class_##_StateMachine; \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_RegisterStateTrigger
/// @brief Add a trigger
//------------------------------------------------------------------------------------------------//
#define COFFEE_RegisterStateTrigger(_event_code_, _state_identifier_) \
        if(event.GetCode().GetIdentifier() == _event_code_) \
        { \
            state_machine->TriggerState(_state_identifier_, event); \
            return true; \
        } \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_EndStateMachineTriggers
/// @brief End state machine triggers
//------------------------------------------------------------------------------------------------//
#define COFFEE_EndStateMachineTriggers() \
        return false; \
    } \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_BeginStateMachineStates
/// @brief Begin states registration
//------------------------------------------------------------------------------------------------//
#define COFFEE_BeginStateMachineStates(_class_, _parent_class_) \
    void _class_::InitializeStateMachineStates_##_class_(uint32 initial_state) \
    { \
        coffee::shell::StateMachine * state_machine = &_class_##_StateMachine; \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_RegisterState
/// @brief Register state
//------------------------------------------------------------------------------------------------//
#define COFFEE_RegisterState(_state_) \
        state_machine->RegisterState(*COFFEE_New(coffee::shell::State, _state_, this, &STATIC_OnEnterState_##_state_, &STATIC_OnLeaveState_##_state_, &STATIC_OnUpdateState_##_state_)); \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_EndStateMachineStates
/// @brief End state registration
//------------------------------------------------------------------------------------------------//
#define COFFEE_EndStateMachineStates() \
        state_machine->ForceCurrentState(initial_state); \
    } \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_OnEnterState
/// @brief Implement state "OnEnter"
//------------------------------------------------------------------------------------------------//
#define COFFEE_OnEnterState(_class_, _state_) \
    void _class_::OnEnterState_##_state_(shell::Event & event) \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_OnLeaveState
/// @brief Implement state "OnLeave"
//------------------------------------------------------------------------------------------------//
#define COFFEE_OnLeaveState(_class_, _state_) \
    void _class_::OnLeaveState_##_state_(shell::Event & event) \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_OnUpdateState
/// @brief Implement state "OnUpdate"
//------------------------------------------------------------------------------------------------//
#define COFFEE_OnUpdateState(_class_, _state_) \
    void _class_::OnUpdateState_##_state_(shell::Event & event) \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_BeginStateMachineStateTransitions
/// @brief Begin transitions registration
//------------------------------------------------------------------------------------------------//
#define COFFEE_BeginStateMachineStateTransitions(_class_, _parent_class_) \
    void _class_::InitializeStateMachineStateTransitions_##_class_() \
    { \
        coffee::shell::StateMachine * state_machine = &_class_##_StateMachine; \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_RegisterStateTransition
/// @brief Register state transition
//------------------------------------------------------------------------------------------------//
#define COFFEE_RegisterStateTransition(_source_state_, _destination_state_) \
        state_machine->RegisterStateTransition(*COFFEE_New(coffee::shell::StateTransition, _source_state_, _destination_state_, this, &STATIC_OnEnterStateTransition_##_source_state_##_destination_state_, &STATIC_OnLeaveStateTransition_##_source_state_##_destination_state_, &STATIC_OnUpdateStateTransition_##_source_state_##_destination_state_)); \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_RegisterEmptyStateTransition
/// @brief Register empty state transition
//------------------------------------------------------------------------------------------------//
#define COFFEE_RegisterEmptyStateTransition(_source_state_, _destination_state_) \
    state_machine->RegisterStateTransition(*COFFEE_New(coffee::shell::StateTransition, _source_state_, _destination_state_, this)); \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_EndStateMachineStateTransitions
/// @brief End transitions registration
//------------------------------------------------------------------------------------------------//
#define COFFEE_EndStateMachineStateTransitions() \
    } \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_OnEnterStateTransition
/// @brief Implement transition "OnEnter"
//------------------------------------------------------------------------------------------------//
#define COFFEE_OnEnterStateTransition(_class_, _source_state_, _destination_state_) \
    void _class_::OnEnterStateTransition_##_source_state_##_destination_state_(shell::Event & event) \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_OnLeaveStateTransition
/// @brief Implement transition "OnLeave"
//------------------------------------------------------------------------------------------------//
#define COFFEE_OnLeaveStateTransition(_class_, _source_state_, _destination_state_) \
    void _class_::OnLeaveStateTransition_##_source_state_##_destination_state_(shell::Event & event) \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_OnUpdateStateTransition
/// @brief Implement transition "OnUpdate"
//------------------------------------------------------------------------------------------------//
#define COFFEE_OnUpdateStateTransition(_class_, _source_state_, _destination_state_) \
    bool _class_::OnUpdateStateTransition_##_source_state_##_destination_state_(shell::Event & event) \

#endif
