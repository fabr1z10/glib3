#include <monkey/activities/turn.h>
#include <gfx/engine.h>
#include <monkey/components/charactercomponent.h>

void Turn::Start() {

    TargetActivity::Start();
    auto state = dynamic_cast<StateCharacter*>(m_entity->GetComponent<StateMachine2>());
    state->SetDirection(m_dir);
    SetComplete();

}
