#include <platformer/states/hit.h>
#include <gfx/components/stateactions.h>>

#include <gfx/components/animator.h>
#include <GLFW/glfw3.h>

Hit::Hit(const std::string &anim, int frame, std::shared_ptr<Shape> attackBox) :
    m_anim(anim), m_frame(frame), m_box(attackBox)
{
    AddKey(GLFW_KEY_LEFT, std::make_shared<StateTransition>("walk"));
    AddKey(GLFW_KEY_RIGHT, std::make_shared<StateTransition>("walk"));

}

Hit::Hit(const Hit& orig) : PlatformerState(orig) {
    m_anim = orig.m_anim;
    m_frame = orig.m_frame;
    m_box = orig.m_box;
}

std::shared_ptr<State> Hit::clone() const {
    return std::make_shared<Hit>(*this);
}

void Hit::Init() {
    m_animator->SetAnimation(m_anim);
}

void Hit::Run(double) {
    if (m_animator->IsComplete()) {
        m_sm->SetState("walk");
    }
    // if player presses L/R while hitting, resume walk



}
//
//HitJump::HitJump(const std::string &anim, int frame, std::shared_ptr<Shape> attackBox) :
//        m_anim(anim), m_frame(frame), m_box(attackBox)
//{
//}
//
//HitJump::HitJump(const HitJump& orig) : PlatformerState(orig) {
//    m_anim = orig.m_anim;
//    m_frame = orig.m_frame;
//    m_box = orig.m_box;
//}
//
//std::shared_ptr<State> HitJump::clone() const {
//    return std::make_shared<HitJump>(*this);
//}
//
//void HitJump::Init() {
//    m_animator->SetAnimation(m_anim);
//}
//
//void HitJump::Run(double) {
//    if (m_animator->IsComplete()) {
//        m_sm->SetState("jump");
//    }
//    // if player presses L/R while hitting, resume walk
//
//
//
//}
