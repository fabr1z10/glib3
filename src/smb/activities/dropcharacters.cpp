#include <platformer/activities/dropcharacters.h>
#include <monkey/engine.h>
#include <monkey/components/platform.h>

DropCharacters::DropCharacters() : TargetActivity() {}

void DropCharacters::Start() {
    TargetActivity::Start();
    m_entity->GetComponent<PlatformComponent>()->RemoveCharacters();
    //entity->SetPosition(m_pos);
    SetComplete();

}