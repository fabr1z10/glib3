#include <gfx/activities/animate.h>
#include <gfx/components/animator.h>
#include <gfx/engine.h>

Animate::Animate(int id, const std::string& animId, bool fwd, int flipX ) : Activity(),
    m_id(id), m_animId{animId}, m_entity{nullptr}, m_flipX{flipX}, m_forward(fwd) {
}

void Animate::Start() {
    m_entity = Ref::GetFromId<Entity>(m_id);
    m_animator = m_entity->GetComponent<Animator>();
    if (m_animator == nullptr) {
        GLIB_FAIL("No animator found. Required for animate action\n");
    }
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
