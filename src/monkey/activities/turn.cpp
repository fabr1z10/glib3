#include <monkey/activities/turn.h>
#include <gfx/engine.h>
#include <monkey/components/charactercomponent.h>

void Turn::Start() {

    auto actor = Engine::get().GetRef<Entity>(m_actorId);
    auto state = dynamic_cast<StateCharacter*>(actor->GetComponent<StateMachine2>());
    state->SetDirection(m_dir);
    SetComplete();

}