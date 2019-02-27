#include <platformer/walk.h>

#include <gfx/components/controller2d.h>
#include <gfx/components/animator.h>
#include <gfx/components/inputmethod.h>

#include <gfx/math/geom.h>
#include <gfx/entity.h>
#include <GLFW/glfw3.h>


extern GLFWwindow* window;

std::shared_ptr<State2> Walk::clone() const {
    return std::make_shared<Walk>(*this);
}


void Walk::AttachStateMachine(StateMachine2* sm) {
    m_stateMachine = (CharacterStateMachine*) dynamic_cast<CharacterStateMachine*>(sm);
    m_entity = sm->GetObject();
    m_controller = m_entity->GetComponent<Controller2D>();
    //m_animator = m_entity->GetComponent<Animator>();
    m_input = m_entity->GetComponent<InputMethod>();
}


void Walk::Run (double dt) {
    if (!m_controller->m_details.below) {
        m_stateMachine->SetState("jump");
        return;
    }

    bool left =m_input->isKeyDown(GLFW_KEY_LEFT);
    bool right =m_input->isKeyDown(GLFW_KEY_RIGHT);

    m_stateMachine->m_velocity.y = m_stateMachine->m_gravity * static_cast<float>(dt);
    float targetVelocityX = 0.0f;
    if (left || right) {
        m_entity->SetFlipX(left);
        targetVelocityX = m_speed;
    }

    m_stateMachine->m_velocity.x = SmoothDamp(m_stateMachine->m_velocity.x, targetVelocityX, m_velocitySmoothing, m_stateMachine->m_accTimeGnd, dt);
    glm::vec2 delta = static_cast<float>(dt) * m_stateMachine->m_velocity;
    m_controller->Move(delta);

}