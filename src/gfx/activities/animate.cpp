#include <gfx/activities/animate.h>
#include <gfx/components/animator.h>
#include <gfx/engine.h>

Animate::Animate(Entity* entity, const std::string& animId, bool fwd, int flip) : Activity(),
    m_animId{animId}, m_entity{entity}, m_flipX{flip}, m_forward(fwd) {

}

Animate::Animate(const std::string& actorId, const std::string& animId, bool fwd, int flipX )
: Activity(), m_animId{animId}, m_entity{nullptr}, m_actorId{actorId}, m_flipX{flipX}, m_forward(fwd) {

}

void Animate::Start() {
    if (m_entity == nullptr) {
        m_entity = Engine::get().GetRef<Entity>(m_actorId);

    }
    m_animator = m_entity->GetComponent<Animator>();

    if (m_animator == nullptr)
        GLIB_FAIL("Error! No renderer found for " << m_actorId << " when trying to animate " << m_animId);
    if (m_flipX != 0) {
        //m_entity->Set
        m_entity->SetFlipX(m_flipX == 2);
    }
    m_animator->SetPlayForward(m_forward);
    m_animator->SetAnimation(m_animId);
    if (!m_sync) {
        SetComplete();
    }

}

void Animate::Run(float dt) {
    // runs only if loop is set
    if (m_animator->IsComplete()) {
        SetComplete();
    }

}
