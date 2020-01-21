#include <platformer/states/hitjump.h>
#include <monkey/components/stateactions.h>
#include <monkey/components/inputmethod.h>
#include <monkey/components/animator.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/controller2d.h>

HitJump::HitJump(const std::string &anim, float speed, float a) :
    HitBase(anim), m_acceleration(a), m_speed(speed)
{

}

HitJump::HitJump(const HitJump& orig) : HitBase(orig) {
    m_speed = orig.m_speed;
    m_acceleration = orig.m_acceleration;
}

std::shared_ptr<State> HitJump::clone() const {
    return std::make_shared<HitJump>(*this);
}

void HitJump::Run(double dt) {

    bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
    bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);

    if (m_controller->grounded() && m_dynamics->m_velocity.y < 0) {
        m_dynamics->m_velocity.y = 0.0f;
        m_sm->SetState("walk");
    }

    // bump head
    if (m_controller->ceiling())	{
        m_dynamics->m_velocity.y = 0;
    }

    float targetVelocityX = 0.0f;
    if (left || right) {
        m_entity->SetFlipX(left);
        targetVelocityX = m_speed;
    }
    glm::vec3 delta = m_dynamics->step(dt, targetVelocityX, m_acceleration);
    m_controller->Move(delta);

    if (m_animator->IsComplete()) {
        m_sm->SetState("jump");
    }

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
