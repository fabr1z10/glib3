#include <gfx/activities/animate.h>
#include <gfx/components/animator.h>
#include <gfx/engine.h>

Animate::Animate(const std::string& animId, bool fwd, int flipX ) : TargetActivity(),
    m_animId{animId}, m_flipX{flipX}, m_forward(fwd) {
}



void Animate::Start() {
    TargetActivity::Start();
    m_animator = m_entity->GetComponent<IAnimator>();
    if (m_animator == nullptr) {
        GLIB_FAIL("No animator found. Required for animate action\n");
    }
    if (m_flipX != 0) {
        //m_entity->Set
        m_entity->SetFlipX(m_flipX == 2);
    }
    m_animator->SetPlayForward(m_forward);
    m_animator->SetAnimation(m_animId, m_forward);
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
