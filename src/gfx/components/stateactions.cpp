#include <gfx/components/stateactions.h>

StateTransition::StateTransition(const std::string &state) : StateAction(), m_state(state) {}

void StateTransition::Run(StateMachine * sm) {
    sm->SetState(m_state);
}

StateCallback::StateCallback(luabridge::LuaRef f) : StateAction(), m_f(f) {
}

void StateCallback::Run(StateMachine *) {
    m_f();
}