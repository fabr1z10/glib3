#include <gfx/basicstate.h>
#include <gfx/entity.h>
#include <gfx/engine.h>
#include <gfx/renderer.h>

BasicState::BasicState(const std::string &anim, const std::vector<std::string>& colliders) : State(), m_anim(anim), m_activeColliders(colliders) {}

void BasicState::Init(Entity* e) {
    State::Init(e);
    m_renderer = m_entity->GetComponent<Renderer>();
    m_colliderContainer = m_entity->GetNamedChild("colliders");
    for (auto& s : m_activeColliders)
        m_colliders.push_back(m_colliderContainer->GetNamedChild(s));
}


void BasicState::Start() {
    m_renderer->SetAnimation(m_anim);
    auto& v = m_colliderContainer->GetChildren();
    for (auto& c : v)
        c->SetActive(false);
    for (auto& c : m_colliders)
        c->SetActive(true);
}

BasicStateFallback::BasicStateFallback(const std::string &anim, const std::string &fallback, const std::vector<std::string>& colliders) :
        BasicState(anim, colliders), m_fallback(fallback) {


}

bool BasicStateFallback::Run(double) {
    if (m_renderer->GetLoopCount() > 0) {
        m_nextState = m_fallback;
        return true;
    }
    return false;
}
