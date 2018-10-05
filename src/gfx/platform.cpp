#include <gfx/platform.h>
#include <gfx/entity.h>

using namespace glm;

void PlatformComponent::Start() {
    m_entity->onMove.Register(this, [this](Entity* node) { Move(node); });
}

PlatformComponent::~PlatformComponent() {
    for (auto& c : m_characters)
        c->ForceDetach();
    m_current = nullptr;
}

void PlatformComponent::Move(Entity* node) {
//    if (m_characters.empty())
//        return;
//    mat4 t = node->GetLastMove();
//    for (auto iter = m_characters.begin(); iter != m_characters.end(); iter++) {
//        m_current = (*iter);
//        m_current->GetObject()->Move(t);
//    }
}