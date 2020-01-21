#include "turn.h"
#include <monkey/engine.h>
#include "../components/character.h"

void Turn::Start() {

    TargetActivity::Start();
    auto state = dynamic_cast<StateCharacter*>(m_entity->GetComponent<StateMachine>());
    state->SetDirection(m_dir);
    SetComplete();

}
