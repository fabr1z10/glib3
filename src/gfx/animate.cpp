#include <gfx/animate.h>
#include <gfx/renderer.h>
#include <gfx/engine.h>

Animate::Animate(int activityId, Entity* entity, const std::string& animId, bool flipX) : Activity(activityId), m_animId{animId}, m_entity{entity}, m_flipX{flipX} {

}

Animate::Animate(int activityId, const std::string& actorId, const std::string& animId, bool flipX )
: Activity(activityId), m_animId{animId}, m_entity{nullptr}, m_actorId{actorId}, m_flipX{flipX} {

}

void Animate::Start() {
    if (m_entity == nullptr) {
        m_entity = Engine::get().GetRef<Entity>(m_actorId);

    }
    auto renderer = m_entity->GetComponent<Renderer>();
    renderer->SetFlipX(m_flipX);
    renderer->SetAnimation(m_animId);
    SetComplete();

}