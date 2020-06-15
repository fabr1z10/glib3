#include "turn.h"
#include <monkey/engine.h>
#include "../components/character.h"


Turn::Turn(const ITable & t) : TargetActivity(t) {
    m_dir = t.get<std::string>("dir")[0];
}


void Turn::Start() {

    TargetActivity::Start();
    auto state = dynamic_cast<StateCharacter*>(m_entity->GetComponent<StateMachine>());
    state->SetDirection(m_dir);
    SetComplete();

}
