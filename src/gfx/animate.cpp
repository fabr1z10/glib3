#include <gfx/animate.h>
#include <gfx/renderer.h>

Animate::Animate(int activityId, Entity* entity, const std::string& animId, bool flipX) : Activity(activityId), m_animId{animId}, m_entity{entity}, m_flipX{flipX} {

}

void Animate::Start() {
    auto renderer = m_entity->GetComponent<Renderer>();
    renderer->SetFlipX(m_flipX);
    renderer->SetAnimation(m_animId);
    SetComplete();

}