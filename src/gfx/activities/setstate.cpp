#include <gfx/activities/setstate.h>
#include <gfx/components/statemachine.h>
#include <gfx/engine.h>
#include <gfx/entity.h>

void SetState::Start() {
    TargetActivity::Start();
    auto sm = m_entity->GetComponent<StateMachine>();
    if (sm == nullptr) {
        GLIB_FAIL("Setting the state requires a state machine component attached.");
    }
    sm->SetState(m_state);
    SetComplete();
}
