#include "turn.h"
#include <monkey/engine.h>
#include "../components/character.h"

Turn::Turn(const LuaTable & t) : TargetActivity(t) {
    m_dir = t.Get<std::string>("dir")[0];
}

void Turn::Start() {

    TargetActivity::Start();
    auto state = dynamic_cast<StateCharacter*>(m_entity->GetComponent<StateMachine>());
    state->SetDirection(m_dir);
    SetComplete();

}
