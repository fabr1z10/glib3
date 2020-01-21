#include <platformer/states/hitbase.h>
#include <monkey/engine.h>
#include <monkey/components/animator.h>
#include <monkey/collisionengine.h>

#include <monkey/components/collider.h>

HitBase::HitBase(const std::string &anim) : m_anim(anim)
{

}

HitBase::HitBase (const HitBase& orig) : PlatformerState(orig) {
    m_anim = orig.m_anim;
}


void HitBase::AttachStateMachine(StateMachine *sm) {
    PlatformerState::AttachStateMachine(sm);

}

void HitBase::Init() {
    ResetAnimation();
}


void HitBase::ResetAnimation() {
    m_animator->SetAnimation(m_anim);
}

void HitBase::HandleCollision() {
    if (m_animator->IsComplete()) {
        m_sm->SetState("walk");
    }
}