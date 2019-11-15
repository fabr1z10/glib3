#include <platformer/activities/dropcharacters.h>
#include <gfx/engine.h>
#include <gfx/components/platform.h>

DropCharacters::DropCharacters() : TargetActivity() {}

void DropCharacters::Start() {
    TargetActivity::Start();
    m_entity->GetComponent<PlatformComponent>()->RemoveCharacters();
    //entity->SetPosition(m_pos);
    SetComplete();

}