#include <monkey/activities/setstate.h>
#include <monkey/components/statemachine.h>
#include <monkey/engine.h>
#include <monkey/entity.h>

void SetState::Start() {
    TargetActivity::Start();
    auto sm = m_entity->GetComponent<StateMachine>();
    if (sm == nullptr) {
        GLIB_FAIL("Setting the state requires a state machine component attached.");
    }
    sm->SetState(m_state);
    SetComplete();
}

void SetStateWithArgs::Start() {
    TargetActivity::Start();
    auto sm = m_entity->GetComponent<StateMachine>();
    if (sm == nullptr) {
        GLIB_FAIL("Setting the state requires a state machine component attached.");
    }
    sm->SetState(m_state, m_args);
    SetComplete();
}