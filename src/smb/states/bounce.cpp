//#include "platformer/states/bounce.h"
//#include <monkey/components/icontroller.h>
//#include <monkey/components/dynamics2d.h>
//
//Bounce::Bounce(float speed, float acceleration) : PlatformerState(), m_speed(speed), m_acceleration(acceleration) {}
//
//Bounce::Bounce(const Bounce &orig) : PlatformerState(orig) {
//    m_speed = orig.m_speed;
//    m_acceleration = orig.m_acceleration;
//}
//
//std::shared_ptr<State> Bounce::clone() const {
//    return std::make_shared<Bounce>(*this);
//}
//
//void Bounce::Init() {
//
//}
//
//void Bounce::End() {
//
//}
//
//void Bounce::Run (double dt) {
//
//    if (m_controller->grounded() && m_dynamics->m_velocity.y < 0) {
//        if (!m_bounce) {
//            m_dynamics->m_velocity.y = 0.0f;
//            m_sm->SetState(m_walkState);
//        } else {
//            m_dynamics->m_velocity.y = m_bounceFactor * m_dynamics->m_velocity.y;
//        }
//        return;
//    }
//
//    // bump head
//    if (m_controller->ceiling())	{
//        m_dynamics->m_velocity.y = 0;
//        m_animator->SetAnimation(m_jumpAnimDown);
//    }
//
//    float targetVelocityX = 0.0f;
//    if (left || right) {
//        if (m_flipHorizontally) {
//            m_entity->SetFlipX(left);
//            targetVelocityX = m_speed;
//        } else {
//            targetVelocityX = (left ? -1.0f : 1.0f) * m_speed;
//        }
//
//    }
//    glm::vec3 delta = m_dynamics->step(dt, targetVelocityX, m_accTimeAir);
//    //if (left) std::cerr<< "J " << m_dynamics->m_velocity.x << " " << delta.x << "\n";
//
//    m_controller->Move(delta);
//    UpdateAnimation();
//}
//
//
//void WalkSide::ResetAnimation() {}
//
//void WalkSide::ModifyAnimation() {
//    if (fabs(m_dynamics->m_velocity.x) > 1.0f) {
//        m_animator->SetAnimation(m_walkAnim);
//    } else {
//        m_animator->SetAnimation(m_idleAnim);
//    }
//
//
//}
//
