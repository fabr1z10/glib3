#include <platformer/characterstatemachine.h>
#include <gfx/components/controller2d.h>


void Idle::Run(double dt) {

    
    // if not touching the ground, set status to jump
    if (!m_controller->m_details.below) {
        m_stateMachine->SetState("jump");
        return;
    }
    
    m_stateMachine->m_velocity.y = m_stateMachine->m_gravity * dt;
    float targetVelocityX = 0.0f;
    //    m_dynamics->m_velocity.x = SmoothDamp(
    //            m_dynamics->m_velocity.x, targetVelocityX, m_velocitySmoothing, m_accTimeGnd, dt);
    //    glm::vec2 delta = static_cast<float>(dt) * m_dynamics->m_velocity;
    //    m_controller->Move(delta);
    //    return false;
    
}
