#include <monkey/activities/turn.h>
#include <gfx/engine.h>
#include <monkey/components/charactercomponent.h>

void Turn::Start() {

    TargetActivity::Start();
    auto state = dynamic_cast<StateCharacter*>(m_entity->GetComponent<StateMachine>());
    state->SetDirection(m_dir);
    SetComplete();

}
