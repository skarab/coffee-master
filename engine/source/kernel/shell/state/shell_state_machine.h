#ifndef _COFFEE_SHELL_STATE_MACHINE_H_
#define _COFFEE_SHELL_STATE_MACHINE_H_

#include "coffee_includes.h"
#include "kernel/meta/meta.h"
#include "kernel/basic/container/basic_containers.h"
#include "kernel/shell/state/shell_state.h"
#include "kernel/shell/state/shell_state_transition.h"

namespace coffee
{
namespace shell
{
    //--------------------------------------------------------------------------------------------//
    /// State machine
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API StateMachine : public meta::Object
    {
        COFFEE_Type(StateMachine);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        StateMachine();
        virtual ~StateMachine();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetCurrentState(uint32 state_identifier);
        void ForceCurrentState(uint32 state_identifier);
        const State & GetCurrentState() const;
        State & GetCurrentState();
        uint32 GetCurrentStateIdentifier() const;
        void SetCurrentStateTransition(uint32 state_transition_index, const Event & event);
        const StateTransition & GetCurrentStateTransition() const;
        StateTransition & GetCurrentStateTransition();
        void SetStateHistorySize(uint32 history_size);
        uint32 GetStateHistorySize() const;
        const State * GetStateHistory(uint32 history_index) const;
        State * GetStateHistory(uint32 history_index);

        //-QUERIES--------------------------------------------------------------------------------//

        bool HasCurrentState() const;
        bool HasCurrentStateTransition() const;
        bool HasWantedState() const;
        bool HasStateHistory() const;
        State * FindState(uint32 state_identifier) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void RegisterState(State & state);
        void RegisterStateTransition(StateTransition & state_transition);
        void ClearHistory();
        void Update();
        void TriggerState(uint32 state_identifier, const Event & event);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _AddCurrentStateToHistory();
        bool _GenerateStateTransitionPath(const State & starting_state, const State & ending_state);
        bool _BuildStateTransitionPath(bool * state_transition_used_array, uint32 source_identifier,
            uint32 destination_identifier);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Prow<State*, true> _StateArray;
        basic::Prow<StateTransition*, true> _StateTransitionArray;
        State* _CurrentState;
        basic::Prow<State*> _StateHistory;
        State* _WantedState;
        StateTransition* _CurrentStateTransition;
        basic::Array<uint32> _StateTransitionPath;
        basic::Array<uint32> _MatchingStateTransitionPath;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, StateMachine);
}
}
#endif
