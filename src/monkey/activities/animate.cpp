#include <monkey/activities/animate.h>
#include <monkey/components/animator.h>
#include <monkey/components/spriterenderer.h>

Animate::Animate(const std::string& animId, bool fwd, int flipX ) : TargetActivity(),
    m_animId{animId}, m_flipX{flipX}, m_forward(fwd) {
}


Animate::Animate(const ITab & t) : TargetActivity(t) {
    m_animId = t.get<std::string>("anim");
    m_forward = t.get<bool>("fwd", true);
    int flip{0};
    if (t.has("flipx")) {
        flip = t.get<bool>("flipx") ? 2 : 1;
    }
    m_flipX = flip;
    bool sync = t.get<bool>("sync", false);
    SetSync(sync);
}

void Animate::Start() {
    TargetActivity::Start();
    m_animator = dynamic_cast<AnimationRenderer*>(m_entity->GetComponent<Renderer>());
    if (m_animator == nullptr) {
        GLIB_FAIL("No animator found. Required for animate action\n");
    }
    if (m_flipX != 0) {
        //m_entity->Set
        m_entity->SetFlipX(m_flipX == 2);
    }
    m_animator->setPlayForward(m_forward);
    m_animator->setAnimation(m_animId);
    if (!m_sync) {
        SetComplete();
    }

}

void Animate::Run(float dt) {
    // runs only if loop is set
    if (m_animator->isComplete()) {
        SetComplete();
    }

}
