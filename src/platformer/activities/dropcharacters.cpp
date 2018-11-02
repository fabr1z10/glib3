#include <platformer/activities/dropcharacters.h>
#include <gfx/engine.h>
#include <gfx/components/platform.h>

DropCharacters::DropCharacters(const std::string &actorId, glm::vec2 pos) : Activity(), m_actorId(actorId), m_pos(pos) {}

void DropCharacters::Start() {
    auto entity = Engine::get().GetRef<Entity>(m_actorId);
    entity->GetComponent<PlatformComponent>()->RemoveCharacters();
    entity->SetPosition(m_pos);
    SetComplete();

}