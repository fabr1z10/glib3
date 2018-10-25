#include <gfx/activities/animate.h>
#include <gfx/components/renderer.h>
#include <gfx/engine.h>

Animate::Animate(Entity* entity, const std::string& animId, int flip) : Activity(), m_animId{animId}, m_entity{entity}, m_flipX{flip}, m_loop{0} {

}

Animate::Animate(const std::string& actorId, const std::string& animId, int flipX )
: Activity(), m_animId{animId}, m_entity{nullptr}, m_actorId{actorId}, m_flipX{flipX}, m_loop{0} {

}

void Animate::Start() {
    if (m_entity == nullptr) {
        m_entity = Engine::get().GetRef<Entity>(m_actorId);

    }
    m_renderer = m_entity->GetComponent<Renderer>();

    if (m_renderer == nullptr)
        GLIB_FAIL("Error! No renderer found for " << m_actorId << " when trying to animate " << m_animId);
    if (m_flipX != 0)
        m_renderer->SetFlipX(m_flipX == 2);
    m_renderer->SetAnimation(m_animId);
    if (m_loop == 0) {
        SetComplete();
    }

}

void Animate::Run(float dt) {
    // runs only if loop is set
    if (m_renderer->GetLoopCount() == m_loop)
        SetComplete();

}