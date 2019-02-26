#include <platformer/walk.h>

#include <gfx/components/controller2d.h>
#include <gfx/components/animator.h>

#include <gfx/math/geom.h>
#include <gfx/entity.h>
#include <GLFW/glfw3.h>


extern GLFWwindow* window;

void Walk::AttachStateMachine(StateMachine2* sm) {
    m_stateMachine = (CharacterStateMachine*) dynamic_cast<CharacterStateMachine*>(sm);
    m_entity = sm->GetObject();
    m_controller = m_entity->GetComponent<Controller2D>();
    m_animator = m_entity->GetComponent<Animator>();
}

void Walk::Run(double dt) {
    
    // if not touching the ground, set status to jump
    if (!m_controller->m_details.below) {
        m_stateMachine->SetState("jump");
        return;
    }
    int stateL = glfwGetKey(window, GLFW_KEY_LEFT);
    int stateR = glfwGetKey(window, GLFW_KEY_RIGHT);
    
    bool left = stateL == GLFW_PRESS;
    bool right = stateR == GLFW_PRESS;
    //    m_dynamics->m_velocity.y = m_dynamics->m_gravity * dt;
    m_stateMachine->m_velocity.y = m_stateMachine->m_gravity * dt;
    float targetVelocityX = 0.0f;
    if (left) {
        m_entity->SetFlipX(true);
        targetVelocityX = -m_speed;
        //m_renderer->SetFlipX(true);
    } else if (right) {
        m_entity->SetFlipX(false);
        targetVelocityX = m_speed;
        //m_renderer->SetFlipX(false);
    }
    //    m_dynamics->m_velocity.x = SmoothDamp(
    //            m_dynamics->m_velocity.x, targetVelocityX, m_velocitySmoothing, m_accTimeGnd, dt);
    m_stateMachine->m_velocity.x = SmoothDamp(m_stateMachine->m_velocity.x, targetVelocityX, m_velocitySmoothing, m_stateMachine->m_accTimeGnd, dt);
    glm::vec2 delta = static_cast<float>(dt) * m_stateMachine->m_velocity;
    m_controller->Move(delta);
}

