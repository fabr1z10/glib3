#include <monkey/activities/animate.h>
#include <monkey/components/animator.h>
#include <monkey/engine.h>

Animate::Animate(const std::string& animId, bool fwd, int flipX ) : TargetActivity(),
    m_animId{animId}, m_flipX{flipX}, m_forward(fwd) {
}

Animate::Animate(const LuaTable & t) : TargetActivity(t) {
    m_animId = t.Get<std::string>("anim");
    m_forward = t.Get<bool>("fwd", true);
    int flip{0};
    if (t.HasKey("flipx")) {
        flip = t.Get<bool>("flipx") ? 2 : 1;
    }
    m_flipX = flip;
    bool sync = t.Get<bool>("sync", false);
    SetSync(sync);
}

Animate::Animate(const ITable & t) : TargetActivity(t) {
    m_animId = t.get<std::string>("anim");
    m_forward = t.get<bool>("fwd", true);
    int flip{0};
    if (t.hasKey("flipx")) {
        flip = t.get<bool>("flipx") ? 2 : 1;
    }
    m_flipX = flip;
    bool sync = t.get<bool>("sync", false);
    SetSync(sync);
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
