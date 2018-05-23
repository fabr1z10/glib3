#include <gfx/animate.h>
#include <gfx/renderer.h>

Animate::Animate(int activityId, Entity* entity, const std::string& animId) : Activity(activityId), m_animId{animId}, m_entity{entity} {

}

void Animate::Start() {
    m_entity->GetComponent<Renderer>()->SetAnimation(m_animId);
    SetComplete();

}