#include <gfx/components/platform.h>
#include <gfx/entity.h>

using namespace glm;

void PlatformComponent::Start() {
    m_entity->onMove.Register(this, [this](Entity* node) { Move(node); });
    m_lastPosition = m_entity->GetPosition();
}

PlatformComponent::~PlatformComponent() {
    for (auto& c : m_characters)
        c->ForceDetach();
    m_current = nullptr;
}

void PlatformComponent::Move(Entity* node) {
    glm::vec3 currentPosition = node->GetPosition();
    glm::vec3 delta = currentPosition - m_lastPosition;
    for (auto iter = m_characters.begin(); iter != m_characters.end(); iter++) {
        m_current = (*iter);
        m_current->GetObject()->Move(delta);
    }
    m_lastPosition = currentPosition;
}