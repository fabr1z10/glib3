#include <monkey/components/stateactions.h>
#include <monkey/entity.h>
#include <monkey/components/animator.h>
#include <monkey/python/wrap1.h>

StateTransition::StateTransition(const std::string &state) : StateAction(), m_state(state) {}

StateTransition::StateTransition(const ITab& t) {
    m_state = t.get<std::string>("state");
}
void StateTransition::Run(StateMachine * sm) {
    sm->SetState(m_state);
}

StateFunc::StateFunc(const ITab&t) {
    m_callback = t.get<pybind11::function>("f");
}


void StateFunc::Run(StateMachine * sm) {
    auto obj = Wrap1::create(sm->GetObject());
    m_callback(obj);
}