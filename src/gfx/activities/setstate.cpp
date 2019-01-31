#include <gfx/activities/setstate.h>
#include <gfx/components/statemachine2.h>
#include <gfx/engine.h>
#include <gfx/entity.h>

void SetState::Start() {
    auto entity = Engine::get().GetRef<Entity>(m_actorId);
    auto sm = entity->GetComponent<StateMachine2>();
    if (sm == nullptr) {
        GLIB_FAIL("Setting the state requires a state machine component attached.");
    }
    sm->SetState(m_state);
    SetComplete();
}