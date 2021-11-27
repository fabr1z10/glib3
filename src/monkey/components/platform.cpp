#include <monkey/components/platform.h>
#include <monkey/entity.h>

using namespace glm;

PlatformComponent::PlatformComponent(const ITab& t) : Component(t) {}

void PlatformComponent::Start() {
    m_entity->onMove.Register(this, [this](Entity* node) { Move(node); });
    m_lastPosition = m_entity->GetPosition();
}

PlatformComponent::~PlatformComponent() {
    for (auto& c : m_characters)
        c->ForceDetach(m_entity);
    m_current = nullptr;
}

void PlatformComponent::Move(Entity* node) {
    glm::vec3 currentPosition = node->GetPosition();
    glm::vec3 delta = currentPosition - m_lastPosition;
    if (delta.x != 0.0f || delta.y != 0.0f) {
        for (auto iter = m_characters.begin(); iter != m_characters.end(); iter++) {


            m_current = (*iter);
            m_current->forceMove(delta);

        }
    }
    m_lastPosition = currentPosition;
}

void PlatformComponent::RemoveCharacters() {
    for (auto& c : m_characters) {
        c->ForceDetach(m_entity);
    }
    m_characters.clear();
}
