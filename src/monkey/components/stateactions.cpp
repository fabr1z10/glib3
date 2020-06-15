#include <monkey/components/stateactions.h>
#include <monkey/entity.h>
#include <monkey/components/animator.h>

StateTransition::StateTransition(const std::string &state) : StateAction(), m_state(state) {}

void StateTransition::Run(StateMachine * sm) {
    sm->SetState(m_state);
}


void StateFunc::Run(StateMachine *) {
    m_f();
}