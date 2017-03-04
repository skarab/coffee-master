#include "kernel/shell/state/shell_state_machine.h"

//-DEFINES----------------------------------------------------------------------------------------//
#define COFFEE_SHELL_STATE_MACHINE_DefaultHistorySize    5
#define COFFEE_SHELL_STATE_MACHINE_MaximumTransitionsToSwitchState   3

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(shell::StateMachine);
    COFFEE_EndType();

namespace shell
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    StateMachine::StateMachine() :
        _CurrentState(NULL),
        _WantedState(NULL),
        _CurrentStateTransition(NULL)
    {
        _StateTransitionPath.Reserve(COFFEE_SHELL_STATE_MACHINE_MaximumTransitionsToSwitchState);
        SetStateHistorySize(COFFEE_SHELL_STATE_MACHINE_DefaultHistorySize);
    }

    //--------------------------------------------------------------------------------------------//

    StateMachine::~StateMachine()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void StateMachine::SetCurrentState(uint32 state_identifier)
    {
        State * state = FindState(state_identifier);

        if (state)
        {
            if (HasCurrentState())
            {
                GetCurrentState().Leave();
                _AddCurrentStateToHistory();
            }
            else if (HasCurrentStateTransition())
            {
                GetCurrentStateTransition().Leave();
            }

            _CurrentState = state;

            if (HasCurrentStateTransition())
            {
                _CurrentState->SetTriggerEvent(GetCurrentStateTransition().GetTriggerEvent());
                _CurrentStateTransition = NULL;
            }

            GetCurrentState().Enter();
        }
    }

    //--------------------------------------------------------------------------------------------//

    void StateMachine::ForceCurrentState(uint32 state_identifier)
    {
        State* state = FindState(state_identifier);
        if (state)
            _CurrentState = state;
    }

    //--------------------------------------------------------------------------------------------//

    const State& StateMachine::GetCurrentState() const
    {
        return *_CurrentState;
    }

    //--------------------------------------------------------------------------------------------//

    State& StateMachine::GetCurrentState()
    {
        return *_CurrentState;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 StateMachine::GetCurrentStateIdentifier() const
    {
        if (HasCurrentState())
            return GetCurrentState().GetIdentifier();
        return NONE;
    }

    //--------------------------------------------------------------------------------------------//

    void StateMachine::SetCurrentStateTransition(uint32 state_transition_index, const Event& event)
    {
        if (HasCurrentState())
        {
            GetCurrentState().Leave();
            _AddCurrentStateToHistory();
            _CurrentState = NULL;
        }

        _CurrentStateTransition = _StateTransitionArray[state_transition_index];
        _CurrentStateTransition->SetTriggerEvent(event);
        _CurrentStateTransition->Enter();
    }

    //--------------------------------------------------------------------------------------------//

    const StateTransition& StateMachine::GetCurrentStateTransition() const
    {
        return *_CurrentStateTransition;
    }

    //--------------------------------------------------------------------------------------------//

    StateTransition& StateMachine::GetCurrentStateTransition()
    {
        return *_CurrentStateTransition;
    }

    //--------------------------------------------------------------------------------------------//

    void StateMachine::SetStateHistorySize(uint32 history_size)
    {
        _StateHistory.Resize(history_size);
        ClearHistory();
    }

    //--------------------------------------------------------------------------------------------//

    uint32 StateMachine::GetStateHistorySize() const
    {
        return _StateHistory.GetSize();
    }

    //--------------------------------------------------------------------------------------------//

    const State* StateMachine::GetStateHistory(uint32 history_index) const
    {
        return _StateHistory[_StateHistory.GetSize()-1-history_index];
    }

    //--------------------------------------------------------------------------------------------//

    State* StateMachine::GetStateHistory(uint32 history_index)
    {
        return _StateHistory[_StateHistory.GetSize()-1-history_index];
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool StateMachine::HasCurrentState() const
    {
        return _CurrentState!=NULL;
    }

    //--------------------------------------------------------------------------------------------//

    bool StateMachine::HasCurrentStateTransition() const
    {
        return _CurrentStateTransition!=NULL;
    }

    //--------------------------------------------------------------------------------------------//

    bool StateMachine::HasWantedState() const
    {
        return _WantedState!=NULL;
    }

    //--------------------------------------------------------------------------------------------//

    bool StateMachine::HasStateHistory() const
    {
        return ((GetStateHistorySize()>0) && (GetStateHistory(0)!=NULL));
    }

    //--------------------------------------------------------------------------------------------//

    State* StateMachine::FindState(uint32 state_identifier) const
    {
        for (uint32 state_index=0 ; state_index<_StateArray.GetSize() ; ++state_index)
        {
            if (_StateArray[state_index]->GetIdentifier()==state_identifier)
                return _StateArray[state_index];
        }
        return NULL;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void StateMachine::RegisterState(State& state)
    {
        _StateArray.AddItem(&state);
    }

    //--------------------------------------------------------------------------------------------//

    void StateMachine::RegisterStateTransition(StateTransition& state_transition)
    {
        _StateTransitionArray.AddItem(&state_transition);
    }

    //--------------------------------------------------------------------------------------------//

    void StateMachine::ClearHistory()
    {
        for (uint32 history_index=0 ; history_index<_StateHistory.GetSize() ; ++history_index)
            _StateHistory[history_index] = NULL;
    }

    //--------------------------------------------------------------------------------------------//

    void StateMachine::Update()
    {
        if (HasCurrentState())
        {
            GetCurrentState().Update();

            if (HasWantedState())
            {
                SetCurrentStateTransition(_StateTransitionPath[0],
                    GetCurrentState().GetTriggerEvent());

                _StateTransitionPath.Remove(0);
            }
        }
        else if (HasCurrentStateTransition())
        {
            if (GetCurrentStateTransition().Update())
            {
                if (_StateTransitionPath.GetSize()==0)
                    _WantedState = NULL;

                SetCurrentState(GetCurrentStateTransition().GetDestinationIdentifier());
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    void StateMachine::TriggerState(uint32 state_identifier, const Event & event)
    {
        State* state = FindState(state_identifier);
        if (state)
        {
            if (!HasCurrentState())
            {
                COFFEE_Assert(HasCurrentStateTransition() && _WantedState!=NULL,
                    core::ERROR_CODE_IncorrectUsage, "State machine is broken.");
                StateMachine::Update();
            }

            COFFEE_Assert(HasCurrentState(),
                core::ERROR_CODE_IncorrectUsage, "State machine is broken.");
            COFFEE_Assert(&GetCurrentState() != state, core::ERROR_CODE_IncorrectUsage,
                "Triggered state is already the current state.");
            COFFEE_Assert(!HasWantedState(), core::ERROR_CODE_IncorrectUsage,
                "There is already a wanted state.");

            if (_GenerateStateTransitionPath(GetCurrentState(), *state))
            {
                GetCurrentState().SetTriggerEvent(event);
                _WantedState = state;
            }
        }
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void StateMachine::_AddCurrentStateToHistory()
    {
        if (_StateHistory.GetSize()>1)
        {
            for (uint32 history_index=0 ; history_index<_StateHistory.GetSize()-1 ; ++history_index)
                _StateHistory[history_index] = _StateHistory[history_index+1];
        }

        if (_StateHistory.GetSize()>0)
            _StateHistory[_StateHistory.GetSize()-1 ] = _CurrentState;
    }

    //--------------------------------------------------------------------------------------------//

    bool StateMachine::_GenerateStateTransitionPath(const State& starting_state,
        const State& ending_state)
    {
        return _BuildStateTransitionPath(NULL, starting_state.GetIdentifier(),
            ending_state.GetIdentifier());
    }

    //--------------------------------------------------------------------------------------------//

    // .ToDo. optimize this
    bool StateMachine::_BuildStateTransitionPath(bool* state_transition_used_array,
        uint32 source_identifier, uint32 destination_identifier)
    {
        bool* current_state_transition_used_array;
        uint32 state_transition_index;

        current_state_transition_used_array =
            (bool*)COFFEE_Allocate(sizeof(bool)*_StateTransitionArray.GetSize());

        if (state_transition_used_array==NULL)
        {
            _MatchingStateTransitionPath.Clear();
            _StateTransitionPath.Clear();
            COFFEE_Set(current_state_transition_used_array, 0,
                sizeof(bool)*_StateTransitionArray.GetSize());
        }
        else
        {
            COFFEE_Copy(current_state_transition_used_array, state_transition_used_array,
                sizeof(bool)*_StateTransitionArray.GetSize());
        }

        for (state_transition_index=0 ; state_transition_index<_StateTransitionArray.GetSize() ;
            ++state_transition_index)
        {
            if (!current_state_transition_used_array[state_transition_index]
                && _StateTransitionArray[state_transition_index]->GetSourceIdentifier()
                    == source_identifier)
            {
                if (_StateTransitionArray[state_transition_index]->GetDestinationIdentifier()
                    == destination_identifier)
                {
                    _MatchingStateTransitionPath.AddItem(state_transition_index);
                    COFFEE_Free(current_state_transition_used_array);

                    if (_StateTransitionPath.GetSize()==0)
                        _StateTransitionPath = _MatchingStateTransitionPath;
                    
                    return true;
                }

                if (_MatchingStateTransitionPath.GetSize()+1
                    == COFFEE_SHELL_STATE_MACHINE_MaximumTransitionsToSwitchState)
                {
                    COFFEE_Free(current_state_transition_used_array);
                    return false;
                }

                _MatchingStateTransitionPath.AddItem(state_transition_index);
                current_state_transition_used_array[state_transition_index] = true;

                if (_BuildStateTransitionPath(current_state_transition_used_array,
                    _StateTransitionArray[state_transition_index]->GetDestinationIdentifier(),
                    destination_identifier))
                {
                    if (state_transition_used_array==NULL)
                    {
                        if (_StateTransitionPath.GetSize()==0)
                        {
                            _StateTransitionPath = _MatchingStateTransitionPath;
                        }
                        else
                        {
                            if (_MatchingStateTransitionPath.GetSize()<_StateTransitionPath.GetSize())
                                _StateTransitionPath = _MatchingStateTransitionPath;
                        }
                    }
                    else
                    {
                        COFFEE_Free(current_state_transition_used_array);
                        return true;
                    }
                }

                _MatchingStateTransitionPath.Remove(_MatchingStateTransitionPath.GetSize()-1);

                if (state_transition_used_array==NULL)
                {
                    COFFEE_Set(current_state_transition_used_array, 0,
                        sizeof(bool)*_StateTransitionArray.GetSize());
                }
                else
                {
                    COFFEE_Copy(current_state_transition_used_array, state_transition_used_array,
                        sizeof(bool)*_StateTransitionArray.GetSize());
                }
            }
        }

        COFFEE_Free(current_state_transition_used_array);

        if (state_transition_used_array==NULL && _StateTransitionPath.GetSize()>0)
            return true;

        return false;
    }

}
}

//-DEFINES----------------------------------------------------------------------------------------//
#undef COFFEE_SHELL_STATE_MACHINE_DefaultHistorySize
#undef COFFEE_SHELL_STATE_MACHINE_MaximumTransitionsToSwitchState
//------------------------------------------------------------------------------------------------//
