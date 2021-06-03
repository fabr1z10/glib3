#include "turn.h"
#include "../components/character.h"
#include <monkey/engine.h>
#include <monkey/components/ianimator.h>


Turn::Turn(const ITab& t) : TargetActivity(t) {
    m_dir = t.get<std::string>("dir")[0];
}


void Turn::Start() {
    TargetActivity::Start();
    m_entity->GetComponent<CharacterController>()->turn(m_dir);
    SetComplete();
}
